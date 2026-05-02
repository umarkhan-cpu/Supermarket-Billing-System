#pragma once
#include <msclr\marshal_cppstd.h>

namespace supermarketui {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class CouponForm : public System::Windows::Forms::Form
    {
    public:
        CouponForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~CouponForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::DataGridView^ gridCoupons;
    private: System::Windows::Forms::Panel^ panelControls;

           // Input Fields
    private: System::Windows::Forms::Label^ lblID;
    private: System::Windows::Forms::TextBox^ txtID;
    private: System::Windows::Forms::Label^ lblCode;
    private: System::Windows::Forms::TextBox^ txtCode;
    private: System::Windows::Forms::Label^ lblType;
    private: System::Windows::Forms::ComboBox^ cbType;
    private: System::Windows::Forms::Label^ lblValue;
    private: System::Windows::Forms::TextBox^ txtValue;

           // Action Buttons
    private: System::Windows::Forms::Button^ btnAdd;
    private: System::Windows::Forms::Button^ btnUpdate;
    private: System::Windows::Forms::Button^ btnDelete;
    private: System::Windows::Forms::Button^ btnToggle;
    private: System::Windows::Forms::Button^ btnClear;

    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->gridCoupons = (gcnew System::Windows::Forms::DataGridView());
               this->panelControls = (gcnew System::Windows::Forms::Panel());
               this->lblID = (gcnew System::Windows::Forms::Label());
               this->txtID = (gcnew System::Windows::Forms::TextBox());
               this->lblCode = (gcnew System::Windows::Forms::Label());
               this->txtCode = (gcnew System::Windows::Forms::TextBox());
               this->lblType = (gcnew System::Windows::Forms::Label());
               this->cbType = (gcnew System::Windows::Forms::ComboBox());
               this->lblValue = (gcnew System::Windows::Forms::Label());
               this->txtValue = (gcnew System::Windows::Forms::TextBox());
               this->btnAdd = (gcnew System::Windows::Forms::Button());
               this->btnUpdate = (gcnew System::Windows::Forms::Button());
               this->btnDelete = (gcnew System::Windows::Forms::Button());
               this->btnToggle = (gcnew System::Windows::Forms::Button());
               this->btnClear = (gcnew System::Windows::Forms::Button());
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridCoupons))->BeginInit();
               this->panelControls->SuspendLayout();
               this->SuspendLayout();
               // 
               // lblTitle
               // 
               this->lblTitle->AutoSize = true;
               this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20, System::Drawing::FontStyle::Bold));
               this->lblTitle->Location = System::Drawing::Point(22, 25);
               this->lblTitle->Name = L"lblTitle";
               this->lblTitle->Size = System::Drawing::Size(432, 54);
               this->lblTitle->TabIndex = 0;
               this->lblTitle->Text = L"Coupon Management";
               // 
               // gridCoupons
               // 
               this->gridCoupons->AllowUserToAddRows = false;
               this->gridCoupons->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
               this->gridCoupons->Location = System::Drawing::Point(22, 100);
               this->gridCoupons->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
               this->gridCoupons->MultiSelect = false;
               this->gridCoupons->Name = L"gridCoupons";
               this->gridCoupons->ReadOnly = true;
               this->gridCoupons->RowHeadersWidth = 62;
               this->gridCoupons->RowTemplate->Height = 28;
               this->gridCoupons->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
               this->gridCoupons->Size = System::Drawing::Size(630, 475);
               this->gridCoupons->TabIndex = 1;
               this->gridCoupons->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &CouponForm::gridCoupons_CellClick);
               // 
               // panelControls
               // 
               this->panelControls->BackColor = System::Drawing::Color::White;
               this->panelControls->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
               this->panelControls->Controls->Add(this->lblID);
               this->panelControls->Controls->Add(this->txtID);
               this->panelControls->Controls->Add(this->lblCode);
               this->panelControls->Controls->Add(this->txtCode);
               this->panelControls->Controls->Add(this->lblType);
               this->panelControls->Controls->Add(this->cbType);
               this->panelControls->Controls->Add(this->lblValue);
               this->panelControls->Controls->Add(this->txtValue);
               this->panelControls->Controls->Add(this->btnAdd);
               this->panelControls->Controls->Add(this->btnUpdate);
               this->panelControls->Controls->Add(this->btnDelete);
               this->panelControls->Controls->Add(this->btnToggle);
               this->panelControls->Controls->Add(this->btnClear);
               this->panelControls->Location = System::Drawing::Point(675, 100);
               this->panelControls->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
               this->panelControls->Name = L"panelControls";
               this->panelControls->Size = System::Drawing::Size(337, 474);
               this->panelControls->TabIndex = 2;
               // 
               // lblID
               // 
               this->lblID->AutoSize = true;
               this->lblID->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
               this->lblID->Location = System::Drawing::Point(22, 25);
               this->lblID->Name = L"lblID";
               this->lblID->Size = System::Drawing::Size(42, 30);
               this->lblID->TabIndex = 0;
               this->lblID->Text = L"ID:";
               // 
               // txtID
               // 
               this->txtID->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->txtID->Location = System::Drawing::Point(124, 21);
               this->txtID->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
               this->txtID->Name = L"txtID";
               this->txtID->ReadOnly = true;
               this->txtID->Size = System::Drawing::Size(180, 39);
               this->txtID->TabIndex = 1;
               // 
               // lblCode
               // 
               this->lblCode->AutoSize = true;
               this->lblCode->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
               this->lblCode->Location = System::Drawing::Point(22, 75);
               this->lblCode->Name = L"lblCode";
               this->lblCode->Size = System::Drawing::Size(72, 30);
               this->lblCode->TabIndex = 2;
               this->lblCode->Text = L"Code:";
               // 
               // txtCode
               // 
               this->txtCode->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->txtCode->Location = System::Drawing::Point(124, 71);
               this->txtCode->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
               this->txtCode->Name = L"txtCode";
               this->txtCode->Size = System::Drawing::Size(180, 39);
               this->txtCode->TabIndex = 3;
               // 
               // lblType
               // 
               this->lblType->AutoSize = true;
               this->lblType->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
               this->lblType->Location = System::Drawing::Point(22, 125);
               this->lblType->Name = L"lblType";
               this->lblType->Size = System::Drawing::Size(69, 30);
               this->lblType->TabIndex = 4;
               this->lblType->Text = L"Type:";
               // 
               // cbType
               // 
               this->cbType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
               this->cbType->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->cbType->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"PERCENTAGE", L"FIXED" });
               this->cbType->Location = System::Drawing::Point(124, 121);
               this->cbType->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
               this->cbType->Name = L"cbType";
               this->cbType->Size = System::Drawing::Size(180, 40);
               this->cbType->TabIndex = 5;
               // 
               // lblValue
               // 
               this->lblValue->AutoSize = true;
               this->lblValue->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
               this->lblValue->Location = System::Drawing::Point(22, 175);
               this->lblValue->Name = L"lblValue";
               this->lblValue->Size = System::Drawing::Size(75, 30);
               this->lblValue->TabIndex = 6;
               this->lblValue->Text = L"Value:";
               // 
               // txtValue
               // 
               this->txtValue->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->txtValue->Location = System::Drawing::Point(124, 171);
               this->txtValue->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
               this->txtValue->Name = L"txtValue";
               this->txtValue->Size = System::Drawing::Size(180, 39);
               this->txtValue->TabIndex = 7;
               // 
               // btnAdd
               // 
               this->btnAdd->BackColor = System::Drawing::Color::SeaGreen;
               this->btnAdd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnAdd->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->btnAdd->ForeColor = System::Drawing::Color::White;
               this->btnAdd->Location = System::Drawing::Point(22, 231);
               this->btnAdd->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
               this->btnAdd->Name = L"btnAdd";
               this->btnAdd->Size = System::Drawing::Size(135, 50);
               this->btnAdd->TabIndex = 8;
               this->btnAdd->Text = L"Add";
               this->btnAdd->UseVisualStyleBackColor = false;
               this->btnAdd->Click += gcnew System::EventHandler(this, &CouponForm::btnAdd_Click);
               // 
               // btnUpdate
               // 
               this->btnUpdate->BackColor = System::Drawing::Color::Goldenrod;
               this->btnUpdate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnUpdate->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->btnUpdate->ForeColor = System::Drawing::Color::White;
               this->btnUpdate->Location = System::Drawing::Point(169, 231);
               this->btnUpdate->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
               this->btnUpdate->Name = L"btnUpdate";
               this->btnUpdate->Size = System::Drawing::Size(135, 50);
               this->btnUpdate->TabIndex = 9;
               this->btnUpdate->Text = L"Update";
               this->btnUpdate->UseVisualStyleBackColor = false;
               this->btnUpdate->Click += gcnew System::EventHandler(this, &CouponForm::btnUpdate_Click);
               // 
               // btnDelete
               // 
               this->btnDelete->BackColor = System::Drawing::Color::IndianRed;
               this->btnDelete->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnDelete->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->btnDelete->ForeColor = System::Drawing::Color::White;
               this->btnDelete->Location = System::Drawing::Point(22, 294);
               this->btnDelete->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
               this->btnDelete->Name = L"btnDelete";
               this->btnDelete->Size = System::Drawing::Size(135, 50);
               this->btnDelete->TabIndex = 10;
               this->btnDelete->Text = L"Delete";
               this->btnDelete->UseVisualStyleBackColor = false;
               this->btnDelete->Click += gcnew System::EventHandler(this, &CouponForm::btnDelete_Click);
               // 
               // btnToggle
               // 
               this->btnToggle->BackColor = System::Drawing::Color::SteelBlue;
               this->btnToggle->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnToggle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->btnToggle->ForeColor = System::Drawing::Color::White;
               this->btnToggle->Location = System::Drawing::Point(169, 294);
               this->btnToggle->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
               this->btnToggle->Name = L"btnToggle";
               this->btnToggle->Size = System::Drawing::Size(135, 50);
               this->btnToggle->TabIndex = 11;
               this->btnToggle->Text = L"Toggle Status";
               this->btnToggle->UseVisualStyleBackColor = false;
               this->btnToggle->Click += gcnew System::EventHandler(this, &CouponForm::btnToggle_Click);
               // 
               // btnClear
               // 
               this->btnClear->BackColor = System::Drawing::Color::Gray;
               this->btnClear->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnClear->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->btnClear->ForeColor = System::Drawing::Color::White;
               this->btnClear->Location = System::Drawing::Point(22, 356);
               this->btnClear->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
               this->btnClear->Name = L"btnClear";
               this->btnClear->Size = System::Drawing::Size(281, 50);
               this->btnClear->TabIndex = 12;
               this->btnClear->Text = L"Clear";
               this->btnClear->UseVisualStyleBackColor = false;
               this->btnClear->Click += gcnew System::EventHandler(this, &CouponForm::btnClear_Click);
               // 
               // CouponForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->AutoScroll = true;
               this->BackColor = System::Drawing::Color::WhiteSmoke;
               this->ClientSize = System::Drawing::Size(1058, 612);
               this->Controls->Add(this->lblTitle);
               this->Controls->Add(this->gridCoupons);
               this->Controls->Add(this->panelControls);
               this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
               this->MaximizeBox = false;
               this->Name = L"CouponForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"Coupon Management";
               this->Load += gcnew System::EventHandler(this, &CouponForm::CouponForm_Load);
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridCoupons))->EndInit();
               this->panelControls->ResumeLayout(false);
               this->panelControls->PerformLayout();
               this->ResumeLayout(false);
               this->PerformLayout();

           }
#pragma endregion

           // Method declarations - implemented in CouponForm.cpp
    private: void RefreshGrid();
    private: System::Void CouponForm_Load(System::Object^ sender, System::EventArgs^ e);
    private: System::Void gridCoupons_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
    private: System::Void btnAdd_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnUpdate_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnDelete_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnToggle_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnClear_Click(System::Object^ sender, System::EventArgs^ e);
    };
}