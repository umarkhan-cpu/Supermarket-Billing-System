#pragma once
#include <msclr\marshal_cppstd.h>

namespace supermarketui {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class RefundForm : public System::Windows::Forms::Form
    {
    public:
        RefundForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~RefundForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::TextBox^ txtTransactionID;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::TextBox^ txtProductID;
    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::TextBox^ txtQuantity;
    private: System::Windows::Forms::Label^ label4;
    private: System::Windows::Forms::TextBox^ txtAmount;
    private: System::Windows::Forms::Label^ label5;
    private: System::Windows::Forms::ComboBox^ cmbReason;
    private: System::Windows::Forms::Button^ btnRefund;
    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->label1 = (gcnew System::Windows::Forms::Label());
               this->txtTransactionID = (gcnew System::Windows::Forms::TextBox());
               this->label2 = (gcnew System::Windows::Forms::Label());
               this->txtProductID = (gcnew System::Windows::Forms::TextBox());
               this->label3 = (gcnew System::Windows::Forms::Label());
               this->txtQuantity = (gcnew System::Windows::Forms::TextBox());
               this->label4 = (gcnew System::Windows::Forms::Label());
               this->txtAmount = (gcnew System::Windows::Forms::TextBox());
               this->label5 = (gcnew System::Windows::Forms::Label());
               this->cmbReason = (gcnew System::Windows::Forms::ComboBox());
               this->btnRefund = (gcnew System::Windows::Forms::Button());
               this->SuspendLayout();

               System::Drawing::Font^ labelFont = (gcnew System::Drawing::Font(L"Segoe UI", 11));
               System::Drawing::Font^ inputFont = (gcnew System::Drawing::Font(L"Segoe UI", 12));

               // lblTitle
               this->lblTitle->AutoSize = true;
               this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold));
               this->lblTitle->Location = System::Drawing::Point(91, 20);
               this->lblTitle->Name = L"lblTitle";
               this->lblTitle->Size = System::Drawing::Size(240, 30);
               this->lblTitle->Text = L"Process Customer Refund";

               // Transaction ID
               this->label1->AutoSize = true;
               this->label1->Font = labelFont;
               this->label1->Location = System::Drawing::Point(50, 80);
               this->label1->Text = L"Transaction ID:";

               this->txtTransactionID->Font = inputFont;
               this->txtTransactionID->Location = System::Drawing::Point(200, 75);
               this->txtTransactionID->Size = System::Drawing::Size(200, 29);

               // Product ID
               this->label2->AutoSize = true;
               this->label2->Font = labelFont;
               this->label2->Location = System::Drawing::Point(50, 130);
               this->label2->Text = L"Product ID to Return:";

               this->txtProductID->Font = inputFont;
               this->txtProductID->Location = System::Drawing::Point(200, 125);
               this->txtProductID->Size = System::Drawing::Size(200, 29);

               // Quantity
               this->label3->AutoSize = true;
               this->label3->Font = labelFont;
               this->label3->Location = System::Drawing::Point(50, 180);
               this->label3->Text = L"Quantity Returned:";

               this->txtQuantity->Font = inputFont;
               this->txtQuantity->Location = System::Drawing::Point(200, 175);
               this->txtQuantity->Size = System::Drawing::Size(200, 29);

               // Refund Amount
               this->label4->AutoSize = true;
               this->label4->Font = labelFont;
               this->label4->Location = System::Drawing::Point(50, 230);
               this->label4->Text = L"Refund Amount (Rs):";

               this->txtAmount->Font = inputFont;
               this->txtAmount->Location = System::Drawing::Point(200, 225);
               this->txtAmount->Size = System::Drawing::Size(200, 29);

               // Reason
               this->label5->AutoSize = true;
               this->label5->Font = labelFont;
               this->label5->Location = System::Drawing::Point(50, 280);
               this->label5->Text = L"Reason for Return:";

               this->cmbReason->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
               this->cmbReason->Font = inputFont;
               this->cmbReason->FormattingEnabled = true;
               this->cmbReason->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"Defective/Damaged", L"Wrong Item", L"Customer Changed Mind", L"Other" });
               this->cmbReason->Location = System::Drawing::Point(200, 275);
               this->cmbReason->Size = System::Drawing::Size(200, 29);

               // btnRefund
               this->btnRefund->BackColor = System::Drawing::Color::IndianRed;
               this->btnRefund->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnRefund->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12, System::Drawing::FontStyle::Bold));
               this->btnRefund->ForeColor = System::Drawing::Color::White;
               this->btnRefund->Location = System::Drawing::Point(130, 350);
               this->btnRefund->Size = System::Drawing::Size(240, 50);
               this->btnRefund->Text = L"Process Refund";
               this->btnRefund->UseVisualStyleBackColor = false;
               this->btnRefund->Click += gcnew System::EventHandler(this, &RefundForm::btnRefund_Click);

               // RefundForm
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->BackColor = System::Drawing::Color::WhiteSmoke;
               this->ClientSize = System::Drawing::Size(480, 450);
               this->Controls->Add(this->btnRefund);
               this->Controls->Add(this->cmbReason);
               this->Controls->Add(this->label5);
               this->Controls->Add(this->txtAmount);
               this->Controls->Add(this->label4);
               this->Controls->Add(this->txtQuantity);
               this->Controls->Add(this->label3);
               this->Controls->Add(this->txtProductID);
               this->Controls->Add(this->label2);
               this->Controls->Add(this->txtTransactionID);
               this->Controls->Add(this->label1);
               this->Controls->Add(this->lblTitle);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->MaximizeBox = false;
               this->Name = L"RefundForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"Refunds";
               this->Load += gcnew System::EventHandler(this, &RefundForm::RefundForm_Load);
               this->ResumeLayout(false);
               this->PerformLayout();

           }
#pragma endregion

    private: System::Void RefundForm_Load(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnRefund_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void RecalculateAmount(System::Object^ sender, System::EventArgs^ e);
    };
}
