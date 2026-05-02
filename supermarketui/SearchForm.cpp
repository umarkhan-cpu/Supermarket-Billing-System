#include "SearchForm.h"
#include "ProductManagement.h"
#include "CategoryManagement.h"
#include "Product.h"
#include "Category.h"
#include <msclr\marshal_cppstd.h>
#include <string>

using namespace System;
using namespace System::Windows::Forms;
using namespace supermarketui;

// Set up grid columns once. The grid is recreated rather than checked
// because reusing columns from a previous load can leave stale state
// (we hit this exact issue on CouponForm).
void SearchForm::EnsureColumns() {
    gridProducts->Columns->Clear();
    gridProducts->Columns->Add("ID", "ID");
    gridProducts->Columns->Add("Name", "Product Name");
    gridProducts->Columns->Add("Category", "Category");
    gridProducts->Columns->Add("Price", "Price (Rs.)");
    gridProducts->Columns->Add("Stock", "Stock");
}

// Helper: render every product currently loaded into memory.
// Used as the default state and on Reset.
void SearchForm::ShowAllProducts() {
    EnsureColumns();
    gridProducts->Rows->Clear();

    bool inStockOnly = chkInStock->Checked;

    // Loop up to a reasonable max ID (mirrors CategoryForm/CouponForm pattern).
    for (int i = 1; i <= 1000; i++) {
        Product p = ProductManagement::findByID(i);
        if (p.getID() == 0) continue;             // skip non-existent IDs
        if (inStockOnly && p.getStock() == 0) continue;

        // Look up the category name from the categoryID for display.
        Category cat = CategoryManagement::findByID(p.getCategoryID());
        std::string catNameStd = (cat.getID() != 0) ? cat.getName() : "(Unknown)";

        String^ id = p.getID().ToString();
        String^ name = msclr::interop::marshal_as<String^>(p.getName());
        String^ catName = msclr::interop::marshal_as<String^>(catNameStd);
        String^ price = p.getPrice().ToString("F2");
        String^ stock = p.getStock().ToString();
        gridProducts->Rows->Add(id, name, catName, price, stock);
    }
}

// On form load: pull fresh product/category data and populate grid with everything.
System::Void SearchForm::SearchForm_Load(System::Object^ sender, System::EventArgs^ e) {
    try {
        ProductManagement::loadFromFile();
        CategoryManagement::loadFromFile();
        ShowAllProducts();
    }
    catch (...) {}
}

// When user switches filter mode (Name / Category / Price), update labels
// and show/hide the second textbox (only Price uses it).
System::Void SearchForm::rbMode_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    // Only react to the radio button that just became checked, not the one
    // being unchecked (CheckedChanged fires for both).
    RadioButton^ rb = safe_cast<RadioButton^>(sender);
    if (!rb->Checked) return;

    if (rbName->Checked) {
        lblValue1->Text = L"Name contains:";
        lblValue2->Visible = false;
        txtValue2->Visible = false;
    }
    else if (rbCategory->Checked) {
        lblValue1->Text = L"Category Name:";
        lblValue2->Visible = false;
        txtValue2->Visible = false;
    }
    else if (rbPrice->Checked) {
        lblValue1->Text = L"Min Price:";
        lblValue2->Visible = true;
        txtValue2->Visible = true;
    }

    // Clear inputs when switching modes to avoid carry-over confusion.
    txtValue1->Text = "";
    txtValue2->Text = "";
}

// Apply whichever filter is currently selected.
// We query ProductManagement directly rather than calling SearchFilter::* methods
// because those methods print to console — they don't return data we can render.
// Apply whichever filter is currently selected.
System::Void SearchForm::btnSearch_Click(System::Object^ sender, System::EventArgs^ e) {
    try {
        EnsureColumns();
        gridProducts->Rows->Clear();

        bool inStockOnly = chkInStock->Checked;

        // Capture filter parameters based on which radio is selected.
        std::string nameNeedle;
        std::string categoryNeedle;
        float minPrice = 0.0f, maxPrice = 0.0f;

        if (rbName->Checked) {
            nameNeedle = msclr::interop::marshal_as<std::string>(txtValue1->Text);
            for (size_t i = 0; i < nameNeedle.size(); i++) {
                nameNeedle[i] = (char)tolower((unsigned char)nameNeedle[i]);
            }
        }
        else if (rbCategory->Checked) {
            if (String::IsNullOrWhiteSpace(txtValue1->Text)) {
                MessageBox::Show("Please enter a category name.", "Missing input",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }
            categoryNeedle = msclr::interop::marshal_as<std::string>(txtValue1->Text);
            for (size_t i = 0; i < categoryNeedle.size(); i++) {
                categoryNeedle[i] = (char)tolower((unsigned char)categoryNeedle[i]);
            }
        }
        else if (rbPrice->Checked) {
            if (String::IsNullOrWhiteSpace(txtValue1->Text) ||
                String::IsNullOrWhiteSpace(txtValue2->Text)) {
                MessageBox::Show("Please enter both Min and Max prices.", "Missing input",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }
            minPrice = (float)Convert::ToDouble(txtValue1->Text);
            maxPrice = (float)Convert::ToDouble(txtValue2->Text);
            if (maxPrice < minPrice) {
                MessageBox::Show("Max price must be >= Min price.", "Invalid range",
                    MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }
        }

        int matches = 0;

        for (int i = 1; i <= 1000; i++) {
            Product p = ProductManagement::findByID(i);
            if (p.getID() == 0) continue;
            if (inStockOnly && p.getStock() == 0) continue;

            Category cat = CategoryManagement::findByID(p.getCategoryID());
            std::string catNameStd = (cat.getID() != 0) ? cat.getName() : "(Unknown)";

            if (rbName->Checked) {
                std::string pname = p.getName();
                for (size_t j = 0; j < pname.size(); j++) {
                    pname[j] = (char)tolower((unsigned char)pname[j]);
                }
                if (!nameNeedle.empty() && pname.find(nameNeedle) == std::string::npos) {
                    continue;
                }
            }
            else if (rbCategory->Checked) {
                std::string catLower = catNameStd;
                for (size_t j = 0; j < catLower.size(); j++) {
                    catLower[j] = (char)tolower((unsigned char)catLower[j]);
                }
                if (catLower.find(categoryNeedle) == std::string::npos) continue;
            }
            else if (rbPrice->Checked) {
                if (p.getPrice() < minPrice || p.getPrice() > maxPrice) continue;
            }

            String^ id = p.getID().ToString();
            String^ name = msclr::interop::marshal_as<String^>(p.getName());
            String^ catName = msclr::interop::marshal_as<String^>(catNameStd);
            String^ price = p.getPrice().ToString("F2");
            String^ stock = p.getStock().ToString();
            gridProducts->Rows->Add(id, name, catName, price, stock);
            matches++;
        }

        if (matches == 0) {
            MessageBox::Show("No products matched your filter.", "No results",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }
    catch (Exception^) {
        MessageBox::Show("Invalid input format. Make sure numeric fields contain numbers.",
            "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}
// Reset: clear all inputs, uncheck in-stock filter, switch back to Name mode,
// and re-render everything.
System::Void SearchForm::btnReset_Click(System::Object^ sender, System::EventArgs^ e) {
    txtValue1->Text = "";
    txtValue2->Text = "";
    chkInStock->Checked = false;
    rbName->Checked = true;  // this also fires rbMode_CheckedChanged which fixes labels
    ShowAllProducts();
}