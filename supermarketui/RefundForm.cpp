#include "RefundForm.h"
#include <msclr\marshal_cppstd.h>

// Include your backend headers
#include "RefundManagement.h"
#include "TransactionManagement.h"
#include "ProductManagement.h"
#include "InventoryManagement.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace supermarketui;

System::Void RefundForm::RefundForm_Load(System::Object^ sender, System::EventArgs^ e) {
    try {
        RefundManagement::loadFromFile();
        ProductManagement::loadFromFile();
        TransactionManagement::loadFromFile();
        InventoryManagement::loadFromFile();
    }
    catch (...) {}
}

System::Void RefundForm::btnRefund_Click(System::Object^ sender, System::EventArgs^ e) {
    // 1. Check if any boxes are empty
    if (String::IsNullOrWhiteSpace(txtTransactionID->Text) ||
        String::IsNullOrWhiteSpace(txtProductID->Text) ||
        String::IsNullOrWhiteSpace(txtQuantity->Text) ||
        String::IsNullOrWhiteSpace(txtAmount->Text) ||
        cmbReason->SelectedIndex == -1)
    {
        MessageBox::Show("Please fill out all fields and select a reason.", "Missing Info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
    }

    try {
        // 2. Read the text boxes
        int txnID = Convert::ToInt32(txtTransactionID->Text);
        int prodID = Convert::ToInt32(txtProductID->Text);
        int qty = Convert::ToInt32(txtQuantity->Text);
        float amount = (float)Convert::ToDouble(txtAmount->Text);

        std::string cppReason = msclr::interop::marshal_as<std::string>(cmbReason->SelectedItem->ToString());

        // 3. Call your teammate's powerful Refund logic
        bool success = RefundManagement::createRefund(txnID, cppReason, amount, prodID, qty);

        if (success) {
            MessageBox::Show("Refund processed successfully!\nInventory has been restocked.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

            // Clear the form for the next customer
            txtTransactionID->Text = "";
            txtProductID->Text = "";
            txtQuantity->Text = "";
            txtAmount->Text = "";
            cmbReason->SelectedIndex = -1;
        }
        else {
            MessageBox::Show("Failed to process refund. Please double-check:\n- The Transaction ID exists and is within 30 days.\n- The Product ID exists.\n- The refund amount is not higher than the original bill.", "Refund Failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
    catch (Exception^) {
        MessageBox::Show("Please enter valid numbers for IDs, Quantity, and Amount.", "Format Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}
