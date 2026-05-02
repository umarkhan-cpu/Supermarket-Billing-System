#pragma once
#include <msclr\marshal_cppstd.h>

namespace supermarketui {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class SearchForm : public System::Windows::Forms::Form
    {
    public:
        SearchForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~SearchForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Label^ lblTitle;
    private: System::Windows::Forms::DataGridView^ gridProducts;
    private: System::Windows::Forms::Panel^ panelControls;

           // Radio buttons - filter mode selector
    private: System::Windows::Forms::Label^ lblMode;
    private: System::Windows::Forms::RadioButton^ rbName;
    private: System::Windows::Forms::RadioButton^ rbCategory;
    private: System::Windows::Forms::RadioButton^ rbPrice;

           // Inputs
    private: System::Windows::Forms::Label^ lblValue1;
    private: System::Windows::Forms::TextBox^ txtValue1;
    private: System::Windows::Forms::Label^ lblValue2;
    private: System::Windows::Forms::TextBox^ txtValue2;

           // In-stock checkbox (combines with any filter)
    private: System::Windows::Forms::CheckBox^ chkInStock;

           // Buttons
    private: System::Windows::Forms::Button^ btnSearch;
    private: System::Windows::Forms::Button^ btnReset;

    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->lblTitle = (gcnew System::Windows::Forms::Label());
               this->gridProducts = (gcnew System::Windows::Forms::DataGridView());
               this->panelControls = (gcnew System::Windows::Forms::Panel());

               this->lblMode = (gcnew System::Windows::Forms::Label());
               this->rbName = (gcnew System::Windows::Forms::RadioButton());
               this->rbCategory = (gcnew System::Windows::Forms::RadioButton());
               this->rbPrice = (gcnew System::Windows::Forms::RadioButton());

               this->lblValue1 = (gcnew System::Windows::Forms::Label());
               this->txtValue1 = (gcnew System::Windows::Forms::TextBox());
               this->lblValue2 = (gcnew System::Windows::Forms::Label());
               this->txtValue2 = (gcnew System::Windows::Forms::TextBox());

               this->chkInStock = (gcnew System::Windows::Forms::CheckBox());

