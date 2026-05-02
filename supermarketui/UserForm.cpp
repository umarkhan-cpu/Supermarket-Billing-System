#include "UserForm.h"
#include "UserManagement.h"
#include "SessionManager.h"
#include "User.h"
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

    std::ifstream file("Data/users.txt");
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
    std::ifstream fileIn("Data/users.txt");
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
    std::ofstream fileOut("Data/users.txt", std::ios::app);
    fileOut << (maxID + 1) << "," << newUser << "," << hashedPass << "," << newRole << "\n";
    fileOut.close();

    MessageBox::Show("New staff member hired successfully!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
    txtUsername->Text = ""; txtPassword->Text = ""; txtID->Text = "";
    RefreshGrid();
}

// --- Delete / Fire User ---
System::Void UserForm::btnDelete_Click(System::Object^ sender, System::EventArgs^ e) {
    if (txtID->Text == "") {
        MessageBox::Show("Please select a user from the list first.",
            "No Selection", MessageBoxButtons::OK, MessageBoxIcon::Information);
        return;
    }

    if (MessageBox::Show("Are you sure you want to delete this account?", "Confirm",
        MessageBoxButtons::YesNo, MessageBoxIcon::Warning) != System::Windows::Forms::DialogResult::Yes) {
        return;
    }

    std::string targetID = msclr::interop::marshal_as<std::string>(txtID->Text);
    std::string targetUser = msclr::interop::marshal_as<std::string>(txtUsername->Text);
    std::string targetRole = msclr::interop::marshal_as<std::string>(cbRole->SelectedItem->ToString());

    // Self-delete protection - the currently logged-in user can't fire themselves.
    // Their session would become invalid mid-action and they'd lose access.
    User* current = SessionManager::getCurrentUser();
    if (current && current->getUsername() == targetUser) {
        MessageBox::Show("You cannot fire yourself. Log in as another admin to delete this account.",
            "Cannot Delete", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
    }

    // Last-admin protection - if this is an Admin, count how many other admins exist.
    // Refuse if this would leave zero admins (would lock the system out forever).
    if (targetRole == "Admin") {
        int adminCount = 0;
        std::ifstream countFile("Data/users.txt");
        std::string countLine;
        while (std::getline(countFile, countLine)) {
            std::stringstream cs(countLine);
            std::string f0, f1, f2, role;
            std::getline(cs, f0, ','); std::getline(cs, f1, ','); std::getline(cs, f2, ','); std::getline(cs, role, ',');
            if (role == "Admin") adminCount++;
        }
        countFile.close();
        if (adminCount <= 1) {
            MessageBox::Show("Cannot delete the last remaining Admin. Promote another user to Admin first.",
                "Cannot Delete", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }
    }

    // All protections passed - rewrite the file without this user
    std::ifstream fileIn("Data/users.txt");
    std::ofstream tempFile("Data/temp_users.txt");

    std::string line;
    while (std::getline(fileIn, line)) {
        std::stringstream ss(line);
        std::string currentID;
        std::getline(ss, currentID, ',');
        if (currentID != targetID) {
            tempFile << line << "\n";
        }
    }

    fileIn.close();
    tempFile.close();

    std::remove("Data/users.txt");
    std::rename("Data/temp_users.txt", "Data/users.txt");

    MessageBox::Show("Account successfully deleted.", "Success",
        MessageBoxButtons::OK, MessageBoxIcon::Information);
    txtUsername->Text = ""; txtPassword->Text = ""; txtID->Text = "";
    RefreshGrid();
}

System::Void UserForm::btnUpdate_Click(System::Object^ sender, System::EventArgs^ e) {
    if (txtID->Text == "") {
        MessageBox::Show("Please select a user from the list first.",
            "No Selection", MessageBoxButtons::OK, MessageBoxIcon::Information);
        return;
    }
    if (String::IsNullOrWhiteSpace(txtUsername->Text) || cbRole->SelectedIndex == -1) {
        MessageBox::Show("Username and Role are required.",
            "Missing Info", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
    }

    std::string targetID = msclr::interop::marshal_as<std::string>(txtID->Text);
    std::string newUsername = msclr::interop::marshal_as<std::string>(txtUsername->Text);
    std::string newRole = msclr::interop::marshal_as<std::string>(cbRole->SelectedItem->ToString());
    std::string newPasswordPlain = msclr::interop::marshal_as<std::string>(txtPassword->Text);

    // Last-admin protection on demotion - if this user was Admin and we're
    // changing them to Cashier, make sure another Admin still exists.
    if (newRole == "Cashier") {
        std::ifstream countFile("Data/users.txt");
        std::string countLine;
        int adminCount = 0;
        bool wasThisAdmin = false;
        while (std::getline(countFile, countLine)) {
            std::stringstream cs(countLine);
            std::string f0, f1, f2, role;
            std::getline(cs, f0, ','); std::getline(cs, f1, ','); std::getline(cs, f2, ','); std::getline(cs, role, ',');
            if (role == "Admin") {
                adminCount++;
                if (f0 == targetID) wasThisAdmin = true;
            }
        }
        countFile.close();
        if (wasThisAdmin && adminCount <= 1) {
            MessageBox::Show("Cannot demote the last remaining Admin. Promote another user to Admin first.",
                "Cannot Demote", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }
    }

    // Read all lines, modify the matching one, write everything back.
    std::ifstream fileIn("Data/users.txt");
    std::ofstream tempFile("Data/temp_users.txt");
    std::string line;
    bool found = false;

    while (std::getline(fileIn, line)) {
        std::stringstream ss(line);
        std::string currentID, currentUser, currentHash, currentRole;
        std::getline(ss, currentID, ',');
        std::getline(ss, currentUser, ',');
        std::getline(ss, currentHash, ',');
        std::getline(ss, currentRole, ',');

        if (currentID == targetID) {
            found = true;
            // If a new password was typed, hash it. Otherwise keep the existing hash.
            std::string finalHash = currentHash;
            if (!newPasswordPlain.empty()) {
                finalHash = UserManagement::hashedpass(newPasswordPlain);
            }
            tempFile << currentID << "," << newUsername << "," << finalHash << "," << newRole << "\n";
        }
        else {
            tempFile << line << "\n";
        }
    }

    fileIn.close();
    tempFile.close();

    if (!found) {
        std::remove("Data/temp_users.txt");
        MessageBox::Show("User not found in file.", "Error",
            MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    std::remove("Data/users.txt");
    std::rename("Data/temp_users.txt", "Data/users.txt");

    MessageBox::Show("Account updated successfully.", "Success",
        MessageBoxButtons::OK, MessageBoxIcon::Information);
    txtUsername->Text = ""; txtPassword->Text = ""; txtID->Text = "";
    cbRole->SelectedIndex = 1;
    RefreshGrid();
}

System::Void UserForm::btnClear_Click(System::Object^ sender, System::EventArgs^ e) {
    // Reset all fields back to "ready for new user" state
    txtID->Text = "";
    txtUsername->Text = "";
    txtPassword->Text = "";
    cbRole->SelectedIndex = 1;  // default to Cashier
    gridUsers->ClearSelection();
}

System::Void UserForm::chkShowPassword_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    // When checked, show actual characters; when unchecked, mask with system char.
    txtPassword->UseSystemPasswordChar = !chkShowPassword->Checked;
}
