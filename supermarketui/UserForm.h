#pragma once
#include <msclr\marshal_cppstd.h>

namespace supermarketui {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class UserForm : public System::Windows::Forms::Form
    {
    public:
        UserForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~UserForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::DataGridView^ gridUsers;
    private: System::Windows::Forms::Panel^ panelControls;

           // Input Fields
    private: System::Windows::Forms::Label^ lblID;
    private: System::Windows::Forms::TextBox^ txtID;
    private: System::Windows::Forms::Label^ lblUser;
    private: System::Windows::Forms::TextBox^ txtUsername;
    private: System::Windows::Forms::Label^ lblPass;
    private: System::Windows::Forms::TextBox^ txtPassword;
    private: System::Windows::Forms::Label^ lblRole;
    private: System::Windows::Forms::ComboBox^ cbRole;

           // Action Buttons
    private: System::Windows::Forms::Button^ btnAdd;
    private: System::Windows::Forms::Button^ btnDelete;
    private: System::Windows::Forms::Button^ btnClear;
    private: System::Windows::Forms::Button^ btnUpdate;
    private: System::Windows::Forms::CheckBox^ chkShowPassword;

    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->gridUsers = (gcnew System::Windows::Forms::DataGridView());
               this->panelControls = (gcnew System::Windows::Forms::Panel());

               this->lblID = (gcnew System::Windows::Forms::Label());
               this->txtID = (gcnew System::Windows::Forms::TextBox());
               this->lblUser = (gcnew System::Windows::Forms::Label());
               this->txtUsername = (gcnew System::Windows::Forms::TextBox());
               this->lblPass = (gcnew System::Windows::Forms::Label());
               this->txtPassword = (gcnew System::Windows::Forms::TextBox());
               this->lblRole = (gcnew System::Windows::Forms::Label());
               this->cbRole = (gcnew System::Windows::Forms::ComboBox());

