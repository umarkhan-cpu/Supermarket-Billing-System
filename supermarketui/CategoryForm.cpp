#include "CategoryForm.h"
#include "CategoryManagement.h"
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace supermarketui;

// --- Helper: Refreshes the Table ---
void CategoryForm::RefreshGrid() {
    gridCategories->Rows->Clear();

    if (gridCategories->Columns->Count == 0) {
        gridCategories->Columns->Add("ID", "ID");
        gridCategories->Columns->Add("Name", "Category Name");
        gridCategories->Columns->Add("Desc", "Description");
    }

    int count = CategoryManagement::getCount();
    // Assuming you have a getAt(i) function, or we can loop by ID if needed.
    // If getAt doesn't exist, we can use findByID (assuming IDs are somewhat sequential).
    // Let's use findByID for safety up to a reasonable max, or write a quick loop.
    for (int i = 1; i <= 100; i++) { // Loop up to max possible ID to find active ones
        Category c = CategoryManagement::findByID(i);
        if (c.getID() != 0) {
            String^ id = c.getID().ToString();
            String^ name = msclr::interop::marshal_as<String^>(c.getName());
            String^ desc = msclr::interop::marshal_as<String^>(c.getDescription());
            gridCategories->Rows->Add(id, name, desc);
        }
    }
}

// --- Screen Load ---
System::Void CategoryForm::CategoryForm_Load(System::Object^ sender, System::EventArgs^ e) {
    try {
        CategoryManagement::loadFromFile();
        RefreshGrid();
    }
    catch (...) {}
}

// --- Cell Click: Auto-fill the form! ---
System::Void CategoryForm::gridCategories_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
    if (e->RowIndex >= 0) {
        DataGridViewRow^ row = gridCategories->Rows[e->RowIndex];
        txtID->Text = row->Cells[0]->Value->ToString();
        txtName->Text = row->Cells[1]->Value->ToString();
        txtDesc->Text = row->Cells[2]->Value->ToString();
    }
}

// --- Clear Button ---
System::Void CategoryForm::btnClear_Click(System::Object^ sender, System::EventArgs^ e) {
    txtID->Text = ""; txtName->Text = ""; txtDesc->Text = "";
}

// --- Add Category ---
System::Void CategoryForm::btnAdd_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        std::string name = msclr::interop::marshal_as<std::string>(txtName->Text);
        std::string desc = msclr::interop::marshal_as<std::string>(txtDesc->Text);

        if (CategoryManagement::addCategory(name, desc)) {
            MessageBox::Show("Category added successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
            RefreshGrid();
            btnClear_Click(nullptr, nullptr);
        }
        else {
            MessageBox::Show("Failed to add Category. Remember names cannot contain commas!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }
    }
    catch (Exception^) { MessageBox::Show("Invalid input.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error); }
}

// --- Update Category ---
System::Void CategoryForm::btnUpdate_Click(System::Object^ sender, System::EventArgs^ e) {
    if (txtID->Text == "") return;
    try {
        int id = Convert::ToInt32(txtID->Text);
        std::string name = msclr::interop::marshal_as<std::string>(txtName->Text);
        std::string desc = msclr::interop::marshal_as<std::string>(txtDesc->Text);

        if (CategoryManagement::editCategory(id, name, desc)) {
            MessageBox::Show("Category updated successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
            RefreshGrid();
        }
    }
    catch (Exception^) { MessageBox::Show("Invalid input format.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error); }
}

// --- Delete Category ---
System::Void CategoryForm::btnDelete_Click(System::Object^ sender, System::EventArgs^ e) {
    if (txtID->Text == "") return;
    if (MessageBox::Show("Are you sure you want to delete this Category forever?", "Confirm Delete", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::Yes) {
        int id = Convert::ToInt32(txtID->Text);
        CategoryManagement::deleteCategory(id);
        RefreshGrid();
        btnClear_Click(nullptr, nullptr);
    }
}
