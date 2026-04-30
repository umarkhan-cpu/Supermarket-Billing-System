#include "BillingForm.h"
#include <msclr\marshal_cppstd.h>

// Include your backend headers
#include "ProductManagement.h"
#include "ReceiptAndBilling.h"
#include "DiscountManagement.h"
#include "TransactionManagement.h"
#include "SessionManager.h"
#include "User.h"
#include "InventoryManagement.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace supermarketui;

System::Void BillingForm::BillingForm_Load(System::Object^ sender, System::EventArgs^ e) {
    // When the form opens, we force the static classes to load their files!
    try {
        ProductManagement::loadFromFile();
        DiscountManagement::loadFromFile();
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
        // 1. Calculate the final Grand Total (ignoring the dot in "Rs.")
        float finalTotal = 0.0f;
        String^ rawText = lblTotal->Text; // (Change this if your label is named lblTotal!)
        String^ cleanText = "";
        bool foundDecimal = false;

        for (int i = 0; i < rawText->Length; i++) {
            if (Char::IsDigit(rawText[i])) {
                cleanText += rawText[i];
            }
            // Only accept a decimal IF we already started reading a number!
            else if (rawText[i] == '.' && !foundDecimal && cleanText->Length > 0) {
                cleanText += rawText[i];
                foundDecimal = true;
            }
        }

        if (cleanText == "") cleanText = "0";
        finalTotal = (float)Convert::ToDouble(cleanText);

        // 2. Generate a new Transaction ID
        int newID = TransactionManagement::getCount() + 1;

        // 3. Get today's date in "YYYY-MM-DD" format using WinForms
        String^ sysDate = DateTime::Now.ToString("yyyy-MM-dd");
        std::string cppDate = msclr::interop::marshal_as<std::string>(sysDate);

        // 4. Get the current Cashier's ID
        int cashierID = SessionManager::getCurrentUser()->getID();

        // 5. Build Farda's Transaction Object!
        Transaction newTxn;
        newTxn.setData(newID, cppDate, cashierID, finalTotal, "Completed");
        // 5.5 Deduct the items from the Store Inventory!
        for (int i = 0; i < gridCart->Rows->Count; i++) {
            int prodID = Convert::ToInt32(gridCart->Rows[i]->Cells[0]->Value);
            int qtyBought = Convert::ToInt32(gridCart->Rows[i]->Cells[3]->Value);
            InventoryManagement::removeStock(prodID, qtyBought);
        }

        // 6. Save it to the database!
        TransactionManagement::addTransaction(newTxn);
        TransactionManagement::saveToFile();

        // Show the beautiful success message
        MessageBox::Show("Payment Processed Successfully!\nTransaction ID: " + newID.ToString() + "\nReceipt Generated.", "Checkout Complete", MessageBoxButtons::OK, MessageBoxIcon::Information);

        // Clear the cart for the next customer
        // NOTE: We keep these commented out so they don't crash the Event Handlers!
        // gridCart->Rows->Clear();
        // lblSubtotal->Text = "Rs. 0.00";
        // lblDiscount->Text = "Rs. 0.00";
        // lblTax->Text = "Rs. 0.00";
        // lblGrandTotal->Text = "Rs. 0.00";
        // txtProductID->Text = "";
        // txtQuantity->Text = "";
        // txtCoupon->Text = "";

    }
    catch (Exception^ ex) {
        MessageBox::Show("Error: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}




