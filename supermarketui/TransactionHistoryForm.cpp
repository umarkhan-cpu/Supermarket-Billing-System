#include "TransactionHistoryForm.h"
#include "TransactionManagement.h"
#include "ReceiptForm.h"
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace supermarketui;

// Helper function to draw the grid columns and load the data!
void TransactionHistoryForm::PopulateGrid() {
    gridHistory->Rows->Clear();
    gridHistory->Columns->Clear();

    // Create the columns for the table
    gridHistory->Columns->Add("ID", "Receipt ID");
    gridHistory->Columns->Add("Date", "Date");
    gridHistory->Columns->Add("Cashier", "Cashier ID");
    gridHistory->Columns->Add("Amount", "Total Amount (Rs)");
    gridHistory->Columns->Add("Status", "Status");

    // Loop through all transactions in the backend and add them to the table!
    int count = TransactionManagement::getCount();
    for (int i = 0; i < count; i++) {
        Transaction t = TransactionManagement::getByIndex(i);

        String^ id = t.getID().ToString();
        String^ date = msclr::interop::marshal_as<String^>(t.getDate());
        String^ cashier = t.getCashierID().ToString();
        String^ amount = t.getTotalAmount().ToString("F2");
        String^ status = msclr::interop::marshal_as<String^>(t.getStatus());

        gridHistory->Rows->Add(id, date, cashier, amount, status);
    }
}

System::Void TransactionHistoryForm::TransactionHistoryForm_Load(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Load the text file from the database
        TransactionManagement::loadFromFile();

        // Build the table
        PopulateGrid();
    }
    catch (...) {}
}

System::Void TransactionHistoryForm::btnSearch_Click(System::Object^ sender, System::EventArgs^ e) {
    if (String::IsNullOrWhiteSpace(txtSearchID->Text)) return;

    try {
        int searchID = Convert::ToInt32(txtSearchID->Text);

        // Find the specific transaction
        Transaction t = TransactionManagement::searchByID(searchID);

        if (t.getID() == 0) {
            MessageBox::Show("No transaction found with ID " + searchID, "Not Found", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Clear the table and show ONLY the searched result!
        gridHistory->Rows->Clear();

        String^ id = t.getID().ToString();
        String^ date = msclr::interop::marshal_as<String^>(t.getDate());
        String^ cashier = t.getCashierID().ToString();
        String^ amount = t.getTotalAmount().ToString("F2");
        String^ status = msclr::interop::marshal_as<String^>(t.getStatus());

        gridHistory->Rows->Add(id, date, cashier, amount, status);
    }
    catch (Exception^) {
        MessageBox::Show("Please enter a valid numeric ID.", "Format Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void TransactionHistoryForm::btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
    // Reset the search box and show everything again
    txtSearchID->Text = "";
    PopulateGrid();
}

System::Void TransactionHistoryForm::btnViewReceipt_Click(System::Object^ sender, System::EventArgs^ e) {
    // Get the currently selected row
    if (gridHistory->SelectedRows->Count == 0) {
        MessageBox::Show("Please click on a transaction row first.",
            "No Selection", MessageBoxButtons::OK, MessageBoxIcon::Information);
        return;
    }

    try {
        DataGridViewRow^ row = gridHistory->SelectedRows[0];
        int txnID = Convert::ToInt32(row->Cells[0]->Value);

        // Open the receipt form for this transaction.
        // ReceiptForm internally calls ReceiptStore::findByTransactionID
        // and shows a friendly "not found" if no receipt was saved
        // (e.g., for transactions created before receipt-saving was added).
        ReceiptForm^ receiptScreen = gcnew ReceiptForm(txnID);
        receiptScreen->ShowDialog();
    }
    catch (Exception^ ex) {
        MessageBox::Show("Error opening receipt: " + ex->Message,
            "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}