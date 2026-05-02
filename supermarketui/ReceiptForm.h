#pragma once
#include <msclr\marshal_cppstd.h>

namespace supermarketui {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class ReceiptForm : public System::Windows::Forms::Form
    {
    public:
        // The transaction ID whose receipt we're displaying.
        // Set by the constructor BEFORE InitializeComponent runs so that
        // the form load handler can look it up.
        ReceiptForm(int transactionID)
        {
            this->targetTransactionID = transactionID;
            InitializeComponent();
        }

    protected:
        ~ReceiptForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        int targetTransactionID;

        // The card panel that holds the receipt body.
        // Background color set to blue (Sale) or red (Refund) at load time.
        System::Windows::Forms::Panel^ panelReceipt;

        System::Windows::Forms::Label^ lblStoreName;
        System::Windows::Forms::Label^ lblTagline;
        System::Windows::Forms::Label^ lblHeaderInfo;     // date / cashier / txn ID
        System::Windows::Forms::Label^ lblSeparatorTop;

        // Items area: column headers + per-line item content.
        // Using a single big monospace label for clean column alignment.
        System::Windows::Forms::Label^ lblItemsHeader;
        System::Windows::Forms::Label^ lblItemsBody;

        System::Windows::Forms::Label^ lblSeparatorMid;

        System::Windows::Forms::Label^ lblSubtotal;
        System::Windows::Forms::Label^ lblDiscount;
        System::Windows::Forms::Label^ lblTax;
        System::Windows::Forms::Label^ lblGrandTotal;

        System::Windows::Forms::Label^ lblSeparatorBottom;
        System::Windows::Forms::Label^ lblFooter;

        System::Windows::Forms::Button^ btnClose;

        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->panelReceipt = (gcnew System::Windows::Forms::Panel());
            this->lblStoreName = (gcnew System::Windows::Forms::Label());
            this->lblTagline = (gcnew System::Windows::Forms::Label());
            this->lblHeaderInfo = (gcnew System::Windows::Forms::Label());
            this->lblSeparatorTop = (gcnew System::Windows::Forms::Label());
            this->lblItemsHeader = (gcnew System::Windows::Forms::Label());
            this->lblItemsBody = (gcnew System::Windows::Forms::Label());
            this->lblSeparatorMid = (gcnew System::Windows::Forms::Label());
            this->lblSubtotal = (gcnew System::Windows::Forms::Label());
            this->lblDiscount = (gcnew System::Windows::Forms::Label());
            this->lblTax = (gcnew System::Windows::Forms::Label());
            this->lblGrandTotal = (gcnew System::Windows::Forms::Label());
            this->lblSeparatorBottom = (gcnew System::Windows::Forms::Label());
            this->lblFooter = (gcnew System::Windows::Forms::Label());
            this->btnClose = (gcnew System::Windows::Forms::Button());

            this->panelReceipt->SuspendLayout();
            this->SuspendLayout();

            // Color palette - deep blue with white text and gold accents.
            // Will be overridden to red theme for refund receipts at runtime.
            System::Drawing::Color bgColor = System::Drawing::Color::FromArgb(30, 58, 138);    // deep blue
            System::Drawing::Color textColor = System::Drawing::Color::White;
            System::Drawing::Color accentColor = System::Drawing::Color::FromArgb(250, 204, 21); // amber/gold

