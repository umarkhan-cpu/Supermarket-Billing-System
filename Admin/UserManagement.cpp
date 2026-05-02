#include "UserManagement.h"
#include <sstream>

string UserManagement::passtrength(string password) {
    int score = 0;
    if (password.length() >= 8) {
        score++;
    }
    if (regex_search(password, regex("[A-Z]"))) { //[] means if present within the set
        score++;
    }
    if (regex_search(password, regex("[0-9]"))) {
        score++;
    }
    if (regex_search(password, regex("[^A-Za-z0-9]"))) { // [^] means apart from the set
        score++;
    }
    string* str = new string[5]{ "Very Weak", "Weak", "Fair", "Strong", "Very Strong" };
    string result = *(str + score);
    delete[] str;
    return result;
}
bool UserManagement::userverify(string fuser, string fpass) {
    int id;
    string user, pass, role;

    ifstream file("Data/users.txt");

    while (getline(file, user, ',')) {
        getline(file, pass, ',');
        getline(file, role);

        if (user == fuser && pass == fpass) {
            return true;
        }
    }
    return false;
}
bool UserManagement::userexists(string fuser) {
    int id;
    string user, pass, role;

    ifstream file("Data/users.txt");

    while (getline(file, user, ',')) {
        getline(file, pass, ',');
        getline(file, role);

        if (user == fuser) {
            return true;
        }
    }
    return false;
}
void UserManagement::generatecaptcha() {
    int minVal = 1, maxVal = 20;
    num1 = rand() % maxVal + minVal;
    num2 = rand() % maxVal + minVal;

    int opCount = 3;
    char* operators = new char[opCount] { '+', '-', '*' };
    op = *(operators + rand() % opCount);

    if (op == '-' && num1 < num2) { // to make sure the ans is not neg
        swap(num1, num2);
    }

    if (op == '+') {
        ans = num1 + num2;
    }
    else if (op == '-') {
        ans = num1 - num2;
    }
    else {
        ans = num1 * num2;
    }

    delete[] operators;

}
bool UserManagement::validatecaptcha() {
    int temp;

    cout << "Solve: " << num1 << " " << op << " " << num2 << " = ";
    cin >> temp;

    if (temp == ans) {
        return true;
    }
    else {
        return false;
    }
}

// Original Work By Areesha
//int UserManagement::nextAvailableID() {
//    int id, maxID = 0;
//    string user, pass, role;
//
//    ifstream file("Data/users.txt");
//
//    while (getline(file, user, ',')) {
//        getline(file, pass, ',');
//        getline(file, role);
//
//        id = stoi(user); // assuming first column is ID
//        if (id > maxID) {
//            maxID = id;
//        }
//    }
//
//    return maxID + 1;
//}

// Modification by Umar (lead): To handle edge cases and crashes in case of empty users.txt (using try-catch)
int UserManagement::nextAvailableID() {
    int id, maxID = 0;
    string user, pass, hash, role;

    ifstream file("Data/users.txt");

    // Read line-by-line so we can skip blanks and handle malformed rows
    // without crashing (e.g. if the file has a trailing newline).
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        if (!getline(ss, user, ',')) continue;
        if (!getline(ss, pass, ',')) continue;
        if (!getline(ss, hash, ',')) continue;
        getline(ss, role);

        if (user.empty()) continue;

        try {
            id = stoi(user);
            if (id > maxID) maxID = id;
        }
        catch (const std::exception&) {
            continue;
        }
    }

    return maxID + 1;
}
UserManagement::UserManagement() {
    username = "Unknown";
    password = "Unknown";
    num1 = 0;
    num2 = 0;
    ans = 0;
    op = '\0';
}
string UserManagement::hashedpass(string pass) {
    hash<string> hasher; //built in hasher
    size_t hashed = hasher(pass); //hashes the password and then store it as a non neg int val
    return to_string(hashed); //converts it into str
}
void UserManagement::signup(string role) {
    string strength;
    string targetStrength = "Very Strong";
    string strengthPrompt = "Password must have more than 8 characters including alphanumeric, uppercase and numbers!";

    cout << "Enter username: ";
    cin >> username;

    if (userexists(username)) {
        cout << "Username already exists! " << endl;
        return;
    }
    cout << strengthPrompt << endl;

    do {
        cout << "Enter password: ";
        cin >> password;

        strength = passtrength(password);
        cout << "Password Strength: " << strength << endl;

    } while (strength != targetStrength);

    bool flag;
    do {
        generatecaptcha();
        flag = validatecaptcha();
        if (!flag) {
            cout << "Try Again!" << endl;
        }
    } while (!flag);

    string hpass = hashedpass(password);

    int id = nextAvailableID();

    ofstream file("Data/users.txt", ios::app);
    file << id << "," << username << "," << hpass << "," << role << endl;
    cout << "Signup successful!" << endl;
}
bool UserManagement::login() {
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    string hpass = hashedpass(password);
    if (userverify(username, hpass)) {
        cout << "Login successful!" << endl;
        return true;
    }
    cout << "Invalid credentials!" << endl;
    return false;
}
void UserManagement::deleteAccount() {
    string fuser, fpass, frole;
    bool found = false;
    string dataFile = "Data/users.txt";
    string tempFileName = "Data/temp.txt";

    ifstream inFile(dataFile);
    ofstream tempFile(tempFileName);

    while (getline(inFile, fuser, ',')) {
        getline(inFile, fpass, ',');
        getline(inFile, frole);

        if (fuser == username && fpass == hashedpass(password)) {
            found = true;
            continue;
        }
        tempFile << fuser << "," << fpass << "," << frole << endl;
    }

    inFile.close();
    tempFile.close();

    remove(dataFile.c_str()); //deletes the old file
    rename(tempFileName.c_str(), dataFile.c_str()); //renames the temp file with the new one

    if (found) {
        cout << "Account deleted successfully!" << endl;
    }
    else {
        cout << "User not found!" << endl;
    }
}

void UserManagement::menu() {
    int choice;

    do {
        cout << "~~USER MANAGEMENT MENU~~";
        cout << "1. Sign Up" << endl;
        cout << "2. Login" << endl;
        cout << "3. Delete Account" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: " << endl;
        cin >> choice;

        switch (choice) {
        case 1: {
            string role;
            cout << "Enter role (Admin/Cashier): ";
            cin >> role;
            signup(role);
            break;
        }

        case 2: {
            if (login()) {
                int innerChoice;

                do {
                    cout << "~~LOGIN PAGE~~" << endl;
                    cout << "1. Delete Account" << endl;
                    cout << "2. Logout" << endl;
                    cout << "Enter choice: ";
                    cin >> innerChoice;

                    if (innerChoice == 1) {
                        deleteAccount();
                        break; 
                    }

                } while (innerChoice != 2);
            }
            break;
        }

        case 3: {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            deleteAccount();
            break;
        }

        case 4:
            cout << "Exiting..." << endl;;
            break;

        default:
            cout << "Invalid choice!" << endl;;
        }

    } while (choice != 4);
}

