#include "CouponForm.h"
#include "DiscountManagement.h"
#include "Discount.h"
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace supermarketui;

// --- Helper: Refreshes the table with all coupons currently loaded ---
void CouponForm::RefreshGrid() {
    gridCoupons->Rows->Clear();

    // Force-recreate columns to avoid stale designer state.
    // Clearing and re-adding is safe — only Rows hold actual data.
    gridCoupons->Columns->Clear();
    gridCoupons->Columns->Add("ID", "ID");
    gridCoupons->Columns->Add("Code", "Code");
    gridCoupons->Columns->Add("Type", "Type");
    gridCoupons->Columns->Add("Value", "Value");
    gridCoupons->Columns->Add("Status", "Status");

    // Loop up to a reasonable max ID (mirrors CategoryForm's pattern).
    // findByID returns a default Discount (id=0) if not found, so we skip those.
    for (int i = 1; i <= 1000; i++) {
        Discount d = DiscountManagement::findByID(i);
        if (d.getID() != 0) {
            String^ id = d.getID().ToString();
            String^ code = msclr::interop::marshal_as<String^>(d.getCode());
            String^ type = msclr::interop::marshal_as<String^>(d.getType());
            String^ value = d.getValue().ToString("F2");
            String^ status = d.getIsActive() ? "Active" : "Inactive";
            gridCoupons->Rows->Add(id, code, type, value, status);
        }
    }
}

// --- Screen Load ---
System::Void CouponForm::CouponForm_Load(System::Object^ sender, System::EventArgs^ e) {
    try {
        DiscountManagement::loadFromFile();
        RefreshGrid();
        cbType->SelectedIndex = 0;  // Default to PERCENTAGE
    }
    catch (...) {}
}

// --- Cell Click: Auto-fill form fields from clicked row ---
System::Void CouponForm::gridCoupons_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
    if (e->RowIndex >= 0) {
        DataGridViewRow^ row = gridCoupons->Rows[e->RowIndex];
        txtID->Text = row->Cells[0]->Value->ToString();
        txtCode->Text = row->Cells[1]->Value->ToString();

        // Set the dropdown to whichever type is in the row
        String^ typeStr = row->Cells[2]->Value->ToString();
        int idx = cbType->Items->IndexOf(typeStr);
        if (idx >= 0) cbType->SelectedIndex = idx;

        txtValue->Text = row->Cells[3]->Value->ToString();
    }
}

// --- Clear Button: Reset all input fields ---
System::Void CouponForm::btnClear_Click(System::Object^ sender, System::EventArgs^ e) {
    txtID->Text = "";
    txtCode->Text = "";
    txtValue->Text = "";
    cbType->SelectedIndex = 0;
}

// --- Add Coupon ---
System::Void CouponForm::btnAdd_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        // Basic validation - none of the fields can be empty
        if (String::IsNullOrWhiteSpace(txtCode->Text) ||
            cbType->SelectedIndex < 0 ||
            String::IsNullOrWhiteSpace(txtValue->Text)) {
            MessageBox::Show("Please fill out Code, Type, and Value.", "Error",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        std::string code = msclr::interop::marshal_as<std::string>(txtCode->Text);
        std::string type = msclr::interop::marshal_as<std::string>(cbType->Text);
        float value = (float)Convert::ToDouble(txtValue->Text);

        if (DiscountManagement::addCoupon(code, type, value)) {
            DiscountManagement::saveToFile();
            MessageBox::Show("Coupon added successfully!", "Success",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            RefreshGrid();
            btnClear_Click(nullptr, nullptr);
        }
        else {
            MessageBox::Show("Failed to add coupon. Code may be a duplicate or contain invalid characters.",
                "Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }
    }
    catch (Exception^) {
        MessageBox::Show("Invalid input. Make sure Value is a valid number.", "Error",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

// --- Update Coupon ---
// Note: backend's editCoupon only changes type and value; the code is treated as
// immutable (changing a code is conceptually a delete + add).
System::Void CouponForm::btnUpdate_Click(System::Object^ sender, System::EventArgs^ e) {
    if (txtID->Text == "") {
        MessageBox::Show("Click a row in the table to select a coupon first.", "No Selection",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
        return;
    }
    try {
        int id = Convert::ToInt32(txtID->Text);
        std::string type = msclr::interop::marshal_as<std::string>(cbType->Text);
        float value = (float)Convert::ToDouble(txtValue->Text);

        if (DiscountManagement::editCoupon(id, type, value)) {
            DiscountManagement::saveToFile();
            MessageBox::Show("Coupon updated successfully!", "Success",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            RefreshGrid();
        }
        else {
            MessageBox::Show("Failed to update coupon. ID may not exist.", "Error",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }
    }
    catch (Exception^) {
        MessageBox::Show("Invalid input format.", "Error",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

// --- Delete Coupon ---
System::Void CouponForm::btnDelete_Click(System::Object^ sender, System::EventArgs^ e) {
    if (txtID->Text == "") {
        MessageBox::Show("Click a row in the table to select a coupon first.", "No Selection",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
        return;
    }
    if (MessageBox::Show("Are you sure you want to delete this coupon forever?",
        "Confirm Delete", MessageBoxButtons::YesNo, MessageBoxIcon::Warning)
        == System::Windows::Forms::DialogResult::Yes) {
        int id = Convert::ToInt32(txtID->Text);
        if (DiscountManagement::deleteCoupon(id)) {
            DiscountManagement::saveToFile();
            MessageBox::Show("Coupon deleted.", "Success",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            RefreshGrid();
            btnClear_Click(nullptr, nullptr);
        }
        else {
            MessageBox::Show("Could not delete coupon.", "Error",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }
    }
}

// --- Toggle Status (Active <-> Inactive) ---
System::Void CouponForm::btnToggle_Click(System::Object^ sender, System::EventArgs^ e) {
    if (txtID->Text == "") {
        MessageBox::Show("Click a row in the table to select a coupon first.", "No Selection",
            MessageBoxButtons::OK, MessageBoxIcon::Information);
        return;
    }
    try {
        int id = Convert::ToInt32(txtID->Text);
        Discount current = DiscountManagement::findByID(id);
        if (current.getID() == 0) {
            MessageBox::Show("Coupon not found.", "Error",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        bool newState = !current.getIsActive();
        if (DiscountManagement::setActive(id, newState)) {
            DiscountManagement::saveToFile();
            String^ msg = newState ? "Coupon activated." : "Coupon deactivated.";
            MessageBox::Show(msg, "Success",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
            RefreshGrid();
        }
        else {
            MessageBox::Show("Could not change status.", "Error",
                MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }
    }
    catch (Exception^) {
        MessageBox::Show("Invalid input format.", "Error",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}