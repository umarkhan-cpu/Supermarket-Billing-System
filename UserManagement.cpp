#include "UserManagement.h"

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
    string user, pass, role;

    ifstream file("managementdata.txt"); 
    while (getline(file, user, ',')) { 
        getline(file, pass, ','); 

        if (user == fuser && pass == fpass) {
            return true;
        }
    }
    return false;
}
bool UserManagement::userexists(string fuser) {
    string user, pass, role;
    ifstream file("managementdata.txt");

    while (getline(file, user, ',')) {
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


    do {
        generatecaptcha();
        if (!validatecaptcha()) {
            cout << "Try Again!" << endl;
        }
    } while (!validatecaptcha());

    string hpass = hashedpass(password);
    ofstream file("managementdata.txt", ios::app);
    file << username << "," << hpass << "," << role << endl;

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
    string dataFile = "managementdata.txt";
    string tempFileName = "temp.txt";

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

    if (found)
        cout << "Account deleted successfully!" << endl;
    else
        cout << "User not found!" << endl;
}