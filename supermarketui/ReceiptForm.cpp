#include "ReceiptForm.h"
#include "ReceiptStore.h"
#include <msclr\marshal_cppstd.h>
#include <sstream>
#include <iomanip>

using namespace System;
using namespace System::Windows::Forms;
using namespace supermarketui;

// Build a fixed-width line for one receipt item.
// Layout matches the header in ReceiptForm.h:
//   "Item                Qty    Price     Total"
// Columns:  0-18 = name (truncated)  18-23 = qty  24-32 = price  33-42 = total
//
// Note: tightened from the original 22/5/8/9 layout because Consolas 11pt at
// the actual rendered DPI was just slightly wider than expected, causing the
// "Total" column to wrap onto a new line. 18/5/9/9 fits cleanly in 490px.
static std::string formatItemLine(const ReceiptItem& item) {
    std::ostringstream ss;

    // Item name - truncate if too long for the narrower column
    std::string name = item.productName;
    if (name.size() > 18) name = name.substr(0, 15) + "...";

    ss << std::left << std::setw(18) << name
        << std::right << std::setw(5) << item.quantity << " "
        << std::fixed << std::setprecision(2) << std::setw(9) << item.unitPrice << " "
        << std::setw(9) << item.lineTotal;

    return ss.str();
}

System::Void ReceiptForm::ReceiptForm_Load(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Pull the receipt for the transaction ID we were constructed with.
        // We use findByTransactionID (not findSaleByTransactionID) so that
        // refund receipts can also be displayed - we'll switch theme based
        // on the type field below.
        ReceiptRecord receipt = ReceiptStore::findByTransactionID(this->targetTransactionID);

        if (receipt.transactionID == 0) {
            // No receipt found - tell the user and bail. Form still renders
            // its empty-state defaults.
            lblHeaderInfo->Text = L"Receipt not found for transaction ID "
                + targetTransactionID.ToString();
            return;
        }

        // Switch to red theme for refund receipts
        if (receipt.type == "Refund") {
            System::Drawing::Color refundBg = System::Drawing::Color::FromArgb(153, 27, 27); // deep red
            panelReceipt->BackColor = refundBg;
            lblStoreName->Text = L"REFUND RECEIPT";
            lblFooter->Text = L"Refund processed - keep this receipt for your records";
        }

        // Header info: date, cashier, transaction ID, type
        String^ dt = msclr::interop::marshal_as<String^>(receipt.dateTime);
        String^ cashier = msclr::interop::marshal_as<String^>(receipt.cashierName);
        String^ type = msclr::interop::marshal_as<String^>(receipt.type);

        String^ headerText = "Date:       " + dt + "\r\n"
            + "Cashier:    " + cashier + "\r\n"
            + "Type:       " + type + "    Txn ID: " + receipt.transactionID.ToString();
        lblHeaderInfo->Text = headerText;

        // Items body - one line per item, fixed-width formatted via stringstream
        std::ostringstream body;
        for (int i = 0; i < receipt.itemCount; i++) {
            body << formatItemLine(receipt.items[i]) << "\r\n";
        }
        lblItemsBody->Text = msclr::interop::marshal_as<String^>(body.str());

        // Build totals using a fixed-width column layout that fits in the label.
        // Format: "Label" left-padded to 30 chars, then "Rs. amount" right side.
        // No setw juggling - we just pad the label and concatenate.
        String^ subStr = "Subtotal:";
        while (subStr->Length < 30) subStr += " ";
        lblSubtotal->Text = subStr + "Rs. " + receipt.subtotal.ToString("F2");

        String^ discStr = "Discount:";
        while (discStr->Length < 30) discStr += " ";
        lblDiscount->Text = discStr + "Rs. " + receipt.discount.ToString("F2");

        String^ taxStr = "Tax(17%):";
        while (taxStr->Length < 30) taxStr += " ";
        lblTax->Text = taxStr + "Rs. " + receipt.tax.ToString("F2");

        // GRAND TOTAL uses larger font so we don't need so much padding.
        lblGrandTotal->Text = "GRAND TOTAL:    Rs. " + receipt.grandTotal.ToString("F2");
    }
    catch (Exception^ ex) {
        lblHeaderInfo->Text = L"Error loading receipt: " + ex->Message;
    }
}

System::Void ReceiptForm::btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
    this->Close();
}