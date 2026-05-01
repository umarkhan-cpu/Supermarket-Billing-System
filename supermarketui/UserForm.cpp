#include "UserForm.h"
#include "UserManagement.h"
#include <fstream>
#include <string>
#include <sstream>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;
using namespace supermarketui;

// --- Helper: Refreshes the Table ---
void UserForm::RefreshGrid() {
    gridUsers->Rows->Clear();

    if (gridUsers->Columns->Count == 0) {
        gridUsers->Columns->Add("ID", "Staff ID");
        gridUsers->Columns->Add("User", "Username");
        gridUsers->Columns->Add("Role", "Role");
    }

    std::ifstream file(R"(C:\Users\mahno\OneDrive\Documents\GitHub\Supermarket-Billing-System\Data\users.txt)");
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string id, user, passHash, role;

        std::getline(ss, id, ',');
        std::getline(ss, user, ',');
        std::getline(ss, passHash, ',');
        std::getline(ss, role, ',');

        gridUsers->Rows->Add(
            msclr::interop::marshal_as<String^>(id),
            msclr::interop::marshal_as<String^>(user),
            msclr::interop::marshal_as<String^>(role)
        );
    }
    file.close();
}

// --- Screen Load ---
System::Void UserForm::UserForm_Load(System::Object^ sender, System::EventArgs^ e) {
    RefreshGrid();
    cbRole->SelectedIndex = 1; // Default to Cashier
}

// --- Cell Click: Auto-fill the form! ---
System::Void UserForm::gridUsers_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
    if (e->RowIndex >= 0) {
        DataGridViewRow^ row = gridUsers->Rows[e->RowIndex];
        txtID->Text = row->Cells[0]->Value->ToString();
        txtUsername->Text = row->Cells[1]->Value->ToString();
        txtPassword->Text = ""; // Leave blank for security
        cbRole->Text = row->Cells[2]->Value->ToString();
    }
}

// --- Add / Hire User ---
System::Void UserForm::btnAdd_Click(System::Object^ sender, System::EventArgs^ e) {
    if (txtUsername->Text == "" || txtPassword->Text == "" || cbRole->Text == "") {
        MessageBox::Show("Please fill out all fields.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
    }

    std::string newUser = msclr::interop::marshal_as<std::string>(txtUsername->Text);
    std::string newPass = msclr::interop::marshal_as<std::string>(txtPassword->Text);
    std::string newRole = msclr::interop::marshal_as<std::string>(cbRole->Text);

    // 1. Secure the password using Farda's hashing algorithm!
    std::string hashedPass = UserManagement::hashedpass(newPass);

    // 2. Find the highest ID to generate a new one
    int maxID = 0;
    std::ifstream fileIn(R"(C:\Users\mahno\OneDrive\Documents\GitHub\Supermarket-Billing-System\Data\users.txt)");
    std::string line;
    while (std::getline(fileIn, line)) {
        std::stringstream ss(line);
        std::string idStr, userStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, userStr, ',');

        // Block duplicates
        if (userStr == newUser) {
            MessageBox::Show("Username already exists!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        int currentID = std::stoi(idStr);
        if (currentID > maxID) maxID = currentID;
    }
    fileIn.close();

    // 3. Save the new user directly to the file!
    std::ofstream fileOut(R"(C:\Users\mahno\OneDrive\Documents\GitHub\Supermarket-Billing-System\Data\users.txt)", std::ios::app);
    fileOut << (maxID + 1) << "," << newUser << "," << hashedPass << "," << newRole << "\n";
    fileOut.close();

    MessageBox::Show("New staff member hired successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
    txtUsername->Text = ""; txtPassword->Text = ""; txtID->Text = "";
    RefreshGrid();
}

// --- Delete / Fire User ---
System::Void UserForm::btnDelete_Click(System::Object^ sender, System::EventArgs^ e) {
    if (txtID->Text == "") return;

    if (MessageBox::Show("Are you sure you want to delete this account?", "Confirm", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::Yes) {

        std::string targetID = msclr::interop::marshal_as<std::string>(txtID->Text);
        std::string targetUser = msclr::interop::marshal_as<std::string>(txtUsername->Text);

        // Protect the master admin
        if (targetUser == "admin" || targetUser == "Admin") {
            MessageBox::Show("You cannot delete the Master Admin account!", "Access Denied", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        std::ifstream fileIn(R"(C:\Users\mahno\OneDrive\Documents\GitHub\Supermarket-Billing-System\Data\users.txt)");
        std::ofstream tempFile("Data/temp_users.txt");

        std::string line;
        while (std::getline(fileIn, line)) {
            std::stringstream ss(line);
            std::string currentID;
            std::getline(ss, currentID, ',');

            // Write everyone EXCEPT the deleted user to the new file
            if (currentID != targetID) {
                tempFile << line << "\n";
            }
        }

        fileIn.close();
        tempFile.close();

        // Replace the old file with the updated one
        std::remove("C:\\Users\\mahno\\OneDrive\\Documents\\GitHub\\Supermarket-Billing-System\\Data\\users.txt");
        std::rename("Data/temp_users.txt", "C:\\Users\\mahno\\OneDrive\\Documents\\GitHub\\Supermarket-Billing-System\\Data\\users.txt");

        MessageBox::Show("Account successfully deleted.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
        txtUsername->Text = ""; txtPassword->Text = ""; txtID->Text = "";
        RefreshGrid();
    }
}
