#include "MyForm.h"
#include "Dashboard.h"
#include <msclr\marshal_cppstd.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Include your backend headers
#include "UserManagement.h"
#include "SessionManager.h"
#include "Admin.h"
#include "Cashier.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace supermarketui;

[STAThreadAttribute]
int main(cli::array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    supermarketui::MyForm form;
    Application::Run(% form);
    return 0;
}

// Helper to split CSV line
std::vector<std::string> splitCSV(const std::string& line) {
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, ',')) {
        result.push_back(item);
    }
    return result;
}

// When you click Login
System::Void MyForm::btnLogin_Click(System::Object^ sender, System::EventArgs^ e) {

    String^ netUsername = this->txtUsername->Text;
    String^ netPassword = this->txtPassword->Text;

    std::string cppUsername = msclr::interop::marshal_as<std::string>(netUsername);
    std::string cppPassword = msclr::interop::marshal_as<std::string>(netPassword);

    std::string hashedInput = UserManagement::hashedpass(cppPassword);
    bool loginSuccess = false;

    // Open the users file directly to bypass the private userverify method
    std::ifstream file("Data/users.txt");

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> fields = splitCSV(line);

            // Expected CSV format: userID,username,passwordHash,role,lastLogin
            if (fields.size() >= 4) {
                std::string fileUser = fields[1];
                std::string fileHash = fields[2];
                std::string role = fields[3];

                if (fileUser == cppUsername && fileHash == hashedInput) {
                    loginSuccess = true;

                    int id = std::stoi(fields[0]);
                    User* loggedInUser = nullptr;

                    if (role == "Admin") {
                        loggedInUser = new Admin(id, fileUser, fileHash);
                    }
                    else {
                        loggedInUser = new Cashier(id, fileUser, fileHash);
                    }

                    SessionManager::startSession(loggedInUser);
                    break;
                }
            }
        }
        file.close();
    }
    else {
        MessageBox::Show("Could not open Data/users.txt. Check your file path!", "File Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    if (loginSuccess) {
        // 1. Hide the login window
        this->Hide();

        // 2. Create the Dashboard
        Dashboard^ dash = gcnew Dashboard();

        // 3. Show it!
        dash->Show();
    }
    else {
        MessageBox::Show("Invalid username or password.", "Login Failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

// When you click Exit
System::Void MyForm::btnExit_Click(System::Object^ sender, System::EventArgs^ e) {
    Application::Exit();
}

System::Void MyForm::chkShowPassword_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
    // When checked, show actual characters; when unchecked, mask with '*'.
    // Note: MyForm uses PasswordChar (not UseSystemPasswordChar like UserForm).
    if (chkShowPassword->Checked) {
        txtPassword->PasswordChar = '\0';
    }
    else {
        txtPassword->PasswordChar = '*';
    }
}