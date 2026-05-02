#include "SalesReportForm.h"
#include "TransactionManagement.h"
#include "RefundManagement.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace supermarketui;

void SalesReportForm::ComputeReport() {

    // Load transaction and refund database
    TransactionManagement::loadFromFile();
    RefundManagement::loadFromFile();
    int totalTransactions = TransactionManagement::getCount();

    // Your exact logic from SalesReport.cpp!
    double totalRevenue = 0.0;
    int validSales = 0;
    int refundedItems = 0;

    for (int i = 0; i < totalTransactions; i++) {
        Transaction temp = TransactionManagement::getByIndex(i);

        // Modification by Umar (lead): To link 3 states of refund to sales report.
        // Net revenue: subtract any refunds against this transaction. This way
        // a partially-refunded transaction still contributes to revenue, but
        // only by the unrefunded portion. Fully-refunded transactions
        // contribute zero. Matches real retail accounting.
        float refunded = RefundManagement::getRefundedAmountForTransaction(temp.getID());
        totalRevenue += (temp.getTotalAmount() - refunded);

        // "Valid sales" = transactions with no refunds yet
        if (temp.getStatus() == "Completed") {
            validSales++;
        }
        else {
            // Partially or Fully Refunded - either way it's a refunded transaction
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
