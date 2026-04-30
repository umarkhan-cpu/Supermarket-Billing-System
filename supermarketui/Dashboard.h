#pragma once
#include "SessionManager.h"
#include "RefundForm.h"
#include "InventoryForm.h"
#include "TransactionHistoryForm.h"
#include "BillingForm.h"
#include "CategoryForm.h"
#include "UserForm.h"
#include "SalesReportForm.h"

namespace supermarketui {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class Dashboard : public System::Windows::Forms::Form
    {
    public:
        Dashboard(void)
        {
            InitializeComponent();
            SetupRoleAccess();
            // Start the session timeout timer!
            this->sessionTimer->Start();
        }

    protected:
        ~Dashboard()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Label^ lblWelcome;
    private: System::Windows::Forms::Label^ lblRole;
    private: System::Windows::Forms::Button^ btnBilling;
    private: System::Windows::Forms::Button^ btnRefunds;
    private: System::Windows::Forms::Button^ btnTransactions;
    private: System::Windows::Forms::Button^ btnInventory;
    private: System::Windows::Forms::Button^ btnCategories;
    private: System::Windows::Forms::Button^ btnUsers;
    private: System::Windows::Forms::Button^ btnSalesReport;
    private: System::Windows::Forms::Button^ btnTheme;
    private: System::Windows::Forms::Button^ btnLogout;
    private: System::Windows::Forms::Panel^ panelSidebar;
    private: System::Windows::Forms::Timer^ sessionTimer;

    private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->components = (gcnew System::ComponentModel::Container());
               this->lblWelcome = (gcnew System::Windows::Forms::Label());
               this->lblRole = (gcnew System::Windows::Forms::Label());
               this->btnBilling = (gcnew System::Windows::Forms::Button());
               this->btnRefunds = (gcnew System::Windows::Forms::Button());
               this->btnTransactions = (gcnew System::Windows::Forms::Button());
               this->btnInventory = (gcnew System::Windows::Forms::Button());
               this->btnCategories = (gcnew System::Windows::Forms::Button());
               this->btnUsers = (gcnew System::Windows::Forms::Button());
               this->btnSalesReport = (gcnew System::Windows::Forms::Button());
               this->btnTheme = (gcnew System::Windows::Forms::Button());
               this->btnLogout = (gcnew System::Windows::Forms::Button());
               this->panelSidebar = (gcnew System::Windows::Forms::Panel());
               this->sessionTimer = (gcnew System::Windows::Forms::Timer(this->components));

               this->panelSidebar->SuspendLayout();
               this->SuspendLayout();

