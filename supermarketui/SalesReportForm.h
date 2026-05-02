#pragma once
#include <msclr\marshal_cppstd.h>

namespace supermarketui {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class SalesReportForm : public System::Windows::Forms::Form
    {
    public:
        SalesReportForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~SalesReportForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::Panel^ panelRevenue;
    private: System::Windows::Forms::Label^ lblRevenueTitle;
    private: System::Windows::Forms::Label^ lblRevenueValue;

    private: System::Windows::Forms::Panel^ panelSales;
    private: System::Windows::Forms::Label^ lblSalesTitle;
    private: System::Windows::Forms::Label^ lblSalesValue;

    private: System::Windows::Forms::Panel^ panelRefunds;
    private: System::Windows::Forms::Label^ lblRefundsTitle;
    private: System::Windows::Forms::Label^ lblRefundsValue;

    private: System::Windows::Forms::Button^ btnRefresh;
    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->panelRevenue = (gcnew System::Windows::Forms::Panel());
               this->lblRevenueTitle = (gcnew System::Windows::Forms::Label());
               this->lblRevenueValue = (gcnew System::Windows::Forms::Label());

               this->panelSales = (gcnew System::Windows::Forms::Panel());
               this->lblSalesTitle = (gcnew System::Windows::Forms::Label());
               this->lblSalesValue = (gcnew System::Windows::Forms::Label());

               this->panelRefunds = (gcnew System::Windows::Forms::Panel());
               this->lblRefundsTitle = (gcnew System::Windows::Forms::Label());
               this->lblRefundsValue = (gcnew System::Windows::Forms::Label());

               this->btnRefresh = (gcnew System::Windows::Forms::Button());

               this->panelRevenue->SuspendLayout();
               this->panelSales->SuspendLayout();
               this->panelRefunds->SuspendLayout();
               this->SuspendLayout();

               // lblTitle
               this->lblTitle->AutoSize = true;
               this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold));
               this->lblTitle->Location = System::Drawing::Point(20, 20);
               this->lblTitle->Text = L"Financial Overview && Sales Report";

               // --- Revenue Card ---
               this->panelRevenue->BackColor = System::Drawing::Color::SeaGreen;
               this->panelRevenue->Location = System::Drawing::Point(20, 100);
               this->panelRevenue->Size = System::Drawing::Size(300, 150);
               this->panelRevenue->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

               this->lblRevenueTitle->AutoSize = true;
               this->lblRevenueTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold));
               this->lblRevenueTitle->ForeColor = System::Drawing::Color::White;
               this->lblRevenueTitle->Location = System::Drawing::Point(20, 20);
               this->lblRevenueTitle->Text = L"Total Revenue (Rs.)";

               this->lblRevenueValue->AutoSize = true;
               this->lblRevenueValue->Font = (gcnew System::Drawing::Font(L"Segoe UI", 28, System::Drawing::FontStyle::Bold));
               this->lblRevenueValue->ForeColor = System::Drawing::Color::White;
               this->lblRevenueValue->Location = System::Drawing::Point(20, 70);
               this->lblRevenueValue->Text = L"0.00";

               this->panelRevenue->Controls->Add(this->lblRevenueTitle);
               this->panelRevenue->Controls->Add(this->lblRevenueValue);

               // --- Valid Sales Card ---
               this->panelSales->BackColor = System::Drawing::Color::DodgerBlue;
               this->panelSales->Location = System::Drawing::Point(340, 100);
               this->panelSales->Size = System::Drawing::Size(300, 150);
               this->panelSales->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

               this->lblSalesTitle->AutoSize = true;
               this->lblSalesTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold));
               this->lblSalesTitle->ForeColor = System::Drawing::Color::White;
               this->lblSalesTitle->Location = System::Drawing::Point(20, 20);
               this->lblSalesTitle->Text = L"Valid Sales Processed";

               this->lblSalesValue->AutoSize = true;
               this->lblSalesValue->Font = (gcnew System::Drawing::Font(L"Segoe UI", 28, System::Drawing::FontStyle::Bold));
               this->lblSalesValue->ForeColor = System::Drawing::Color::White;
               this->lblSalesValue->Location = System::Drawing::Point(20, 70);
               this->lblSalesValue->Text = L"0";

               this->panelSales->Controls->Add(this->lblSalesTitle);
               this->panelSales->Controls->Add(this->lblSalesValue);

               // --- Refunds Card ---
               this->panelRefunds->BackColor = System::Drawing::Color::IndianRed;
               this->panelRefunds->Location = System::Drawing::Point(660, 100);
               this->panelRefunds->Size = System::Drawing::Size(300, 150);
               this->panelRefunds->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

               this->lblRefundsTitle->AutoSize = true;
               this->lblRefundsTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold));
               this->lblRefundsTitle->ForeColor = System::Drawing::Color::White;
               this->lblRefundsTitle->Location = System::Drawing::Point(20, 20);
               this->lblRefundsTitle->Text = L"Refunded Items";

               this->lblRefundsValue->AutoSize = true;
               this->lblRefundsValue->Font = (gcnew System::Drawing::Font(L"Segoe UI", 28, System::Drawing::FontStyle::Bold));
               this->lblRefundsValue->ForeColor = System::Drawing::Color::White;
               this->lblRefundsValue->Location = System::Drawing::Point(20, 70);
               this->lblRefundsValue->Text = L"0";

               this->panelRefunds->Controls->Add(this->lblRefundsTitle);
               this->panelRefunds->Controls->Add(this->lblRefundsValue);

               // --- Refresh Button ---
               this->btnRefresh->BackColor = System::Drawing::Color::DimGray;
               this->btnRefresh->ForeColor = System::Drawing::Color::White;
               this->btnRefresh->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
               this->btnRefresh->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnRefresh->Location = System::Drawing::Point(340, 280);
               this->btnRefresh->Size = System::Drawing::Size(300, 50);
               this->btnRefresh->Text = L"🔄 Generate Live Report";
               this->btnRefresh->Click += gcnew System::EventHandler(this, &SalesReportForm::btnRefresh_Click);
               this->btnRefresh->Visible = false;  // Refresh button had to be hidden due to inactivity because of the single-modal model

               // Form setup
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->BackColor = System::Drawing::Color::WhiteSmoke;
               this->ClientSize = System::Drawing::Size(980, 290);

               this->Controls->Add(this->panelRevenue);
               this->Controls->Add(this->panelSales);
               this->Controls->Add(this->panelRefunds);
               this->Controls->Add(this->btnRefresh);
               this->Controls->Add(this->lblTitle);

               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->MaximizeBox = false;
               this->Name = L"SalesReportForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"Sales Report Dashboard";
               this->Load += gcnew System::EventHandler(this, &SalesReportForm::SalesReportForm_Load);

               this->panelRevenue->ResumeLayout(false);
               this->panelRevenue->PerformLayout();
               this->panelSales->ResumeLayout(false);
               this->panelSales->PerformLayout();
               this->panelRefunds->ResumeLayout(false);
               this->panelRefunds->PerformLayout();
               this->ResumeLayout(false);
               this->PerformLayout();
           }
#pragma endregion

    private: System::Void SalesReportForm_Load(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e);

           // Core computation logic!
    private: void ComputeReport();
    };
}
