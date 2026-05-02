#include "RefundForm.h"
#include <msclr\marshal_cppstd.h>

// Backend headers
#include "RefundManagement.h"
#include "TransactionManagement.h"
#include "ProductManagement.h"
#include "InventoryManagement.h"
#include "Product.h"
#include "ReceiptStore.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace supermarketui;

System::Void RefundForm::RefundForm_Load(System::Object^ sender, System::EventArgs^ e) {
    try {
        RefundManagement::loadFromFile();
        ProductManagement::loadFromFile();
        TransactionManagement::loadFromFile();
        InventoryManagement::loadFromFile();

        // Make Amount read-only - prevents the cashier entering a number that
        // doesn't match what was actually paid. Auto-calculated from the
        // saved receipt's unit price * quantity.
        txtAmount->ReadOnly = true;
        txtAmount->BackColor = System::Drawing::Color::FromArgb(240, 240, 240);

        // Hook up the auto-calc to all three input fields. Whenever any
        // of them changes, we recompute Amount.
        txtTransactionID->TextChanged += gcnew System::EventHandler(this, &RefundForm::RecalculateAmount);
        txtProductID->TextChanged += gcnew System::EventHandler(this, &RefundForm::RecalculateAmount);
        txtQuantity->TextChanged += gcnew System::EventHandler(this, &RefundForm::RecalculateAmount);
    }
    catch (...) {}
}

// Looks up the saved receipt for the entered Transaction ID, finds the
// product line item, and calculates the refund amount as
//   unit_price (from receipt) * quantity_being_returned.
//
// We use the saved receipt - NOT the current product price - so that price
// changes since the original sale don't affect the refund amount.
//
// If any input is incomplete or invalid, the Amount field is cleared. The
// real validation (over-refund, txn exists, etc.) happens server-side in
// RefundManagement::createRefund when the user clicks Process Refund.
System::Void RefundForm::RecalculateAmount(System::Object^ sender, System::EventArgs^ e) {
    try {
        if (String::IsNullOrWhiteSpace(txtTransactionID->Text) ||
            String::IsNullOrWhiteSpace(txtProductID->Text) ||
            String::IsNullOrWhiteSpace(txtQuantity->Text)) {
            txtAmount->Text = "";
            return;
        }

        int txnID = Convert::ToInt32(txtTransactionID->Text);
        int prodID = Convert::ToInt32(txtProductID->Text);
        int qty = Convert::ToInt32(txtQuantity->Text);

        if (txnID <= 0 || prodID <= 0 || qty <= 0) {
            txtAmount->Text = "";
            return;
        }

        // Pull the original sale receipt for this transaction.
        ReceiptRecord receipt = ReceiptStore::findSaleByTransactionID(txnID);
        if (receipt.transactionID == 0) {
            txtAmount->Text = "";
            return;
        }

        // Find this product on the receipt
        int idx = receipt.findItemByProductID(prodID);
        if (idx == -1) {
            txtAmount->Text = "";
            return;
        }

        // Calculate proportional refund amount.
        float refundAmount;
        if (receipt.subtotal > 0.001f) {
            // Per-unit proportional share of what they actually paid
            float perUnitPaid = (receipt.items[idx].lineTotal / receipt.items[idx].quantity)
                * (receipt.grandTotal / receipt.subtotal);
            refundAmount = perUnitPaid * qty;
        }
        else {
            // Fallback for corrupt receipts
            float baseAmount = receipt.items[idx].unitPrice * qty;
            const float taxRate = 0.17f;
            refundAmount = baseAmount * (1.0f + taxRate);
        }

        txtAmount->Text = refundAmount.ToString("F2");
    }
    catch (Exception^) {
        // Mid-typing or non-numeric input - just clear and wait
        txtAmount->Text = "";
    }
}

System::Void RefundForm::btnRefund_Click(System::Object^ sender, System::EventArgs^ e) {
    if (String::IsNullOrWhiteSpace(txtTransactionID->Text) ||
        String::IsNullOrWhiteSpace(txtProductID->Text) ||
        String::IsNullOrWhiteSpace(txtQuantity->Text) ||
        cmbReason->SelectedIndex == -1)
    {
        MessageBox::Show("Please fill out Transaction ID, Product ID, Quantity, and select a reason.",
            "Missing Info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
    }

    if (String::IsNullOrWhiteSpace(txtAmount->Text)) {
        MessageBox::Show("Refund amount could not be calculated. Verify that:\n"
            " - The Transaction ID exists.\n"
            " - The Product ID was actually purchased on this transaction.\n"
            "The amount auto-fills from the original receipt.",
            "Lookup Failed", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
    }

    try {
        int txnID = Convert::ToInt32(txtTransactionID->Text);
        int prodID = Convert::ToInt32(txtProductID->Text);
        int qty = Convert::ToInt32(txtQuantity->Text);
        float amount = (float)Convert::ToDouble(txtAmount->Text);
        std::string cppReason = msclr::interop::marshal_as<std::string>(cmbReason->SelectedItem->ToString());

        // Backend now enforces:
        //  - 30-day window
        //  - cumulative refund amount <= original transaction total
        //  - quantity refunded so far + this qty <= quantity originally purchased
        //  - sets status to "Partially Refunded" or "Fully Refunded" automatically
        bool success = RefundManagement::createRefund(txnID, cppReason, amount, prodID, qty);

        if (success) {
            MessageBox::Show("Refund processed successfully!\nInventory restocked.\nTransaction status updated.",
                "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

            txtTransactionID->Text = "";
            txtProductID->Text = "";
            txtQuantity->Text = "";
            txtAmount->Text = "";
            cmbReason->SelectedIndex = -1;
        }
        else {
            MessageBox::Show("Refund could not be processed. Possible reasons:\n\n"
                " - Transaction ID does not exist\n"
                " - Transaction is older than 30 days\n"
                " - Cumulative refund would exceed the original total\n"
                " - The quantity returned exceeds what was originally purchased\n"
                "   (including any prior partial refunds for this product)",
                "Refund Failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
    catch (Exception^) {
        MessageBox::Show("Please enter valid numeric values for IDs and Quantity.",
            "Format Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}