               // panelSidebar
               this->panelSidebar->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(52)), static_cast<System::Int32>(static_cast<System::Byte>(60)));
               this->panelSidebar->Controls->Add(this->btnTheme);
               this->panelSidebar->Controls->Add(this->btnLogout);
               this->panelSidebar->Controls->Add(this->btnSalesReport);
               this->panelSidebar->Controls->Add(this->btnUsers);
               this->panelSidebar->Controls->Add(this->btnCategories);
               this->panelSidebar->Controls->Add(this->btnInventory);
               this->panelSidebar->Controls->Add(this->btnTransactions);
               this->panelSidebar->Controls->Add(this->btnRefunds);
               this->panelSidebar->Controls->Add(this->btnBilling);
               this->panelSidebar->Controls->Add(this->lblRole);
               this->panelSidebar->Controls->Add(this->lblWelcome);
               this->panelSidebar->Dock = System::Windows::Forms::DockStyle::Left;
               this->panelSidebar->Location = System::Drawing::Point(0, 0);
               this->panelSidebar->Name = L"panelSidebar";
               this->panelSidebar->Size = System::Drawing::Size(240, 600);

               // lblWelcome
               this->lblWelcome->AutoSize = true;
               this->lblWelcome->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
               this->lblWelcome->ForeColor = System::Drawing::Color::White;
               this->lblWelcome->Location = System::Drawing::Point(15, 30);
               this->lblWelcome->Name = L"lblWelcome";
               this->lblWelcome->Size = System::Drawing::Size(101, 25);
               this->lblWelcome->Text = L"Welcome!";

               // lblRole
               this->lblRole->AutoSize = true;
               this->lblRole->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
               this->lblRole->ForeColor = System::Drawing::Color::Silver;
               this->lblRole->Location = System::Drawing::Point(16, 60);
               this->lblRole->Name = L"lblRole";
               this->lblRole->Size = System::Drawing::Size(35, 19);
               this->lblRole->Text = L"Role";

               System::Drawing::Font^ btnFont = (gcnew System::Drawing::Font(L"Segoe UI", 11));
               System::Drawing::Color btnColor = System::Drawing::Color::FromArgb(45, 52, 60);

               // btnBilling
               this->btnBilling->BackColor = btnColor;
               this->btnBilling->FlatAppearance->BorderSize = 0;
               this->btnBilling->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnBilling->Font = btnFont;
               this->btnBilling->ForeColor = System::Drawing::Color::White;
               this->btnBilling->Location = System::Drawing::Point(0, 100);
               this->btnBilling->Name = L"btnBilling";
               this->btnBilling->Size = System::Drawing::Size(240, 45);
               this->btnBilling->Text = L"🛒  POS & Billing";
               this->btnBilling->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
               this->btnBilling->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
               this->btnBilling->Click += gcnew System::EventHandler(this,&Dashboard::btnBilling_Click);

               // btnRefunds
               this->btnRefunds->BackColor = btnColor;
               this->btnRefunds->FlatAppearance->BorderSize = 0;
               this->btnRefunds->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnRefunds->Font = btnFont;
               this->btnRefunds->ForeColor = System::Drawing::Color::White;
               this->btnRefunds->Location = System::Drawing::Point(0, 145);
               this->btnRefunds->Name = L"btnRefunds";
               this->btnRefunds->Size = System::Drawing::Size(240, 45);
               this->btnRefunds->Text = L"↩️  Refunds";
               this->btnRefunds->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
               this->btnRefunds->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
               this->btnRefunds->Click += gcnew System::EventHandler(this, &Dashboard::btnRefunds_Click);

               // btnTransactions
               this->btnTransactions->BackColor = btnColor;
               this->btnTransactions->FlatAppearance->BorderSize = 0;
               this->btnTransactions->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnTransactions->Font = btnFont;
               this->btnTransactions->ForeColor = System::Drawing::Color::White;
               this->btnTransactions->Location = System::Drawing::Point(0, 190);
               this->btnTransactions->Name = L"btnTransactions";
               this->btnTransactions->Size = System::Drawing::Size(240, 45);
               this->btnTransactions->Text = L"🧾  Transactions";
               this->btnTransactions->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
               this->btnTransactions->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
               this->btnTransactions->Click += gcnew System::EventHandler(this, &Dashboard::btnTransactions_Click);

               // btnInventory
               this->btnInventory->BackColor = btnColor;
               this->btnInventory->FlatAppearance->BorderSize = 0;
               this->btnInventory->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnInventory->Font = btnFont;
               this->btnInventory->ForeColor = System::Drawing::Color::White;
               this->btnInventory->Location = System::Drawing::Point(0, 235);
               this->btnInventory->Name = L"btnInventory";
               this->btnInventory->Size = System::Drawing::Size(240, 45);
               this->btnInventory->Text = L"📦  Inventory";
               this->btnInventory->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
               this->btnInventory->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
               this->btnInventory->Click += gcnew System::EventHandler(this, &Dashboard::btnInventory_Click);

               // btnCategories
               this->btnCategories->BackColor = btnColor;
               this->btnCategories->FlatAppearance->BorderSize = 0;
               this->btnCategories->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnCategories->Font = btnFont;
               this->btnCategories->ForeColor = System::Drawing::Color::White;
               this->btnCategories->Location = System::Drawing::Point(0, 280);
               this->btnCategories->Name = L"btnCategories";
               this->btnCategories->Size = System::Drawing::Size(240, 45);
               this->btnCategories->Text = L"📂  Categories";
               this->btnCategories->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
               this->btnCategories->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
               this->btnCategories->Click += gcnew System::EventHandler(this, &Dashboard::btnCategories_Click);

               // btnUsers
               this->btnUsers->BackColor = btnColor;
               this->btnUsers->FlatAppearance->BorderSize = 0;
               this->btnUsers->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnUsers->Font = btnFont;
               this->btnUsers->ForeColor = System::Drawing::Color::White;
               this->btnUsers->Location = System::Drawing::Point(0, 325);
               this->btnUsers->Name = L"btnUsers";
               this->btnUsers->Size = System::Drawing::Size(240, 45);
               this->btnUsers->Text = L"👥  User Management";
               this->btnUsers->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
               this->btnUsers->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
               this->btnUsers->Click += gcnew System::EventHandler(this, &Dashboard::btnUsers_Click);

               // btnSalesReport
               this->btnSalesReport->BackColor = btnColor;
               this->btnSalesReport->FlatAppearance->BorderSize = 0;
               this->btnSalesReport->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnSalesReport->Font = btnFont;
               this->btnSalesReport->ForeColor = System::Drawing::Color::White;
               this->btnSalesReport->Location = System::Drawing::Point(0, 370);
               this->btnSalesReport->Name = L"btnSalesReport";
               this->btnSalesReport->Size = System::Drawing::Size(240, 45);
               this->btnSalesReport->Text = L"📊  Sales Report";
               this->btnSalesReport->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
               this->btnSalesReport->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
               this->btnSalesReport->Click += gcnew System::EventHandler(this, &Dashboard::btnSalesReport_Click);

               // btnTheme
               this->btnTheme->BackColor = System::Drawing::Color::SteelBlue;
               this->btnTheme->FlatAppearance->BorderSize = 0;
               this->btnTheme->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnTheme->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
               this->btnTheme->ForeColor = System::Drawing::Color::White;
               this->btnTheme->Location = System::Drawing::Point(0, 505);
               this->btnTheme->Name = L"btnTheme";
               this->btnTheme->Size = System::Drawing::Size(240, 45);
               this->btnTheme->Text = L"☀️  Light Mode";
               this->btnTheme->Click += gcnew System::EventHandler(this, &Dashboard::btnTheme_Click);

               // btnLogout
               this->btnLogout->BackColor = System::Drawing::Color::IndianRed;
               this->btnLogout->FlatAppearance->BorderSize = 0;
               this->btnLogout->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnLogout->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
               this->btnLogout->ForeColor = System::Drawing::Color::White;
               this->btnLogout->Location = System::Drawing::Point(0, 550);
               this->btnLogout->Name = L"btnLogout";
               this->btnLogout->Size = System::Drawing::Size(240, 50);
               this->btnLogout->Text = L"Logout";
               this->btnLogout->Click += gcnew System::EventHandler(this, &Dashboard::btnLogout_Click);

               // sessionTimer (checks timeout every 5 seconds)
               this->sessionTimer->Interval = 5000;
               this->sessionTimer->Tick += gcnew System::EventHandler(this, &Dashboard::sessionTimer_Tick);

               // Dashboard Form
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->BackColor = System::Drawing::Color::WhiteSmoke;
               this->ClientSize = System::Drawing::Size(900, 600);
               this->Controls->Add(this->panelSidebar);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
               this->MaximizeBox = false;
               this->Name = L"Dashboard";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"Supermarket Dashboard";
               this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Dashboard::Dashboard_FormClosed);
               this->Click += gcnew System::EventHandler(this, &Dashboard::UpdateActivity);
               this->panelSidebar->ResumeLayout(false);
               this->panelSidebar->PerformLayout();
               this->ResumeLayout(false);
           }