               this->btnAdd = (gcnew System::Windows::Forms::Button());
               this->btnDelete = (gcnew System::Windows::Forms::Button());
               this->btnClear = (gcnew System::Windows::Forms::Button());
               this->btnUpdate = (gcnew System::Windows::Forms::Button());
               this->chkShowPassword = (gcnew System::Windows::Forms::CheckBox());

               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridUsers))->BeginInit();
               this->panelControls->SuspendLayout();
               this->SuspendLayout();

               System::Drawing::Font^ fLabel = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
               System::Drawing::Font^ fInput = (gcnew System::Drawing::Font(L"Segoe UI", 12));

               // lblTitle
               this->lblTitle->AutoSize = true;
               this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20, System::Drawing::FontStyle::Bold));
               this->lblTitle->Location = System::Drawing::Point(20, 20);
               this->lblTitle->Text = L"Staff && User Management";

               // gridUsers (Left Side) - matches form height for clean visual balance
               this->gridUsers->AllowUserToAddRows = false;
               this->gridUsers->AllowUserToDeleteRows = false;
               this->gridUsers->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
               this->gridUsers->BackgroundColor = System::Drawing::Color::White;
               this->gridUsers->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
               this->gridUsers->Location = System::Drawing::Point(20, 70);
               this->gridUsers->ReadOnly = true;
               this->gridUsers->RowHeadersVisible = false;
               this->gridUsers->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
               this->gridUsers->Size = System::Drawing::Size(500, 480);
               this->gridUsers->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &UserForm::gridUsers_CellClick);

               // panelControls (Right Side) - made taller to accommodate Show Password row
               this->panelControls->BackColor = System::Drawing::Color::White;
               this->panelControls->Location = System::Drawing::Point(540, 70);
               this->panelControls->Size = System::Drawing::Size(320, 480);
               this->panelControls->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

               // ID label + textbox (read-only, auto-filled when row clicked)
               this->lblID->AutoSize = true; this->lblID->Font = fLabel; this->lblID->Location = System::Drawing::Point(20, 20); this->lblID->Text = L"Staff ID:";
               this->txtID->Font = fInput; this->txtID->Location = System::Drawing::Point(20, 45); this->txtID->Size = System::Drawing::Size(280, 29);
               this->txtID->ReadOnly = true;

               // Username
               this->lblUser->AutoSize = true; this->lblUser->Font = fLabel; this->lblUser->Location = System::Drawing::Point(20, 80); this->lblUser->Text = L"Username:";
               this->txtUsername->Font = fInput; this->txtUsername->Location = System::Drawing::Point(20, 105); this->txtUsername->Size = System::Drawing::Size(280, 29);

               // Password (masked by default)
               this->lblPass->AutoSize = true; this->lblPass->Font = fLabel; this->lblPass->Location = System::Drawing::Point(20, 140); this->lblPass->Text = L"Password:";
               this->txtPassword->Font = fInput; this->txtPassword->Location = System::Drawing::Point(20, 165); this->txtPassword->Size = System::Drawing::Size(280, 29);
               this->txtPassword->UseSystemPasswordChar = true;

               // Show Password checkbox - sits cleanly below the password field, above Role
               this->chkShowPassword->AutoSize = true;
               this->chkShowPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
               this->chkShowPassword->Location = System::Drawing::Point(20, 200);
               this->chkShowPassword->Text = L"Show password";
               this->chkShowPassword->UseVisualStyleBackColor = true;
               this->chkShowPassword->CheckedChanged += gcnew System::EventHandler(this, &UserForm::chkShowPassword_CheckedChanged);

               // Role - bumped down to make room for the checkbox row
               this->lblRole->AutoSize = true; this->lblRole->Font = fLabel; this->lblRole->Location = System::Drawing::Point(20, 230); this->lblRole->Text = L"Role:";
               this->cbRole->Font = fInput; this->cbRole->Location = System::Drawing::Point(20, 255); this->cbRole->Size = System::Drawing::Size(280, 29);
               this->cbRole->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
               this->cbRole->Items->Add("Admin");
               this->cbRole->Items->Add("Cashier");

               // Buttons - all bumped down 30px to keep their relative spacing under Role
               this->btnAdd->BackColor = System::Drawing::Color::SeaGreen; this->btnAdd->ForeColor = System::Drawing::Color::White;
               this->btnAdd->Font = fLabel; this->btnAdd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnAdd->Location = System::Drawing::Point(20, 310); this->btnAdd->Size = System::Drawing::Size(135, 40); this->btnAdd->Text = L"Hire (Add)";
               this->btnAdd->Click += gcnew System::EventHandler(this, &UserForm::btnAdd_Click);

               this->btnDelete->BackColor = System::Drawing::Color::IndianRed; this->btnDelete->ForeColor = System::Drawing::Color::White;
               this->btnDelete->Font = fLabel; this->btnDelete->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnDelete->Location = System::Drawing::Point(165, 310); this->btnDelete->Size = System::Drawing::Size(135, 40); this->btnDelete->Text = L"Fire (Delete)";
               this->btnDelete->Click += gcnew System::EventHandler(this, &UserForm::btnDelete_Click);

               this->btnUpdate->BackColor = System::Drawing::Color::DodgerBlue;
               this->btnUpdate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnUpdate->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
               this->btnUpdate->ForeColor = System::Drawing::Color::White;
               this->btnUpdate->Location = System::Drawing::Point(20, 355);
               this->btnUpdate->Size = System::Drawing::Size(280, 40);
               this->btnUpdate->Text = L"Update Selected";
               this->btnUpdate->UseVisualStyleBackColor = false;
               this->btnUpdate->Click += gcnew System::EventHandler(this, &UserForm::btnUpdate_Click);

               this->btnClear->BackColor = System::Drawing::Color::Gray;
               this->btnClear->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnClear->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
               this->btnClear->ForeColor = System::Drawing::Color::White;
               this->btnClear->Location = System::Drawing::Point(20, 410);
               this->btnClear->Size = System::Drawing::Size(280, 32);
               this->btnClear->Text = L"Clear Form";
               this->btnClear->UseVisualStyleBackColor = false;
               this->btnClear->Click += gcnew System::EventHandler(this, &UserForm::btnClear_Click);

               // Add ALL controls to panel - the previous version was missing chkShowPassword,
               // which is why it never appeared regardless of where we placed it.
               this->panelControls->Controls->Add(this->lblID); this->panelControls->Controls->Add(this->txtID);
               this->panelControls->Controls->Add(this->lblUser); this->panelControls->Controls->Add(this->txtUsername);
               this->panelControls->Controls->Add(this->lblPass); this->panelControls->Controls->Add(this->txtPassword);
               this->panelControls->Controls->Add(this->chkShowPassword);
               this->panelControls->Controls->Add(this->lblRole); this->panelControls->Controls->Add(this->cbRole);
               this->panelControls->Controls->Add(this->btnAdd); this->panelControls->Controls->Add(this->btnDelete);
               this->panelControls->Controls->Add(this->btnUpdate); this->panelControls->Controls->Add(this->btnClear);

               // Form setup - height grew to 570 to fit the now-taller right panel
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->BackColor = System::Drawing::Color::WhiteSmoke;
               this->ClientSize = System::Drawing::Size(880, 570);
               this->Controls->Add(this->panelControls);
               this->Controls->Add(this->gridUsers);
               this->Controls->Add(this->lblTitle);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->MaximizeBox = false;
               this->Name = L"UserForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"Staff & User Management";
               this->Load += gcnew System::EventHandler(this, &UserForm::UserForm_Load);

               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridUsers))->EndInit();
               this->panelControls->ResumeLayout(false);
               this->panelControls->PerformLayout();
               this->ResumeLayout(false);
               this->PerformLayout();
           }
#pragma endregion

    private: System::Void UserForm_Load(System::Object^ sender, System::EventArgs^ e);
    private: System::Void gridUsers_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
    private: System::Void btnAdd_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnDelete_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnUpdate_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnClear_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void chkShowPassword_CheckedChanged(System::Object^ sender, System::EventArgs^ e);

           // Helper function
    private: void RefreshGrid();
    };
}