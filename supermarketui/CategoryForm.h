#pragma once
#include <msclr\marshal_cppstd.h>

namespace supermarketui {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class CategoryForm : public System::Windows::Forms::Form
    {
    public:
        CategoryForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~CategoryForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::DataGridView^ gridCategories;
    private: System::Windows::Forms::Panel^ panelControls;

           // Input Fields
    private: System::Windows::Forms::Label^ lblID;
    private: System::Windows::Forms::TextBox^ txtID;
    private: System::Windows::Forms::Label^ lblName;
    private: System::Windows::Forms::TextBox^ txtName;
    private: System::Windows::Forms::Label^ lblDesc;
    private: System::Windows::Forms::TextBox^ txtDesc;

           // Action Buttons
    private: System::Windows::Forms::Button^ btnAdd;
    private: System::Windows::Forms::Button^ btnUpdate;
    private: System::Windows::Forms::Button^ btnDelete;
    private: System::Windows::Forms::Button^ btnClear;

    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->gridCategories = (gcnew System::Windows::Forms::DataGridView());
               this->panelControls = (gcnew System::Windows::Forms::Panel());

               this->lblID = (gcnew System::Windows::Forms::Label());
               this->txtID = (gcnew System::Windows::Forms::TextBox());
               this->lblName = (gcnew System::Windows::Forms::Label());
               this->txtName = (gcnew System::Windows::Forms::TextBox());
               this->lblDesc = (gcnew System::Windows::Forms::Label());
               this->txtDesc = (gcnew System::Windows::Forms::TextBox());

