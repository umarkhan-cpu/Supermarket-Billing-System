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

        // Branded header (top blue band)
    private: System::Windows::Forms::Panel^ panelHeader;
    private: System::Windows::Forms::Label^ lblBrand;
    private: System::Windows::Forms::Label^ lblTagline;

           // Welcome / login section (the white area below the header)
    private: System::Windows::Forms::Label^ lblWelcome;
    private: System::Windows::Forms::Label^ lblSubtitle;
    private: System::Windows::Forms::Label^ lblUsername;
    private: System::Windows::Forms::Label^ lblPassword;
    private: System::Windows::Forms::TextBox^ txtUsername;
    private: System::Windows::Forms::TextBox^ txtPassword;
    private: System::Windows::Forms::CheckBox^ chkShowPassword;
    private: System::Windows::Forms::Button^ btnLogin;
    private: System::Windows::Forms::Button^ btnExit;
    private: System::Windows::Forms::Label^ lblFooter;

    private:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->panelHeader = (gcnew System::Windows::Forms::Panel());
            this->lblBrand = (gcnew System::Windows::Forms::Label());
            this->lblTagline = (gcnew System::Windows::Forms::Label());
            this->lblWelcome = (gcnew System::Windows::Forms::Label());
            this->lblSubtitle = (gcnew System::Windows::Forms::Label());
            this->lblUsername = (gcnew System::Windows::Forms::Label());
            this->lblPassword = (gcnew System::Windows::Forms::Label());
            this->txtUsername = (gcnew System::Windows::Forms::TextBox());
            this->txtPassword = (gcnew System::Windows::Forms::TextBox());
            this->chkShowPassword = (gcnew System::Windows::Forms::CheckBox());
            this->btnLogin = (gcnew System::Windows::Forms::Button());
            this->btnExit = (gcnew System::Windows::Forms::Button());
            this->lblFooter = (gcnew System::Windows::Forms::Label());
            this->panelHeader->SuspendLayout();
            this->SuspendLayout();

            // Color palette - deep blue header to match the receipt's branding,
            // gold accent for the tagline, neutrals for the form body.
            System::Drawing::Color brandBlue = System::Drawing::Color::FromArgb(30, 58, 138);
            System::Drawing::Color brandGold = System::Drawing::Color::FromArgb(250, 204, 21);

            // panelHeader - top branded band
            this->panelHeader->BackColor = brandBlue;
            this->panelHeader->Location = System::Drawing::Point(0, 0);
            this->panelHeader->Size = System::Drawing::Size(540, 130);
            this->panelHeader->Controls->Add(this->lblBrand);
            this->panelHeader->Controls->Add(this->lblTagline);

            // lblBrand - the FAST MART logo text
            this->lblBrand->AutoSize = false;
            this->lblBrand->Size = System::Drawing::Size(540, 60);
            this->lblBrand->Location = System::Drawing::Point(0, 30);
            this->lblBrand->Font = (gcnew System::Drawing::Font(L"Segoe UI", 32, System::Drawing::FontStyle::Bold));
            this->lblBrand->ForeColor = System::Drawing::Color::White;
            this->lblBrand->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            this->lblBrand->Text = L"FAST MART";

            // lblTagline
            this->lblTagline->AutoSize = false;
            this->lblTagline->Size = System::Drawing::Size(540, 25);
            this->lblTagline->Location = System::Drawing::Point(0, 90);
            this->lblTagline->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Italic));
            this->lblTagline->ForeColor = brandGold;
            this->lblTagline->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            this->lblTagline->Text = L"Where convenience meets value";

            // lblWelcome - greeting in the form body
            this->lblWelcome->AutoSize = false;
            this->lblWelcome->Size = System::Drawing::Size(540, 30);
            this->lblWelcome->Location = System::Drawing::Point(0, 155);
            this->lblWelcome->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold));
            this->lblWelcome->ForeColor = System::Drawing::Color::FromArgb(40, 40, 40);
            this->lblWelcome->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            this->lblWelcome->Text = L"Welcome Back";

            // lblSubtitle
            this->lblSubtitle->AutoSize = false;
            this->lblSubtitle->Size = System::Drawing::Size(540, 22);
            this->lblSubtitle->Location = System::Drawing::Point(0, 188);
            this->lblSubtitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
            this->lblSubtitle->ForeColor = System::Drawing::Color::Gray;
            this->lblSubtitle->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            this->lblSubtitle->Text = L"Sign in to your Admin or Cashier account";

            // lblUsername
            this->lblUsername->AutoSize = true;
            this->lblUsername->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
            this->lblUsername->Location = System::Drawing::Point(120, 240);
            this->lblUsername->Text = L"Username";

            // txtUsername
            this->txtUsername->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
            this->txtUsername->Location = System::Drawing::Point(120, 265);
            this->txtUsername->Size = System::Drawing::Size(300, 29);
            this->txtUsername->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

            // lblPassword
            this->lblPassword->AutoSize = true;
            this->lblPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
            this->lblPassword->Location = System::Drawing::Point(120, 310);
            this->lblPassword->Text = L"Password";

            // txtPassword
            this->txtPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
            this->txtPassword->Location = System::Drawing::Point(120, 335);
            this->txtPassword->PasswordChar = '*';
            this->txtPassword->Size = System::Drawing::Size(300, 29);
            this->txtPassword->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

            // chkShowPassword
            this->chkShowPassword->AutoSize = true;
            this->chkShowPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9));
            this->chkShowPassword->Location = System::Drawing::Point(120, 370);
            this->chkShowPassword->Text = L"Show password";
            this->chkShowPassword->UseVisualStyleBackColor = true;
            this->chkShowPassword->CheckedChanged += gcnew System::EventHandler(this, &MyForm::chkShowPassword_CheckedChanged);

            // btnLogin - primary action in brand color
            this->btnLogin->BackColor = brandBlue;
            this->btnLogin->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnLogin->FlatAppearance->BorderSize = 0;
            this->btnLogin->Font = (gcnew System::Drawing::Font(L"Segoe UI", 13, System::Drawing::FontStyle::Bold));
            this->btnLogin->ForeColor = System::Drawing::Color::White;
            this->btnLogin->Location = System::Drawing::Point(120, 410);
            this->btnLogin->Size = System::Drawing::Size(195, 45);
            this->btnLogin->Text = L"Sign In";
            this->btnLogin->UseVisualStyleBackColor = false;
            this->btnLogin->Click += gcnew System::EventHandler(this, &MyForm::btnLogin_Click);

            // btnExit - secondary, neutral grey
            this->btnExit->BackColor = System::Drawing::Color::FromArgb(229, 231, 235);
            this->btnExit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnExit->FlatAppearance->BorderSize = 0;
            this->btnExit->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
            this->btnExit->ForeColor = System::Drawing::Color::FromArgb(60, 60, 60);
            this->btnExit->Location = System::Drawing::Point(325, 410);
            this->btnExit->Size = System::Drawing::Size(95, 45);
            this->btnExit->Text = L"Exit";
            this->btnExit->UseVisualStyleBackColor = false;
            this->btnExit->Click += gcnew System::EventHandler(this, &MyForm::btnExit_Click);

            // LoginForm
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::White;
            this->ClientSize = System::Drawing::Size(540, 510);
            this->Controls->Add(this->panelHeader);
            this->Controls->Add(this->lblWelcome);
            this->Controls->Add(this->lblSubtitle);
            this->Controls->Add(this->lblUsername);
            this->Controls->Add(this->txtUsername);
            this->Controls->Add(this->lblPassword);
            this->Controls->Add(this->txtPassword);
            this->Controls->Add(this->chkShowPassword);
            this->Controls->Add(this->btnLogin);
            this->Controls->Add(this->btnExit);
            this->Controls->Add(this->lblFooter);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->Name = L"MyForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Login";
            this->panelHeader->ResumeLayout(false);
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: System::Void btnLogin_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnExit_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void chkShowPassword_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
    };
}