#pragma endregion

           // ----- LOGIC STARTS HERE -----
    private: bool isDarkMode = true; // Default theme

           // Hide Admin buttons if a Cashier logs in
    private: void SetupRoleAccess() {
        if (SessionManager::getCurrentUser() != nullptr) {
            String^ username = gcnew String(SessionManager::getCurrentUser()->getUsername().c_str());
            String^ role = gcnew String(SessionManager::getCurrentUser()->getRole().c_str());

            this->lblWelcome->Text = "Welcome, " + username + "!";
            this->lblRole->Text = "Role: " + role;

            if (SessionManager::isCashier()) {
                this->btnInventory->Visible = false;
                this->btnCategories->Visible = false;
                this->btnUsers->Visible = false;
                this->btnSalesReport->Visible = false;
            }
        }
    }

           // This resets Umar's timeout clock whenever a button is clicked
    private: System::Void UpdateActivity(System::Object^ sender, System::EventArgs^ e) {
        SessionManager::updateActivity();
    }

           // Toggle between Dark and Light mode
    private: System::Void btnTheme_Click(System::Object^ sender, System::EventArgs^ e) {
        isDarkMode = !isDarkMode;
        SessionManager::updateActivity(); // Reset timeout

        if (isDarkMode) {
            this->BackColor = System::Drawing::Color::WhiteSmoke; // Main background
            this->panelSidebar->BackColor = System::Drawing::Color::FromArgb(45, 52, 60);
            this->lblWelcome->ForeColor = System::Drawing::Color::White;
            this->lblRole->ForeColor = System::Drawing::Color::Silver;
            this->btnTheme->Text = L"☀️  Light Mode";
            this->btnTheme->BackColor = System::Drawing::Color::SteelBlue;

            // Set buttons back to Dark Mode
            System::Drawing::Color darkBtn = System::Drawing::Color::FromArgb(45, 52, 60);
            this->btnBilling->BackColor = darkBtn; this->btnBilling->ForeColor = System::Drawing::Color::White;
            this->btnRefunds->BackColor = darkBtn; this->btnRefunds->ForeColor = System::Drawing::Color::White;
            this->btnTransactions->BackColor = darkBtn; this->btnTransactions->ForeColor = System::Drawing::Color::White;
            this->btnInventory->BackColor = darkBtn; this->btnInventory->ForeColor = System::Drawing::Color::White;
            this->btnCategories->BackColor = darkBtn; this->btnCategories->ForeColor = System::Drawing::Color::White;
            this->btnUsers->BackColor = darkBtn; this->btnUsers->ForeColor = System::Drawing::Color::White;
            this->btnSalesReport->BackColor = darkBtn; this->btnSalesReport->ForeColor = System::Drawing::Color::White;
            this->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
        }
        else {
            this->BackColor = System::Drawing::Color::White;
            this->panelSidebar->BackColor = System::Drawing::Color::LightGray;
            this->lblWelcome->ForeColor = System::Drawing::Color::Black;
            this->lblRole->ForeColor = System::Drawing::Color::DimGray;
            this->btnTheme->Text = L"🌙  Dark Mode";
            this->btnTheme->BackColor = System::Drawing::Color::DimGray;

            // Set buttons to Light Mode
            System::Drawing::Color lightBtn = System::Drawing::Color::LightGray;
            this->btnBilling->BackColor = lightBtn; this->btnBilling->ForeColor = System::Drawing::Color::Black;
            this->btnRefunds->BackColor = lightBtn; this->btnRefunds->ForeColor = System::Drawing::Color::Black;
            this->btnTransactions->BackColor = lightBtn; this->btnTransactions->ForeColor = System::Drawing::Color::Black;
            this->btnInventory->BackColor = lightBtn; this->btnInventory->ForeColor = System::Drawing::Color::Black;
            this->btnCategories->BackColor = lightBtn; this->btnCategories->ForeColor = System::Drawing::Color::Black;
            this->btnUsers->BackColor = lightBtn; this->btnUsers->ForeColor = System::Drawing::Color::Black;
            this->btnSalesReport->BackColor = lightBtn; this->btnSalesReport->ForeColor = System::Drawing::Color::Black;
            this->BackColor = System::Drawing::Color::WhiteSmoke;
        }
    }

           // The Timer that watches for Session Timeout
    private: System::Void sessionTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
        if (SessionManager::checkTimeout()) {
            this->sessionTimer->Stop();
            MessageBox::Show("You have been logged out due to inactivity.", "Session Timeout", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            SessionManager::endSession();
            Application::Restart();
        }
    }
    private: System::Void btnRefunds_Click(System::Object^ sender, System::EventArgs^ e) {
        SessionManager::updateActivity();
        RefundForm^ refundScreen = gcnew RefundForm();
        refundScreen->ShowDialog();
    }
    private: System::Void btnTransactions_Click(System::Object^ sender, System::EventArgs^ e) {
        SessionManager::updateActivity();
        TransactionHistoryForm^ historyScreen = gcnew TransactionHistoryForm();
        historyScreen->ShowDialog();
    }
    private: System::Void btnInventory_Click(System::Object^ sender, System::EventArgs^ e) {
        SessionManager::updateActivity();
        InventoryForm^ inventoryScreen = gcnew InventoryForm();
        inventoryScreen->ShowDialog();
    }

    private: System::Void btnCategories_Click(System::Object^ sender, System::EventArgs^ e) {
        SessionManager::updateActivity();
        CategoryForm^ categoryScreen = gcnew CategoryForm();
        categoryScreen->ShowDialog();
    }
    private: System::Void btnUsers_Click(System::Object^ sender, System::EventArgs^ e) {
        SessionManager::updateActivity();
        UserForm^ userScreen = gcnew UserForm();
        userScreen->ShowDialog();
    }
    private: System::Void btnSalesReport_Click(System::Object^ sender, System::EventArgs^ e) {
        SessionManager::updateActivity();
        SalesReportForm^ reportScreen = gcnew SalesReportForm();
        reportScreen->ShowDialog();
    }
    private: System::Void btnLogout_Click(System::Object^ sender, System::EventArgs^ e) {
        SessionManager::endSession();
        Application::Restart(); // Shuts down the dashboard and reopens the Login screen
    }
    private: System::Void btnBilling_Click(System::Object^ sender, System::EventArgs^ e) {
        SessionManager::updateActivity();
        BillingForm^ billing = gcnew BillingForm();
        billing->ShowDialog(); // ShowDialog freezes the dashboard until billing is closed!
    }

    private: System::Void Dashboard_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
        Application::Exit(); // Completely closes the program if they hit the red X
    }
    };
}
