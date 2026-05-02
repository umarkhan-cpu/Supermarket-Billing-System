#include "BillingForm.h"
#include "ReceiptForm.h"
#include <msclr\marshal_cppstd.h>

// Backend headers
#include "ProductManagement.h"
#include "ReceiptAndBilling.h"
#include "DiscountManagement.h"
#include "TransactionManagement.h"
#include "SessionManager.h"
#include "User.h"
#include "InventoryManagement.h"
#include "ReceiptStore.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace supermarketui;

System::Void BillingForm::BillingForm_Load(System::Object^ sender, System::EventArgs^ e) {
    // When the form opens, we force the static classes to load their files!
    try {
        ProductManagement::loadFromFile();
        DiscountManagement::loadFromFile();
        TransactionManagement::loadFromFile();
        InventoryManagement::loadFromFile();
    }
    catch (...) {
        // Just in case the files don't exist yet
    }
}

System::Void BillingForm::btnAdd_Click(System::Object^ sender, System::EventArgs^ e) {
    if (String::IsNullOrWhiteSpace(txtProductID->Text) || String::IsNullOrWhiteSpace(txtQuantity->Text)) {
        MessageBox::Show("Please enter a Product ID and Quantity.", "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
    }

    try {
        int id = Convert::ToInt32(txtProductID->Text);
        int qty = Convert::ToInt32(txtQuantity->Text);

        if (qty <= 0) {
            MessageBox::Show("Quantity must be greater than 0.", "Input Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Talk to the backend!
        Product p = ProductManagement::findByID(id);

        // Assuming your backend returns ID 0 or -1 if the product isn't found
        if (p.getID() <= 0) {
            MessageBox::Show("Product not found in the system!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        if (p.getStock() < qty) {
            MessageBox::Show("Not enough stock available!", "Stock Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Add it to the UI Grid
        double price = p.getPrice();
        double lineTotal = price * qty;

        String^ name = gcnew String(p.getName().c_str());

        cli::array<String^>^ row = { id.ToString(), name, price.ToString("F2"), qty.ToString(), lineTotal.ToString("F2") };
        gridCart->Rows->Add(row);

        // Update Totals
        subtotal += lineTotal;
        UpdateTotals();

        // Clear the textboxes for the next item
        txtProductID->Text = "";
        txtQuantity->Text = "1";
    }
    catch (Exception^) {
        MessageBox::Show("Please enter valid numbers for ID and Quantity.", "Format Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void BillingForm::btnApplyCoupon_Click(System::Object^ sender, System::EventArgs^ e) {
    if (String::IsNullOrWhiteSpace(txtCoupon->Text)) return;

    std::string cppCode = msclr::interop::marshal_as<std::string>(txtCoupon->Text);

    // Call the backend discount system
    float disc = DiscountManagement::applyCoupon(cppCode, (float)subtotal);

    if (disc > 0) {
        discount = disc;
        UpdateTotals();
        MessageBox::Show("Coupon Applied successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
    else {
        MessageBox::Show("Invalid or inactive coupon.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void BillingForm::btnCheckout_Click(System::Object^ sender, System::EventArgs^ e) {
    if (gridCart->Rows->Count == 0) {
        MessageBox::Show("The cart is empty. Please add items before checking out.", "Empty Cart", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
    }

    try {
        // 1. Read the final Grand Total off the lblTotal display (parses "Rs. 84.00").
        float finalTotal = 0.0f;
        String^ rawText = lblTotal->Text;
        String^ cleanText = "";
        bool foundDecimal = false;

        for (int i = 0; i < rawText->Length; i++) {
            if (Char::IsDigit(rawText[i])) {
                cleanText += rawText[i];
            }
            else if (rawText[i] == '.' && !foundDecimal && cleanText->Length > 0) {
                cleanText += rawText[i];
                foundDecimal = true;
            }
        }
        if (cleanText == "") cleanText = "0";
        finalTotal = (float)Convert::ToDouble(cleanText);

        // 2. Generate transaction metadata
        int newID = TransactionManagement::getNextAvailableID();
        String^ sysDate = DateTime::Now.ToString("yyyy-MM-dd hh:mm tt");
        std::string cppDate = msclr::interop::marshal_as<std::string>(sysDate);
        int cashierID = SessionManager::getCurrentUser()->getID();
        std::string cashierName = SessionManager::getCurrentUser()->getUsername();

        // 3. Compute tax for the receipt (matches what's shown in lblTax)
        double tax = (subtotal - discount) * 0.17;
        if (tax < 0) tax = 0;

        // 4. Build the ReceiptRecord with structured line items.
        // This is the key new step - it preserves unit price and quantity per
        // item so refunds can later reconstruct what was actually purchased.
        ReceiptRecord receipt;
        receipt.transactionID = newID;
        receipt.dateTime = msclr::interop::marshal_as<std::string>(sysDate);
        receipt.cashierName = cashierName;
        receipt.type = "Sale";
        receipt.subtotal = (float)subtotal;
        receipt.discount = (float)discount;
        receipt.tax = (float)tax;
        receipt.grandTotal = finalTotal;

        for (int i = 0; i < gridCart->Rows->Count; i++) {
            int prodID = Convert::ToInt32(gridCart->Rows[i]->Cells[0]->Value);
            String^ nameStr = gridCart->Rows[i]->Cells[1]->Value->ToString();
            float price = (float)Convert::ToDouble(gridCart->Rows[i]->Cells[2]->Value);
            int qty = Convert::ToInt32(gridCart->Rows[i]->Cells[3]->Value);

            ReceiptItem item(prodID, msclr::interop::marshal_as<std::string>(nameStr), qty, price);
            receipt.addItem(item);
        }

        // 5. Persist receipt FIRST so even if a later step fails,
        // we have a record of what the customer paid for.
        ReceiptStore::saveReceipt(receipt);

        // 6. Deduct stock for each item in the cart
        for (int i = 0; i < gridCart->Rows->Count; i++) {
            int prodID = Convert::ToInt32(gridCart->Rows[i]->Cells[0]->Value);
            int qtyBought = Convert::ToInt32(gridCart->Rows[i]->Cells[3]->Value);
            InventoryManagement::removeStock(prodID, qtyBought);
        }

        // 7. Save the transaction record (existing flow)
        Transaction newTxn;
        newTxn.setData(newID, cppDate, cashierID, finalTotal, "Completed");
        TransactionManagement::addTransaction(newTxn);
        TransactionManagement::saveToFile();

        // 8. Show the receipt visually using our ReceiptForm.
        ReceiptForm^ receiptScreen = gcnew ReceiptForm(newID);
        receiptScreen->ShowDialog();

        // 9. Clear the cart and all totals for the next customer.
        // (The original code had these commented out due to a label name typo;
        // using the correct names - lblTotal not lblGrandTotal - it works.)
        gridCart->Rows->Clear();
        subtotal = 0.0;
        discount = 0.0;
        lblSubtotal->Text = L"Subtotal: Rs. 0.00";
        lblDiscount->Text = L"Discount: -Rs. 0.00";
        lblTax->Text = L"Tax (17%): Rs. 0.00";
        lblTotal->Text = L"Total: Rs. 0.00";
        txtProductID->Text = "";
        txtQuantity->Text = "1";
        txtCoupon->Text = "";
    }
    catch (Exception^ ex) {
        MessageBox::Show("Error: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

// Clears all items from the cart without checking out. Useful when a customer
// changes their mind mid-transaction or the cashier mis-rings several items.
// Confirms before wiping to prevent accidental clicks killing a real cart.
//
// Mirrors the cleanup that btnCheckout_Click does after a successful sale -
// same labels, same default values, same input field reset.
System::Void BillingForm::btnClearCart_Click(System::Object^ sender, System::EventArgs^ e) {
    if (gridCart->Rows->Count == 0) {
        // Nothing to clear - quietly do nothing rather than show a popup
        return;
    }

    if (MessageBox::Show("Clear all items from the cart?\nThis cannot be undone.",
        "Confirm Clear Cart", MessageBoxButtons::YesNo, MessageBoxIcon::Question)
        != System::Windows::Forms::DialogResult::Yes) {
        return;
    }

    // Wipe cart rows and reset all running totals back to zero
    gridCart->Rows->Clear();
    subtotal = 0.0;
    discount = 0.0;

    lblSubtotal->Text = L"Subtotal: Rs. 0.00";
    lblDiscount->Text = L"Discount: -Rs. 0.00";
    lblTax->Text = L"Tax (17%): Rs. 0.00";
    lblTotal->Text = L"Total: Rs. 0.00";

    // Reset input fields back to ready-for-next-item state
    txtProductID->Text = "";
    txtQuantity->Text = "1";
    txtCoupon->Text = "";
}