#pragma once
#include <msclr\marshal_cppstd.h>

namespace supermarketui {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class BillingForm : public System::Windows::Forms::Form
    {
    public:
        BillingForm(void)
        {
            InitializeComponent();
            SetupGrid();
        }

    protected:
        ~BillingForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::DataGridView^ gridCart;
    private: System::Windows::Forms::TextBox^ txtProductID;
    private: System::Windows::Forms::TextBox^ txtQuantity;
    private: System::Windows::Forms::Button^ btnAdd;
    private: System::Windows::Forms::TextBox^ txtCoupon;
    private: System::Windows::Forms::Button^ btnApplyCoupon;
    private: System::Windows::Forms::Label^ lblSubtotal;
    private: System::Windows::Forms::Label^ lblDiscount;
    private: System::Windows::Forms::Label^ lblTax;
    private: System::Windows::Forms::Label^ lblTotal;
    private: System::Windows::Forms::Button^ btnCheckout;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Label^ label3;
    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->gridCart = (gcnew System::Windows::Forms::DataGridView());
               this->txtProductID = (gcnew System::Windows::Forms::TextBox());
               this->txtQuantity = (gcnew System::Windows::Forms::TextBox());
               this->btnAdd = (gcnew System::Windows::Forms::Button());
               this->txtCoupon = (gcnew System::Windows::Forms::TextBox());
               this->btnApplyCoupon = (gcnew System::Windows::Forms::Button());
               this->lblSubtotal = (gcnew System::Windows::Forms::Label());
               this->lblDiscount = (gcnew System::Windows::Forms::Label());
               this->lblTax = (gcnew System::Windows::Forms::Label());
               this->lblTotal = (gcnew System::Windows::Forms::Label());
               this->btnCheckout = (gcnew System::Windows::Forms::Button());
               this->label1 = (gcnew System::Windows::Forms::Label());
               this->label2 = (gcnew System::Windows::Forms::Label());
               this->label3 = (gcnew System::Windows::Forms::Label());
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridCart))->BeginInit();
               this->SuspendLayout();
               // 
               // gridCart
               // 
               this->gridCart->AllowUserToAddRows = false;
               this->gridCart->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
               this->gridCart->BackgroundColor = System::Drawing::Color::White;
               this->gridCart->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
               this->gridCart->Location = System::Drawing::Point(30, 31);
               this->gridCart->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->gridCart->Name = L"gridCart";
               this->gridCart->ReadOnly = true;
               this->gridCart->RowHeadersWidth = 62;
               this->gridCart->Size = System::Drawing::Size(900, 692);
               this->gridCart->TabIndex = 13;
               // 
               // txtProductID
               // 
               this->txtProductID->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->txtProductID->Location = System::Drawing::Point(960, 69);
               this->txtProductID->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->txtProductID->Name = L"txtProductID";
               this->txtProductID->Size = System::Drawing::Size(223, 39);
               this->txtProductID->TabIndex = 11;
               // 
               // txtQuantity
               // 
               this->txtQuantity->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->txtQuantity->Location = System::Drawing::Point(1215, 69);
               this->txtQuantity->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->txtQuantity->Name = L"txtQuantity";
               this->txtQuantity->Size = System::Drawing::Size(88, 39);
               this->txtQuantity->TabIndex = 9;
               this->txtQuantity->Text = L"1";
               // 
               // btnAdd
               // 
               this->btnAdd->BackColor = System::Drawing::Color::SeaGreen;
               this->btnAdd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnAdd->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
               this->btnAdd->ForeColor = System::Drawing::Color::White;
               this->btnAdd->Location = System::Drawing::Point(960, 138);
               this->btnAdd->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->btnAdd->Name = L"btnAdd";
               this->btnAdd->Size = System::Drawing::Size(345, 62);
               this->btnAdd->TabIndex = 8;
               this->btnAdd->Text = L"Add to Cart";
               this->btnAdd->UseVisualStyleBackColor = false;
               this->btnAdd->Click += gcnew System::EventHandler(this, &BillingForm::btnAdd_Click);
               // 
               // txtCoupon
               // 
               this->txtCoupon->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->txtCoupon->Location = System::Drawing::Point(960, 285);
               this->txtCoupon->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->txtCoupon->Name = L"txtCoupon";
               this->txtCoupon->Size = System::Drawing::Size(343, 39);
               this->txtCoupon->TabIndex = 6;
               // 
               // btnApplyCoupon
               // 
               this->btnApplyCoupon->BackColor = System::Drawing::Color::SteelBlue;
               this->btnApplyCoupon->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnApplyCoupon->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold));
               this->btnApplyCoupon->ForeColor = System::Drawing::Color::White;
               this->btnApplyCoupon->Location = System::Drawing::Point(960, 354);
               this->btnApplyCoupon->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->btnApplyCoupon->Name = L"btnApplyCoupon";
               this->btnApplyCoupon->Size = System::Drawing::Size(345, 62);
               this->btnApplyCoupon->TabIndex = 5;
               this->btnApplyCoupon->Text = L"Apply Coupon";
               this->btnApplyCoupon->UseVisualStyleBackColor = false;
               this->btnApplyCoupon->Click += gcnew System::EventHandler(this, &BillingForm::btnApplyCoupon_Click);
               // 
               // lblSubtotal
               // 
               this->lblSubtotal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->lblSubtotal->Location = System::Drawing::Point(960, 477);
               this->lblSubtotal->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
               this->lblSubtotal->Name = L"lblSubtotal";
               this->lblSubtotal->Size = System::Drawing::Size(345, 38);
               this->lblSubtotal->TabIndex = 4;
               this->lblSubtotal->Text = L"Subtotal: Rs. 0.00";
               // 
               // lblDiscount
               // 
               this->lblDiscount->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->lblDiscount->ForeColor = System::Drawing::Color::Green;
               this->lblDiscount->Location = System::Drawing::Point(960, 523);
               this->lblDiscount->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
               this->lblDiscount->Name = L"lblDiscount";
               this->lblDiscount->Size = System::Drawing::Size(345, 38);
               this->lblDiscount->TabIndex = 3;
               this->lblDiscount->Text = L"Discount: -Rs. 0.00";
               // 
               // lblTax
               // 
               this->lblTax->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               this->lblTax->Location = System::Drawing::Point(960, 569);
               this->lblTax->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
               this->lblTax->Name = L"lblTax";
               this->lblTax->Size = System::Drawing::Size(345, 38);
               this->lblTax->TabIndex = 2;
               this->lblTax->Text = L"Tax (5%): Rs. 0.00";
               // 
               // lblTotal
               // 
               this->lblTotal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 16, System::Drawing::FontStyle::Bold));
               this->lblTotal->ForeColor = System::Drawing::Color::DarkRed;
               this->lblTotal->Location = System::Drawing::Point(960, 615);
               this->lblTotal->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
               this->lblTotal->Name = L"lblTotal";
               this->lblTotal->Size = System::Drawing::Size(345, 54);
               this->lblTotal->TabIndex = 1;
               this->lblTotal->Text = L"Total: Rs. 0.00";
               this->lblTotal->Click += gcnew System::EventHandler(this, &BillingForm::lblTotal_Click);
               // 
               // btnCheckout
               // 
               this->btnCheckout->BackColor = System::Drawing::Color::DarkOrange;
               this->btnCheckout->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnCheckout->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14, System::Drawing::FontStyle::Bold));
               this->btnCheckout->ForeColor = System::Drawing::Color::White;
               this->btnCheckout->Location = System::Drawing::Point(960, 692);
               this->btnCheckout->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->btnCheckout->Name = L"btnCheckout";
               this->btnCheckout->Size = System::Drawing::Size(345, 92);
               this->btnCheckout->TabIndex = 0;
               this->btnCheckout->Text = L"Checkout";
               this->btnCheckout->UseVisualStyleBackColor = false;
               this->btnCheckout->Click += gcnew System::EventHandler(this, &BillingForm::btnCheckout_Click);
               // 
               // label1
               // 
               this->label1->AutoSize = true;
               this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
               this->label1->Location = System::Drawing::Point(960, 31);
               this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
               this->label1->Name = L"label1";
               this->label1->Size = System::Drawing::Size(109, 28);
               this->label1->TabIndex = 12;
               this->label1->Text = L"Product ID:";
               // 
               // label2
               // 
               this->label2->AutoSize = true;
               this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
               this->label2->Location = System::Drawing::Point(1215, 31);
               this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
               this->label2->Name = L"label2";
               this->label2->Size = System::Drawing::Size(48, 28);
               this->label2->TabIndex = 10;
               this->label2->Text = L"Qty:";
               // 
               // label3
               // 
               this->label3->AutoSize = true;
               this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 10));
               this->label3->Location = System::Drawing::Point(960, 246);
               this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
               this->label3->Name = L"label3";
               this->label3->Size = System::Drawing::Size(137, 28);
               this->label3->TabIndex = 7;
               this->label3->Text = L"Coupon Code:";
               // 
               // BillingForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->BackColor = System::Drawing::Color::WhiteSmoke;
               this->ClientSize = System::Drawing::Size(1350, 831);
               this->Controls->Add(this->btnCheckout);
               this->Controls->Add(this->lblTotal);
               this->Controls->Add(this->lblTax);
               this->Controls->Add(this->lblDiscount);
               this->Controls->Add(this->lblSubtotal);
               this->Controls->Add(this->btnApplyCoupon);
               this->Controls->Add(this->txtCoupon);
               this->Controls->Add(this->label3);
               this->Controls->Add(this->btnAdd);
               this->Controls->Add(this->txtQuantity);
               this->Controls->Add(this->label2);
               this->Controls->Add(this->txtProductID);
               this->Controls->Add(this->label1);
               this->Controls->Add(this->gridCart);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
               this->MaximizeBox = false;
               this->Name = L"BillingForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"POS & Billing";
               this->Load += gcnew System::EventHandler(this, &BillingForm::BillingForm_Load);
               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridCart))->EndInit();
               this->ResumeLayout(false);
               this->PerformLayout();

           }
