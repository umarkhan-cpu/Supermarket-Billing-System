#pragma once
#include <msclr\marshal_cppstd.h> 
#include "UserManagement.h" 

namespace supermarketui {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::Label^ lblUsername;
    private: System::Windows::Forms::Label^ lblPassword;
    private: System::Windows::Forms::TextBox^ txtUsername;
    private: System::Windows::Forms::TextBox^ txtPassword;
    private: System::Windows::Forms::Button^ btnLogin;
    private: System::Windows::Forms::Button^ btnExit;

    private:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->lblUsername = (gcnew System::Windows::Forms::Label());
            this->lblPassword = (gcnew System::Windows::Forms::Label());
            this->txtUsername = (gcnew System::Windows::Forms::TextBox());
            this->txtPassword = (gcnew System::Windows::Forms::TextBox());
            this->btnLogin = (gcnew System::Windows::Forms::Button());
            this->btnExit = (gcnew System::Windows::Forms::Button());
            this->SuspendLayout();

            // lblTitle
            this->lblTitle->AutoSize = true;
            this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold));
            this->lblTitle->Location = System::Drawing::Point(100, 30);
            this->lblTitle->Name = L"lblTitle";
            this->lblTitle->Size = System::Drawing::Size(200, 45);
            this->lblTitle->Text = L"System Login";

            // lblUsername
            this->lblUsername->AutoSize = true;
            this->lblUsername->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
            this->lblUsername->Location = System::Drawing::Point(50, 120);
            this->lblUsername->Name = L"lblUsername";
            this->lblUsername->Size = System::Drawing::Size(84, 21);
            this->lblUsername->Text = L"Username:";

            // lblPassword
            this->lblPassword->AutoSize = true;
            this->lblPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
            this->lblPassword->Location = System::Drawing::Point(50, 170);
            this->lblPassword->Name = L"lblPassword";
            this->lblPassword->Size = System::Drawing::Size(79, 21);
            this->lblPassword->Text = L"Password:";

            // txtUsername
            this->txtUsername->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
            this->txtUsername->Location = System::Drawing::Point(150, 117);
            this->txtUsername->Name = L"txtUsername";
            this->txtUsername->Size = System::Drawing::Size(200, 29);

            // txtPassword
            this->txtPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
            this->txtPassword->Location = System::Drawing::Point(150, 167);
            this->txtPassword->Name = L"txtPassword";
            this->txtPassword->PasswordChar = '*';
            this->txtPassword->Size = System::Drawing::Size(200, 29);

            // btnLogin
            this->btnLogin->BackColor = System::Drawing::Color::DodgerBlue;
            this->btnLogin->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnLogin->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
            this->btnLogin->ForeColor = System::Drawing::Color::White;
            this->btnLogin->Location = System::Drawing::Point(150, 230);
            this->btnLogin->Name = L"btnLogin";
            this->btnLogin->Size = System::Drawing::Size(90, 40);
            this->btnLogin->Text = L"Login";
            this->btnLogin->UseVisualStyleBackColor = false;
            this->btnLogin->Click += gcnew System::EventHandler(this, &MyForm::btnLogin_Click);

            // btnExit
            this->btnExit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnExit->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
            this->btnExit->Location = System::Drawing::Point(260, 230);
            this->btnExit->Name = L"btnExit";
            this->btnExit->Size = System::Drawing::Size(90, 40);
            this->btnExit->Text = L"Exit";
            this->btnExit->UseVisualStyleBackColor = true;
            this->btnExit->Click += gcnew System::EventHandler(this, &MyForm::btnExit_Click);

            // MyForm
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::WhiteSmoke;
            this->ClientSize = System::Drawing::Size(430, 330);
            this->Controls->Add(this->btnExit);
            this->Controls->Add(this->btnLogin);
            this->Controls->Add(this->txtPassword);
            this->Controls->Add(this->txtUsername);
            this->Controls->Add(this->lblPassword);
            this->Controls->Add(this->lblUsername);
            this->Controls->Add(this->lblTitle);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->Name = L"MyForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Supermarket Login";
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: System::Void btnLogin_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnExit_Click(System::Object^ sender, System::EventArgs^ e);
    };
}
