#pragma once
#include <msclr\marshal_cppstd.h>

namespace supermarketui {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class InventoryForm : public System::Windows::Forms::Form
    {
    public:
        InventoryForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~InventoryForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::DataGridView^ gridInventory;
    private: System::Windows::Forms::Panel^ panelControls;

           // Input Fields
    private: System::Windows::Forms::Label^ lblID;
    private: System::Windows::Forms::TextBox^ txtID;
    private: System::Windows::Forms::Label^ lblName;
    private: System::Windows::Forms::TextBox^ txtName;
    private: System::Windows::Forms::Label^ lblCat;
    private: System::Windows::Forms::TextBox^ txtCategory;
    private: System::Windows::Forms::Label^ lblPrice;
    private: System::Windows::Forms::TextBox^ txtPrice;
    private: System::Windows::Forms::Label^ lblStock;
    private: System::Windows::Forms::TextBox^ txtStock;

           // Action Buttons
    private: System::Windows::Forms::Button^ btnAdd;
    private: System::Windows::Forms::Button^ btnUpdate;
    private: System::Windows::Forms::Button^ btnDelete;
    private: System::Windows::Forms::Button^ btnRestock;
    private: System::Windows::Forms::Button^ btnClear;

    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->gridInventory = (gcnew System::Windows::Forms::DataGridView());
               this->panelControls = (gcnew System::Windows::Forms::Panel());

               this->lblID = (gcnew System::Windows::Forms::Label());
               this->txtID = (gcnew System::Windows::Forms::TextBox());
               this->lblName = (gcnew System::Windows::Forms::Label());
               this->txtName = (gcnew System::Windows::Forms::TextBox());
               this->lblCat = (gcnew System::Windows::Forms::Label());
               this->txtCategory = (gcnew System::Windows::Forms::TextBox());
               this->lblPrice = (gcnew System::Windows::Forms::Label());
               this->txtPrice = (gcnew System::Windows::Forms::TextBox());
               this->lblStock = (gcnew System::Windows::Forms::Label());
               this->txtStock = (gcnew System::Windows::Forms::TextBox());

