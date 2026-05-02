#include "InventoryForm.h"
#include "ProductManagement.h"
#include "InventoryManagement.h"
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace supermarketui;

// --- Helper: Refreshes the Table ---
void InventoryForm::RefreshGrid() {
    gridInventory->Rows->Clear();

    if (gridInventory->Columns->Count == 0) {
        gridInventory->Columns->Add("ID", "ID");
        gridInventory->Columns->Add("Name", "Product Name");
        gridInventory->Columns->Add("Category", "Category");
        gridInventory->Columns->Add("Price", "Price (Rs.)");
        gridInventory->Columns->Add("Stock", "Stock");
    }

    int count = ProductManagement::getCount();
    for (int i = 0; i < count; i++) {
        Product p = ProductManagement::getAt(i);

        String^ id = p.getID().ToString();
        String^ name = msclr::interop::marshal_as<String^>(p.getName());
        String^ cat = p.getCategoryID().ToString();
        String^ price = p.getPrice().ToString("F2");
        String^ stock = p.getStock().ToString();

        gridInventory->Rows->Add(id, name, cat, price, stock);

        // Highlight low stock items in red!
        if (p.getStock() <= 5) {
            gridInventory->Rows[i]->DefaultCellStyle->BackColor = Drawing::Color::MistyRose;
            gridInventory->Rows[i]->DefaultCellStyle->ForeColor = Drawing::Color::DarkRed;
        }
    }
}

// --- Screen Load ---
System::Void InventoryForm::InventoryForm_Load(System::Object^ sender, System::EventArgs^ e) {
    try {
        ProductManagement::loadFromFile();
        InventoryManagement::loadFromFile();
        RefreshGrid();
    }
    catch (...) {}
}

// --- Cell Click: Auto-fill the form! ---
System::Void InventoryForm::gridInventory_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
    if (e->RowIndex >= 0) {
        DataGridViewRow^ row = gridInventory->Rows[e->RowIndex];
        txtID->Text = row->Cells[0]->Value->ToString();
        txtName->Text = row->Cells[1]->Value->ToString();
        txtCategory->Text = row->Cells[2]->Value->ToString();
        txtPrice->Text = row->Cells[3]->Value->ToString();
        txtStock->Text = ""; // Leave blank so they can type a restock amount
    }
}

// --- Clear Button ---
System::Void InventoryForm::btnClear_Click(System::Object^ sender, System::EventArgs^ e) {
    txtID->Text = ""; txtName->Text = ""; txtCategory->Text = ""; txtPrice->Text = ""; txtStock->Text = "";
}

// --- Add Product ---
System::Void InventoryForm::btnAdd_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        std::string name = msclr::interop::marshal_as<std::string>(txtName->Text);
        int cat = Convert::ToInt32(txtCategory->Text);
        float price = (float)Convert::ToDouble(txtPrice->Text);
        int stock = Convert::ToInt32(txtStock->Text);

        if (ProductManagement::addProduct(name, cat, price, stock)) {
            MessageBox::Show("Product added successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
            RefreshGrid();
            btnClear_Click(nullptr, nullptr);
        }
        else {
            MessageBox::Show("Failed to add product. Check your inputs.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }
    }
    catch (Exception^) { MessageBox::Show("Invalid input format.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error); }
}

// --- Update Product ---
System::Void InventoryForm::btnUpdate_Click(System::Object^ sender, System::EventArgs^ e) {
    if (txtID->Text == "") return;
    try {
        int id = Convert::ToInt32(txtID->Text);
        std::string name = msclr::interop::marshal_as<std::string>(txtName->Text);
        int cat = Convert::ToInt32(txtCategory->Text);
        float price = (float)Convert::ToDouble(txtPrice->Text);
        int stock = ProductManagement::findByID(id).getStock(); // Keep existing stock

        if (ProductManagement::editProduct(id, name, cat, price, stock)) {
            MessageBox::Show("Product updated successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
            RefreshGrid();
        }
    }
    catch (Exception^) { MessageBox::Show("Invalid input format.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error); }
}

// --- Delete Product ---
System::Void InventoryForm::btnDelete_Click(System::Object^ sender, System::EventArgs^ e) {
    if (txtID->Text == "") return;
    if (MessageBox::Show("Are you sure you want to delete this product forever?", "Confirm Delete", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::Yes) {
        int id = Convert::ToInt32(txtID->Text);
        ProductManagement::deleteProduct(id);
        RefreshGrid();
        btnClear_Click(nullptr, nullptr);
    }
}

// --- Restock Item ---
System::Void InventoryForm::btnRestock_Click(System::Object^ sender, System::EventArgs^ e) {
    if (txtID->Text == "" || txtStock->Text == "") return;
    try {
        int id = Convert::ToInt32(txtID->Text);
        int amount = Convert::ToInt32(txtStock->Text);

        if (InventoryManagement::addStock(id, amount)) {
            MessageBox::Show(amount + " units successfully added to stock!", "Restocked", MessageBoxButtons::OK, MessageBoxIcon::Information);
            RefreshGrid();
            txtStock->Text = "";
        }
        else {
            MessageBox::Show("Failed to restock. Make sure product exists.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }
    }
    catch (Exception^) { MessageBox::Show("Please enter a valid stock amount.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error); }
}