               this->btnAdd = (gcnew System::Windows::Forms::Button());
               this->btnUpdate = (gcnew System::Windows::Forms::Button());
               this->btnDelete = (gcnew System::Windows::Forms::Button());
               this->btnClear = (gcnew System::Windows::Forms::Button());

               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridCategories))->BeginInit();
               this->panelControls->SuspendLayout();
               this->SuspendLayout();

               System::Drawing::Font^ fLabel = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
               System::Drawing::Font^ fInput = (gcnew System::Drawing::Font(L"Segoe UI", 12));

               // lblTitle
               this->lblTitle->AutoSize = true;
               this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20, System::Drawing::FontStyle::Bold));
               this->lblTitle->Location = System::Drawing::Point(20, 20);
               this->lblTitle->Text = L"Category Management";

               // gridCategories (Left Side)
               this->gridCategories->AllowUserToAddRows = false;
               this->gridCategories->AllowUserToDeleteRows = false;
               this->gridCategories->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
               this->gridCategories->BackgroundColor = System::Drawing::Color::White;
               this->gridCategories->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
               this->gridCategories->Location = System::Drawing::Point(20, 70);
               this->gridCategories->ReadOnly = true;
               this->gridCategories->RowHeadersVisible = false;
               this->gridCategories->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
               this->gridCategories->Size = System::Drawing::Size(500, 350);
               this->gridCategories->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &CategoryForm::gridCategories_CellClick);

               // panelControls (Right Side)
               this->panelControls->BackColor = System::Drawing::Color::White;
               this->panelControls->Location = System::Drawing::Point(540, 70);
               this->panelControls->Size = System::Drawing::Size(320, 350);
               this->panelControls->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

               // Inputs inside Panel
               this->lblID->AutoSize = true; this->lblID->Font = fLabel; this->lblID->Location = System::Drawing::Point(20, 20); this->lblID->Text = L"Category ID (Auto on Add):";
               this->txtID->Font = fInput; this->txtID->Location = System::Drawing::Point(20, 45); this->txtID->Size = System::Drawing::Size(280, 29);
               this->txtID->ReadOnly = true;

               this->lblName->AutoSize = true; this->lblName->Font = fLabel; this->lblName->Location = System::Drawing::Point(20, 80); this->lblName->Text = L"Category Name:";
               this->txtName->Font = fInput; this->txtName->Location = System::Drawing::Point(20, 105); this->txtName->Size = System::Drawing::Size(280, 29);

               this->lblDesc->AutoSize = true; this->lblDesc->Font = fLabel; this->lblDesc->Location = System::Drawing::Point(20, 140); this->lblDesc->Text = L"Description:";
               this->txtDesc->Font = fInput; this->txtDesc->Location = System::Drawing::Point(20, 165); this->txtDesc->Size = System::Drawing::Size(280, 29);

               // Buttons inside Panel
               this->btnAdd->BackColor = System::Drawing::Color::SeaGreen; this->btnAdd->ForeColor = System::Drawing::Color::White;
               this->btnAdd->Font = fLabel; this->btnAdd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnAdd->Location = System::Drawing::Point(20, 230); this->btnAdd->Size = System::Drawing::Size(135, 40); this->btnAdd->Text = L"Add Category";
               this->btnAdd->Click += gcnew System::EventHandler(this, &CategoryForm::btnAdd_Click);

               this->btnUpdate->BackColor = System::Drawing::Color::Goldenrod; this->btnUpdate->ForeColor = System::Drawing::Color::White;
               this->btnUpdate->Font = fLabel; this->btnUpdate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnUpdate->Location = System::Drawing::Point(165, 230); this->btnUpdate->Size = System::Drawing::Size(135, 40); this->btnUpdate->Text = L"Update Info";
               this->btnUpdate->Click += gcnew System::EventHandler(this, &CategoryForm::btnUpdate_Click);

               this->btnDelete->BackColor = System::Drawing::Color::IndianRed; this->btnDelete->ForeColor = System::Drawing::Color::White;
               this->btnDelete->Font = fLabel; this->btnDelete->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnDelete->Location = System::Drawing::Point(20, 280); this->btnDelete->Size = System::Drawing::Size(135, 40); this->btnDelete->Text = L"Delete";
               this->btnDelete->Click += gcnew System::EventHandler(this, &CategoryForm::btnDelete_Click);

               this->btnClear->BackColor = System::Drawing::Color::Gray; this->btnClear->ForeColor = System::Drawing::Color::White;
               this->btnClear->Font = fLabel; this->btnClear->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnClear->Location = System::Drawing::Point(165, 280); this->btnClear->Size = System::Drawing::Size(135, 40); this->btnClear->Text = L"Clear Form";
               this->btnClear->Click += gcnew System::EventHandler(this, &CategoryForm::btnClear_Click);

               // Add controls to panel
               this->panelControls->Controls->Add(this->lblID); this->panelControls->Controls->Add(this->txtID);
               this->panelControls->Controls->Add(this->lblName); this->panelControls->Controls->Add(this->txtName);
               this->panelControls->Controls->Add(this->lblDesc); this->panelControls->Controls->Add(this->txtDesc);
               this->panelControls->Controls->Add(this->btnAdd); this->panelControls->Controls->Add(this->btnUpdate);
               this->panelControls->Controls->Add(this->btnDelete); this->panelControls->Controls->Add(this->btnClear);

               // Form setup
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->BackColor = System::Drawing::Color::WhiteSmoke;
               this->ClientSize = System::Drawing::Size(880, 450);
               this->Controls->Add(this->panelControls);
               this->Controls->Add(this->gridCategories);
               this->Controls->Add(this->lblTitle);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->MaximizeBox = false;
               this->Name = L"CategoryForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"Category Management";
               this->Load += gcnew System::EventHandler(this, &CategoryForm::CategoryForm_Load);

               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridCategories))->EndInit();
               this->panelControls->ResumeLayout(false);
               this->panelControls->PerformLayout();
               this->ResumeLayout(false);
               this->PerformLayout();
           }
#pragma endregion

    private: System::Void CategoryForm_Load(System::Object^ sender, System::EventArgs^ e);
    private: System::Void gridCategories_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
    private: System::Void btnAdd_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnUpdate_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnDelete_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnClear_Click(System::Object^ sender, System::EventArgs^ e);

           // Helper function to draw the table
    private: void RefreshGrid();
    };
}