               this->btnAdd = (gcnew System::Windows::Forms::Button());
               this->btnUpdate = (gcnew System::Windows::Forms::Button());
               this->btnDelete = (gcnew System::Windows::Forms::Button());
               this->btnRestock = (gcnew System::Windows::Forms::Button());
               this->btnClear = (gcnew System::Windows::Forms::Button());

               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridInventory))->BeginInit();
               this->panelControls->SuspendLayout();
               this->SuspendLayout();

               System::Drawing::Font^ fLabel = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
               System::Drawing::Font^ fInput = (gcnew System::Drawing::Font(L"Segoe UI", 12));

               // lblTitle
               this->lblTitle->AutoSize = true;
               this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20, System::Drawing::FontStyle::Bold));
               this->lblTitle->Location = System::Drawing::Point(20, 20);
               this->lblTitle->Text = L"Inventory && Product Management";

               // gridInventory (Left Side)
               this->gridInventory->AllowUserToAddRows = false;
               this->gridInventory->AllowUserToDeleteRows = false;
               this->gridInventory->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
               this->gridInventory->BackgroundColor = System::Drawing::Color::White;
               this->gridInventory->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
               this->gridInventory->Location = System::Drawing::Point(20, 70);
               this->gridInventory->ReadOnly = true;
               this->gridInventory->RowHeadersVisible = false;
               this->gridInventory->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
               this->gridInventory->Size = System::Drawing::Size(600, 480);
               this->gridInventory->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &InventoryForm::gridInventory_CellClick);

               // panelControls (Right Side)
               this->panelControls->BackColor = System::Drawing::Color::White;
               this->panelControls->Location = System::Drawing::Point(640, 70);
               this->panelControls->Size = System::Drawing::Size(320, 480);
               this->panelControls->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

               // Inputs inside Panel
               this->lblID->AutoSize = true; this->lblID->Font = fLabel; this->lblID->Location = System::Drawing::Point(20, 20); this->lblID->Text = L"Product ID (Auto on Add):";
               this->txtID->Font = fInput; this->txtID->Location = System::Drawing::Point(20, 45); this->txtID->Size = System::Drawing::Size(280, 29);
               this->txtID->ReadOnly = true; // Protect ID from manual editing

               this->lblName->AutoSize = true; this->lblName->Font = fLabel; this->lblName->Location = System::Drawing::Point(20, 80); this->lblName->Text = L"Product Name:";
               this->txtName->Font = fInput; this->txtName->Location = System::Drawing::Point(20, 105); this->txtName->Size = System::Drawing::Size(280, 29);

               this->lblCat->AutoSize = true; this->lblCat->Font = fLabel; this->lblCat->Location = System::Drawing::Point(20, 140); this->lblCat->Text = L"Category ID:";
               this->txtCategory->Font = fInput; this->txtCategory->Location = System::Drawing::Point(20, 165); this->txtCategory->Size = System::Drawing::Size(280, 29);

               this->lblPrice->AutoSize = true; this->lblPrice->Font = fLabel; this->lblPrice->Location = System::Drawing::Point(20, 200); this->lblPrice->Text = L"Price (Rs.):";
               this->txtPrice->Font = fInput; this->txtPrice->Location = System::Drawing::Point(20, 225); this->txtPrice->Size = System::Drawing::Size(280, 29);

               this->lblStock->AutoSize = true; this->lblStock->Font = fLabel; this->lblStock->Location = System::Drawing::Point(20, 260); this->lblStock->Text = L"Initial Stock / Restock Qty:";
               this->txtStock->Font = fInput; this->txtStock->Location = System::Drawing::Point(20, 285); this->txtStock->Size = System::Drawing::Size(280, 29);

               // Buttons inside Panel
               this->btnAdd->BackColor = System::Drawing::Color::SeaGreen; this->btnAdd->ForeColor = System::Drawing::Color::White;
               this->btnAdd->Font = fLabel; this->btnAdd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnAdd->Location = System::Drawing::Point(20, 330); this->btnAdd->Size = System::Drawing::Size(135, 40); this->btnAdd->Text = L"Add Product";
               this->btnAdd->Click += gcnew System::EventHandler(this, &InventoryForm::btnAdd_Click);

               this->btnUpdate->BackColor = System::Drawing::Color::Goldenrod; this->btnUpdate->ForeColor = System::Drawing::Color::White;
               this->btnUpdate->Font = fLabel; this->btnUpdate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnUpdate->Location = System::Drawing::Point(165, 330); this->btnUpdate->Size = System::Drawing::Size(135, 40); this->btnUpdate->Text = L"Update Info";
               this->btnUpdate->Click += gcnew System::EventHandler(this, &InventoryForm::btnUpdate_Click);

               this->btnDelete->BackColor = System::Drawing::Color::IndianRed; this->btnDelete->ForeColor = System::Drawing::Color::White;
               this->btnDelete->Font = fLabel; this->btnDelete->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnDelete->Location = System::Drawing::Point(20, 380); this->btnDelete->Size = System::Drawing::Size(135, 40); this->btnDelete->Text = L"Delete Item";
               this->btnDelete->Click += gcnew System::EventHandler(this, &InventoryForm::btnDelete_Click);

               this->btnRestock->BackColor = System::Drawing::Color::DodgerBlue; this->btnRestock->ForeColor = System::Drawing::Color::White;
               this->btnRestock->Font = fLabel; this->btnRestock->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnRestock->Location = System::Drawing::Point(165, 380); this->btnRestock->Size = System::Drawing::Size(135, 40); this->btnRestock->Text = L"Restock Item (+)";
               this->btnRestock->Click += gcnew System::EventHandler(this, &InventoryForm::btnRestock_Click);

               this->btnClear->BackColor = System::Drawing::Color::Gray; this->btnClear->ForeColor = System::Drawing::Color::White;
               this->btnClear->Font = fLabel; this->btnClear->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnClear->Location = System::Drawing::Point(20, 430); this->btnClear->Size = System::Drawing::Size(280, 30); this->btnClear->Text = L"Clear Form";
               this->btnClear->Click += gcnew System::EventHandler(this, &InventoryForm::btnClear_Click);

               // Add controls to panel
               this->panelControls->Controls->Add(this->lblID); this->panelControls->Controls->Add(this->txtID);
               this->panelControls->Controls->Add(this->lblName); this->panelControls->Controls->Add(this->txtName);
               this->panelControls->Controls->Add(this->lblCat); this->panelControls->Controls->Add(this->txtCategory);
               this->panelControls->Controls->Add(this->lblPrice); this->panelControls->Controls->Add(this->txtPrice);
               this->panelControls->Controls->Add(this->lblStock); this->panelControls->Controls->Add(this->txtStock);
               this->panelControls->Controls->Add(this->btnAdd); this->panelControls->Controls->Add(this->btnUpdate);
               this->panelControls->Controls->Add(this->btnDelete); this->panelControls->Controls->Add(this->btnRestock);
               this->panelControls->Controls->Add(this->btnClear);

               // Form setup
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->BackColor = System::Drawing::Color::WhiteSmoke;
               this->ClientSize = System::Drawing::Size(980, 580);
               this->Controls->Add(this->panelControls);
               this->Controls->Add(this->gridInventory);
               this->Controls->Add(this->lblTitle);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->MaximizeBox = false;
               this->Name = L"InventoryForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"Inventory Management";
               this->Load += gcnew System::EventHandler(this, &InventoryForm::InventoryForm_Load);

               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridInventory))->EndInit();
               this->panelControls->ResumeLayout(false);
               this->panelControls->PerformLayout();
               this->ResumeLayout(false);
               this->PerformLayout();
           }
#pragma endregion

    private: System::Void InventoryForm_Load(System::Object^ sender, System::EventArgs^ e);
    private: System::Void gridInventory_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
    private: System::Void btnAdd_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnUpdate_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnDelete_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnRestock_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnClear_Click(System::Object^ sender, System::EventArgs^ e);

           // Helper function to draw the table
    private: void RefreshGrid();
    };
}
