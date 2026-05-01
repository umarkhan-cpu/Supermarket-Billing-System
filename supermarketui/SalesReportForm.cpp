#include "SalesReportForm.h"
#include "TransactionManagement.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace supermarketui;

void SalesReportForm::ComputeReport() {

    // Load Farda's database
    TransactionManagement::loadFromFile();
    int totalTransactions = TransactionManagement::getCount();

    // Your exact logic from SalesReport.cpp!
    double totalRevenue = 0.0;
    int validSales = 0;
    int refundedItems = 0;

    for (int i = 0; i < totalTransactions; i++) {
        Transaction temp = TransactionManagement::getByIndex(i);

        // Count valid revenue
        if (temp.getStatus() != "Refunded") {
            totalRevenue += temp.getTotalAmount();
            validSales++;
        }
        else {
            refundedItems++;
        }
    }

    // Push the answers to the visual dashboard labels!
    lblRevenueValue->Text = totalRevenue.ToString("F2");
    lblSalesValue->Text = validSales.ToString();
    lblRefundsValue->Text = refundedItems.ToString();
}

System::Void SalesReportForm::SalesReportForm_Load(System::Object^ sender, System::EventArgs^ e) {
    // Generate the report the instant the screen opens
    ComputeReport();
}

System::Void SalesReportForm::btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
    // Re-generate the report if someone clicks the button
    ComputeReport();
}