               this->btnSearch = (gcnew System::Windows::Forms::Button());
               this->btnReset = (gcnew System::Windows::Forms::Button());

               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridProducts))->BeginInit();
               this->panelControls->SuspendLayout();
               this->SuspendLayout();

               System::Drawing::Font^ fLabel = (gcnew System::Drawing::Font(L"Segoe UI", 11, System::Drawing::FontStyle::Bold));
               System::Drawing::Font^ fInput = (gcnew System::Drawing::Font(L"Segoe UI", 12));
               System::Drawing::Font^ fRadio = (gcnew System::Drawing::Font(L"Segoe UI", 11));

               // lblTitle
               this->lblTitle->AutoSize = true;
               this->lblTitle->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20, System::Drawing::FontStyle::Bold));
               this->lblTitle->Location = System::Drawing::Point(20, 20);
               this->lblTitle->Text = L"Search && Filter Products";

               // gridProducts
               this->gridProducts->AllowUserToAddRows = false;
               this->gridProducts->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
               this->gridProducts->Location = System::Drawing::Point(20, 80);
               this->gridProducts->Name = L"gridProducts";
               this->gridProducts->RowTemplate->Height = 28;
               this->gridProducts->Size = System::Drawing::Size(560, 460);
               this->gridProducts->ReadOnly = true;
               this->gridProducts->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
               this->gridProducts->MultiSelect = false;

               // panelControls
               this->panelControls->BackColor = System::Drawing::Color::White;
               this->panelControls->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
               this->panelControls->Controls->Add(this->lblMode);
               this->panelControls->Controls->Add(this->rbName);
               this->panelControls->Controls->Add(this->rbCategory);
               this->panelControls->Controls->Add(this->rbPrice);
               this->panelControls->Controls->Add(this->lblValue1);
               this->panelControls->Controls->Add(this->txtValue1);
               this->panelControls->Controls->Add(this->lblValue2);
               this->panelControls->Controls->Add(this->txtValue2);
               this->panelControls->Controls->Add(this->chkInStock);
               this->panelControls->Controls->Add(this->btnSearch);
               this->panelControls->Controls->Add(this->btnReset);
               this->panelControls->Location = System::Drawing::Point(600, 80);
               this->panelControls->Name = L"panelControls";
               this->panelControls->Size = System::Drawing::Size(320, 460);

               // lblMode
               this->lblMode->AutoSize = true;
               this->lblMode->Font = fLabel;
               this->lblMode->Location = System::Drawing::Point(20, 20);
               this->lblMode->Text = L"Filter by:";

               // rbName
               this->rbName->AutoSize = true;
               this->rbName->Checked = true;
               this->rbName->Font = fRadio;
               this->rbName->Location = System::Drawing::Point(20, 50);
               this->rbName->Text = L"Product Name";
               this->rbName->CheckedChanged += gcnew System::EventHandler(this, &SearchForm::rbMode_CheckedChanged);

               // rbCategory
               this->rbCategory->AutoSize = true;
               this->rbCategory->Font = fRadio;
               this->rbCategory->Location = System::Drawing::Point(20, 80);
               this->rbCategory->Text = L"Category Name";
               this->rbCategory->CheckedChanged += gcnew System::EventHandler(this, &SearchForm::rbMode_CheckedChanged);

               // rbPrice
               this->rbPrice->AutoSize = true;
               this->rbPrice->Font = fRadio;
               this->rbPrice->Location = System::Drawing::Point(20, 110);
               this->rbPrice->Text = L"Price Range";
               this->rbPrice->CheckedChanged += gcnew System::EventHandler(this, &SearchForm::rbMode_CheckedChanged);

               // lblValue1
               this->lblValue1->AutoSize = true;
               this->lblValue1->Font = fLabel;
               this->lblValue1->Location = System::Drawing::Point(20, 155);
               this->lblValue1->Text = L"Name contains:";

               // txtValue1
               this->txtValue1->Font = fInput;
               this->txtValue1->Location = System::Drawing::Point(20, 180);
               this->txtValue1->Size = System::Drawing::Size(270, 29);

               // lblValue2 (only used for price range upper bound)
               this->lblValue2->AutoSize = true;
               this->lblValue2->Font = fLabel;
               this->lblValue2->Location = System::Drawing::Point(20, 220);
               this->lblValue2->Text = L"Max Price:";
               this->lblValue2->Visible = false;

               // txtValue2
               this->txtValue2->Font = fInput;
               this->txtValue2->Location = System::Drawing::Point(20, 245);
               this->txtValue2->Size = System::Drawing::Size(270, 29);
               this->txtValue2->Visible = false;

               // chkInStock
               this->chkInStock->AutoSize = true;
               this->chkInStock->Font = fRadio;
               this->chkInStock->Location = System::Drawing::Point(20, 295);
               this->chkInStock->Text = L"Only show in-stock items";

               // btnSearch
               this->btnSearch->BackColor = System::Drawing::Color::SteelBlue;
               this->btnSearch->ForeColor = System::Drawing::Color::White;
               this->btnSearch->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnSearch->Font = fInput;
               this->btnSearch->Location = System::Drawing::Point(20, 340);
               this->btnSearch->Size = System::Drawing::Size(270, 40);
               this->btnSearch->Text = L"Search";
               this->btnSearch->UseVisualStyleBackColor = false;
               this->btnSearch->Click += gcnew System::EventHandler(this, &SearchForm::btnSearch_Click);

               // btnReset
               this->btnReset->BackColor = System::Drawing::Color::Gray;
               this->btnReset->ForeColor = System::Drawing::Color::White;
               this->btnReset->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
               this->btnReset->Font = fInput;
               this->btnReset->Location = System::Drawing::Point(20, 390);
               this->btnReset->Size = System::Drawing::Size(270, 40);
               this->btnReset->Text = L"Reset / Show All";
               this->btnReset->UseVisualStyleBackColor = false;
               this->btnReset->Click += gcnew System::EventHandler(this, &SearchForm::btnReset_Click);

               // SearchForm
               this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->BackColor = System::Drawing::Color::WhiteSmoke;
               this->ClientSize = System::Drawing::Size(960, 580);
               this->Controls->Add(this->lblTitle);
               this->Controls->Add(this->gridProducts);
               this->Controls->Add(this->panelControls);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
               this->AutoScroll = true;
               this->MaximizeBox = false;
               this->Name = L"SearchForm";
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
               this->Text = L"Search & Filter Products";
               this->Load += gcnew System::EventHandler(this, &SearchForm::SearchForm_Load);

               (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gridProducts))->EndInit();
               this->panelControls->ResumeLayout(false);
               this->panelControls->PerformLayout();
               this->ResumeLayout(false);
               this->PerformLayout();
           }
#pragma endregion

           // Method declarations - implemented in SearchForm.cpp
    private: void EnsureColumns();
    private: void ShowAllProducts();
    private: System::Void SearchForm_Load(System::Object^ sender, System::EventArgs^ e);
    private: System::Void rbMode_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnSearch_Click(System::Object^ sender, System::EventArgs^ e);
    private: System::Void btnReset_Click(System::Object^ sender, System::EventArgs^ e);
    };
}