            // Fonts - monospace for items so columns align cleanly
            System::Drawing::Font^ fStore = (gcnew System::Drawing::Font(L"Segoe UI", 22, System::Drawing::FontStyle::Bold));
            System::Drawing::Font^ fTag = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Italic));
            System::Drawing::Font^ fInfo = (gcnew System::Drawing::Font(L"Consolas", 10));
            System::Drawing::Font^ fItems = (gcnew System::Drawing::Font(L"Consolas", 11));
            System::Drawing::Font^ fItemsHead = (gcnew System::Drawing::Font(L"Consolas", 11, System::Drawing::FontStyle::Bold));
            System::Drawing::Font^ fTotalLine = (gcnew System::Drawing::Font(L"Consolas", 11));
            System::Drawing::Font^ fGrand = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold));
            System::Drawing::Font^ fFooter = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Italic));
            System::Drawing::Font^ fSep = (gcnew System::Drawing::Font(L"Consolas", 9));

            // panelReceipt - the colored card that everything sits on
            this->panelReceipt->BackColor = bgColor;
            this->panelReceipt->Location = System::Drawing::Point(30, 25);
            this->panelReceipt->Size = System::Drawing::Size(540, 660);
            this->panelReceipt->Controls->Add(this->lblStoreName);
            this->panelReceipt->Controls->Add(this->lblTagline);
            this->panelReceipt->Controls->Add(this->lblHeaderInfo);
            this->panelReceipt->Controls->Add(this->lblSeparatorTop);
            this->panelReceipt->Controls->Add(this->lblItemsHeader);
            this->panelReceipt->Controls->Add(this->lblItemsBody);
            this->panelReceipt->Controls->Add(this->lblSeparatorMid);
            this->panelReceipt->Controls->Add(this->lblSubtotal);
            this->panelReceipt->Controls->Add(this->lblDiscount);
            this->panelReceipt->Controls->Add(this->lblTax);
            this->panelReceipt->Controls->Add(this->lblGrandTotal);
            this->panelReceipt->Controls->Add(this->lblSeparatorBottom);
            this->panelReceipt->Controls->Add(this->lblFooter);

            // lblStoreName
            this->lblStoreName->AutoSize = false;
            this->lblStoreName->Size = System::Drawing::Size(540, 40);
            this->lblStoreName->Location = System::Drawing::Point(0, 25);
            this->lblStoreName->Font = fStore;
            this->lblStoreName->ForeColor = textColor;
            this->lblStoreName->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            this->lblStoreName->Text = L"FAST MART";

            // lblTagline
            this->lblTagline->AutoSize = false;
            this->lblTagline->Size = System::Drawing::Size(540, 20);
            this->lblTagline->Location = System::Drawing::Point(0, 65);
            this->lblTagline->Font = fTag;
            this->lblTagline->ForeColor = textColor;
            this->lblTagline->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            this->lblTagline->Text = L"Where convenience meets value";

            // lblHeaderInfo - filled at load time with date/cashier/txnID
            this->lblHeaderInfo->AutoSize = false;
            this->lblHeaderInfo->Size = System::Drawing::Size(490, 60);
            this->lblHeaderInfo->Location = System::Drawing::Point(25, 100);
            this->lblHeaderInfo->Font = fInfo;
            this->lblHeaderInfo->ForeColor = textColor;
            this->lblHeaderInfo->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

            // lblSeparatorTop
            this->lblSeparatorTop->AutoSize = false;
            this->lblSeparatorTop->Size = System::Drawing::Size(490, 18);
            this->lblSeparatorTop->Location = System::Drawing::Point(25, 165);
            this->lblSeparatorTop->Font = fSep;
            this->lblSeparatorTop->ForeColor = textColor;
            this->lblSeparatorTop->Text = L"================================================";

            // lblItemsHeader - column titles for the items table
            this->lblItemsHeader->AutoSize = false;
            this->lblItemsHeader->Size = System::Drawing::Size(490, 22);
            this->lblItemsHeader->Location = System::Drawing::Point(25, 188);
            this->lblItemsHeader->Font = fItemsHead;
            this->lblItemsHeader->ForeColor = textColor;
            // Header columns must EXACTLY match the positions used by
            // formatItemLine in ReceiptForm.cpp:
            //   setw(18) name + setw(5) qty + " " + setw(9) price + " " + setw(9) total
            //
            // That puts the data right-edges at columns 22 (qty), 32 (price), 42 (total).
            // The header labels are right-aligned to those same end-columns:
            //   "Qty"   ends at col 22  -> "  Qty" in cols 18-22
            //   "Price" ends at col 32  -> "    Price" in cols 24-32
            //   "Total" ends at col 42  -> "    Total" in cols 34-42
            this->lblItemsHeader->Text = L"Item                Qty     Price     Total";

            // lblItemsBody - the actual line items, set at load time
            this->lblItemsBody->AutoSize = false;
            this->lblItemsBody->Size = System::Drawing::Size(490, 220);
            this->lblItemsBody->Location = System::Drawing::Point(25, 215);
            this->lblItemsBody->Font = fItems;
            this->lblItemsBody->ForeColor = textColor;
            this->lblItemsBody->TextAlign = System::Drawing::ContentAlignment::TopLeft;

            // lblSeparatorMid
            this->lblSeparatorMid->AutoSize = false;
            this->lblSeparatorMid->Size = System::Drawing::Size(490, 18);
            this->lblSeparatorMid->Location = System::Drawing::Point(25, 440);
            this->lblSeparatorMid->Font = fSep;
            this->lblSeparatorMid->ForeColor = textColor;
            this->lblSeparatorMid->Text = L"------------------------------------------------";

            // lblSubtotal
            this->lblSubtotal->AutoSize = false;
            this->lblSubtotal->Size = System::Drawing::Size(490, 20);
            this->lblSubtotal->Location = System::Drawing::Point(25, 465);
            this->lblSubtotal->Font = fTotalLine;
            this->lblSubtotal->ForeColor = textColor;

            // lblDiscount
            this->lblDiscount->AutoSize = false;
            this->lblDiscount->Size = System::Drawing::Size(490, 20);
            this->lblDiscount->Location = System::Drawing::Point(25, 490);
            this->lblDiscount->Font = fTotalLine;
            this->lblDiscount->ForeColor = textColor;

            // lblTax
            this->lblTax->AutoSize = false;
            this->lblTax->Size = System::Drawing::Size(490, 20);
            this->lblTax->Location = System::Drawing::Point(25, 515);
            this->lblTax->Font = fTotalLine;
            this->lblTax->ForeColor = textColor;

            // lblGrandTotal - bigger and gold for emphasis
            this->lblGrandTotal->AutoSize = false;
            this->lblGrandTotal->Size = System::Drawing::Size(490, 35);
            this->lblGrandTotal->Location = System::Drawing::Point(25, 545);
            this->lblGrandTotal->Font = fGrand;
            this->lblGrandTotal->ForeColor = accentColor;
            this->lblGrandTotal->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;

            // lblSeparatorBottom
            this->lblSeparatorBottom->AutoSize = false;
            this->lblSeparatorBottom->Size = System::Drawing::Size(490, 18);
            this->lblSeparatorBottom->Location = System::Drawing::Point(25, 590);
            this->lblSeparatorBottom->Font = fSep;
            this->lblSeparatorBottom->ForeColor = textColor;
            this->lblSeparatorBottom->Text = L"================================================";

            // lblFooter
            this->lblFooter->AutoSize = false;
            this->lblFooter->Size = System::Drawing::Size(540, 25);
            this->lblFooter->Location = System::Drawing::Point(0, 615);
            this->lblFooter->Font = fFooter;
            this->lblFooter->ForeColor = textColor;
            this->lblFooter->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            this->lblFooter->Text = L"Thank you for shopping with us!";

            // btnClose - sits below the receipt panel on the form background
            this->btnClose->BackColor = System::Drawing::Color::Gray;
            this->btnClose->ForeColor = System::Drawing::Color::White;
            this->btnClose->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnClose->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
            this->btnClose->Location = System::Drawing::Point(220, 705);
            this->btnClose->Size = System::Drawing::Size(160, 40);
            this->btnClose->Text = L"Close";
            this->btnClose->UseVisualStyleBackColor = false;
            this->btnClose->Click += gcnew System::EventHandler(this, &ReceiptForm::btnClose_Click);

            // ReceiptForm
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::Color::WhiteSmoke;
            this->ClientSize = System::Drawing::Size(600, 760);
            this->Controls->Add(this->panelReceipt);
            this->Controls->Add(this->btnClose);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
            this->AutoScroll = true;
            this->Name = L"ReceiptForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Receipt";
            this->Load += gcnew System::EventHandler(this, &ReceiptForm::ReceiptForm_Load);

            this->panelReceipt->ResumeLayout(false);
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: System::Void ReceiptForm_Load(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e);
    };
}