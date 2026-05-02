#pragma once
#include <msclr\marshal_cppstd.h>

namespace supermarketui {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class TransactionHistoryForm : public System::Windows::Forms::Form
    {
    public:
        TransactionHistoryForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~TransactionHistoryForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::DataGridView^ gridHistory;
    private: System::Windows::Forms::Label^ lblSearch;
    private: System::Windows::Forms::TextBox^ txtSearchID;
    private: System::Windows::Forms::Button^ btnSearch;
    private: System::Windows::Forms::Button^ btnRefresh;
    private: System::Windows::Forms::Button^ btnViewReceipt;
    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->gridHistory = (gcnew System::Windows::Forms::DataGridView());
               this->lblSearch = (gcnew System::Windows::Forms::Label());
               this->txtSearchID = (gcnew System::Windows::Forms::TextBox());
               this->btnSearch = (gcnew System::Windows::Forms::Button());
               this->btnRefresh = (gcnew System::Windows::Forms::Button());
               this->btnViewReceipt = (gcnew System::Windows::Forms::Button());

               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridHistory))->BeginInit();
               this->SuspendLayout();

               // lblTitle
               this->lblTitle->AutoSize = true;
               this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20, System::Drawing::FontStyle::Bold));
               this->lblTitle->Location = System::Drawing::Point(15, 20);
               this->lblTitle->Name = L"lblTitle";
               this->lblTitle->Size = System::Drawing::Size(270, 37);
               this->lblTitle->Text = L"Transaction History";

               // lblSearch
               this->lblSearch->AutoSize = true;
               this->lblSearch->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->lblSearch->Location = System::Drawing::Point(412, 32);
               this->lblSearch->Name = L"lblSearch";
               this->lblSearch->Size = System::Drawing::Size(100, 21);
               this->lblSearch->Text = L"Search by ID:";

               // txtSearchID
               this->txtSearchID->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->txtSearchID->Location = System::Drawing::Point(510, 27);
               this->txtSearchID->Name = L"txtSearchID";
               this->txtSearchID->Size = System::Drawing::Size(100, 29);

               // btnSearch
               this->btnSearch->BackColor = System::Drawing::Color::DodgerBlue;
               this->btnSearch->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnSearch->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
               this->btnSearch->ForeColor = System::Drawing::Color::White;
               this->btnSearch->Location = System::Drawing::Point(620, 26);
               this->btnSearch->Name = L"btnSearch";
               this->btnSearch->Size = System::Drawing::Size(80, 31);
               this->btnSearch->Text = L"Search";
               this->btnSearch->UseVisualStyleBackColor = false;
               this->btnSearch->Click += gcnew System::EventHandler(this, &TransactionHistoryForm::btnSearch_Click);

               // btnRefresh
               this->btnRefresh->BackColor = System::Drawing::Color::Gray;
               this->btnRefresh->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnRefresh->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
               this->btnRefresh->ForeColor = System::Drawing::Color::White;
               this->btnRefresh->Location = System::Drawing::Point(710, 26);
               this->btnRefresh->Name = L"btnRefresh";
               this->btnRefresh->Size = System::Drawing::Size(80, 31);
               this->btnRefresh->Text = L"Reset";
               this->btnRefresh->UseVisualStyleBackColor = false;
               this->btnRefresh->Click += gcnew System::EventHandler(this, &TransactionHistoryForm::btnRefresh_Click);

               // btnViewReceipt - opens ReceiptForm for the currently-selected row
               this->btnViewReceipt->BackColor = System::Drawing::Color::SeaGreen;
               this->btnViewReceipt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnViewReceipt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
               this->btnViewReceipt->ForeColor = System::Drawing::Color::White;
               this->btnViewReceipt->Location = System::Drawing::Point(279, 29);
               this->btnViewReceipt->Name = L"btnViewReceipt";
               this->btnViewReceipt->Size = System::Drawing::Size(110, 30);
               this->btnViewReceipt->Text = L"View Receipt";
               this->btnViewReceipt->UseVisualStyleBackColor = false;
               this->btnViewReceipt->Click += gcnew System::EventHandler(this, &TransactionHistoryForm::btnViewReceipt_Click);

               // gridHistory
               this->gridHistory->AllowUserToAddRows = false;
               this->gridHistory->AllowUserToDeleteRows = false;
               this->gridHistory->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
               this->gridHistory->BackgroundColor = System::Drawing::Color::White;
               this->gridHistory->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
               this->gridHistory->Location = System::Drawing::Point(20, 80);
               this->gridHistory->Name = L"gridHistory";
               this->gridHistory->ReadOnly = true;
               this->gridHistory->RowHeadersVisible = false;
               this->gridHistory->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
               this->gridHistory->Size = System::Drawing::Size(770, 400);

               // Form setup
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->BackColor = System::Drawing::Color::WhiteSmoke;
               this->ClientSize = System::Drawing::Size(820, 500);
               this->Controls->Add(this->btnRefresh);
               this->Controls->Add(this->btnSearch);
               this->Controls->Add(this->btnViewReceipt);
               this->Controls->Add(this->txtSearchID);
               this->Controls->Add(this->lblSearch);
               this->Controls->Add(this->gridHistory);
               this->Controls->Add(this->lblTitle);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->MaximizeBox = false;
               this->Name = L"TransactionHistoryForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"Transaction History";
               this->Load += gcnew System::EventHandler(this, &TransactionHistoryForm::TransactionHistoryForm_Load);

               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridHistory))->EndInit();
               this->ResumeLayout(false);
               this->PerformLayout();
           }
#pragma endregion

    private: System::Void TransactionHistoryForm_Load(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnSearch_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnViewReceipt_Click(System::Object^ sender, System::EventArgs^ e);

           // Helper function to populate the grid
    private: void PopulateGrid();
    };
}