#pragma endregion

    private:
        double subtotal = 0.0;
        double discount = 0.0;
        double taxRate = 0.05; // 5% tax

        void SetupGrid() {
            this->gridCart->ColumnCount = 5;
            this->gridCart->Columns[0]->Name = "ID";
            this->gridCart->Columns[1]->Name = "Product Name";
            this->gridCart->Columns[2]->Name = "Price";
            this->gridCart->Columns[3]->Name = "Qty";
            this->gridCart->Columns[4]->Name = "Total";
        }

        void UpdateTotals() {
            double tax = (subtotal - discount) * taxRate;
            if (tax < 0) tax = 0;
            double grandTotal = (subtotal - discount) + tax;
            if (grandTotal < 0) grandTotal = 0;

            this->lblSubtotal->Text = "Subtotal: Rs. " + subtotal.ToString("F2");
            this->lblDiscount->Text = "Discount: -Rs. " + discount.ToString("F2");
            this->lblTax->Text = "Tax (5%): Rs. " + tax.ToString("F2");
            this->lblTotal->Text = "Total: Rs. " + grandTotal.ToString("F2");
        }

    private: System::Void BillingForm_Load(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnAdd_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnApplyCoupon_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnCheckout_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void lblTotal_Click(System::Object^ sender, System::EventArgs^ e) {
    }
};
}
