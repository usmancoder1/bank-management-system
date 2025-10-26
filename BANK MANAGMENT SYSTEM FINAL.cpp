#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
using namespace std;

// ------------------ Base Class ------------------
class Account {
protected:
    string name, cnic, phone;
    double balance;
    int pin;

public:
    void getAccountInfo() {
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your CNIC: ";
        cin >> cnic;
        cout << "Enter your Phone: ";
        cin >> phone;
        cout << "Enter your PIN: ";
        cin >> pin;
        cout << "Enter initial deposit: ";
        cin >> balance;
    }

    string getCNIC() { return cnic; }
    int getPIN() { return pin; }
};

// ------------------ Saving Account ------------------
class SavingAccount : public Account {
public:
    void createAccount() {
        getAccountInfo();
        ofstream file("saving.txt", ios::app);
        file << "CNIC:" << cnic << "\n";
        file << "PIN:" << pin << "\n";
        file << "Name:" << name << "\n";
        file << "Phone:" << phone << "\n";
        file << "Balance:" << balance << "\n";
        file << "----------------------\n";
        file.close();
        cout << "Saving Account Created Successfully!\n";
    }

    bool login(string cnic, int pin) {
        ifstream file("saving.txt");
        string line, fileCnic;
        int filePin;
        while (getline(file, line)) {
            if (line.substr(0, 5) == "CNIC:") fileCnic = line.substr(5);
            if (line.substr(0, 4) == "PIN:") {
                stringstream ss(line.substr(4));
                ss >> filePin;
            }
            if (fileCnic == cnic && filePin == pin) return true;
        }
        return false;
    }

    void withdraw(string cnic) {
        ifstream in("saving.txt");
        ofstream temp("temp.txt");
        string line;
        while (getline(in, line)) {
            if (line.substr(0, 5) == "CNIC:" && line.substr(5) == cnic) {
                temp << line << "\n"; 
                getline(in, line); temp << line << "\n"; 
                getline(in, line); temp << line << "\n"; 
                getline(in, line); temp << line << "\n"; 
                getline(in, line);    
                double fileBalance;
                stringstream ss(line.substr(8));
                ss >> fileBalance;

                double amount;
                cout << "Enter withdraw amount: ";
                cin >> amount;

                if (fileBalance >= amount) {
                    fileBalance -= amount;
                    cout << "Withdraw Successful! New Balance: " << fileBalance << endl;
                } else {
                    cout << "Insufficient Balance!\n";
                }
                temp << "Balance:" << fileBalance << "\n";
            } else {
                temp << line << "\n";
            }
        }
        in.close();
        temp.close();
        remove("saving.txt");
        rename("temp.txt", "saving.txt");
    }

    void deposit(string cnic) {
        ifstream in("saving.txt");
        ofstream temp("temp.txt");
        string line;
        bool found = false;
        while (getline(in, line)) {
            if (line.substr(0,5) == "CNIC:" && line.substr(5) == cnic) {
                found = true;
                temp << line << "\n"; 
                getline(in, line); temp << line << "\n"; 
                getline(in, line); temp << line << "\n"; 
                getline(in, line); temp << line << "\n"; 
                getline(in, line); 
                double bal;
                stringstream ss(line.substr(8));
                ss >> bal;
                double amount;
                cout << "Enter deposit amount: ";
                cin >> amount;
                bal += amount;
                cout << "Deposit Successful! New Balance: " << bal << endl;
                temp << "Balance:" << bal << "\n";
            } else {
                temp << line << "\n";
            }
        }
        in.close();
        temp.close();
        remove("saving.txt");
        rename("temp.txt","saving.txt");
        if(!found) cout<<"Account not found!\n";
    }

    void checkDetails(string cnic) {
        ifstream file("saving.txt");
        string line;
        bool found = false;
        cout << "\n--- Saving Account Details ---\n";
        while (getline(file, line)) {
            if (line.substr(0, 5) == "CNIC:" && line.substr(5) == cnic) {
                found = true;
                cout << line << "\n";
                for (int i = 0; i < 4; i++) {
                    getline(file, line);
                    cout << line << "\n";
                }
                break;
            }
        }
        if (!found) cout << "Account not found!\n";
    }
};

// ------------------ Current Account ------------------
class CurrentAccount : public Account {
public:
    void createAccount() {
        getAccountInfo();
        ofstream file("current.txt", ios::app);
        file << "CNIC:" << cnic << "\n";
        file << "PIN:" << pin << "\n";
        file << "Name:" << name << "\n";
        file << "Phone:" << phone << "\n";
        file << "Balance:" << balance << "\n";
        file << "----------------------\n";
        file.close();
        cout << "Current Account Created Successfully!\n";
    }

    bool login(string cnic, int pin) {
        ifstream file("current.txt");
        string line, fileCnic;
        int filePin;
        while (getline(file, line)) {
            if (line.substr(0, 5) == "CNIC:") fileCnic = line.substr(5);
            if (line.substr(0, 4) == "PIN:") {
                stringstream ss(line.substr(4));
                ss >> filePin;
            }
            if (fileCnic == cnic && filePin == pin) return true;
        }
        return false;
    }
    void withdraw(string cnic) {
    ifstream in("current.txt");
    ofstream temp("temp.txt");
    string line;
    bool found = false;
    while (getline(in, line)) {
        if (line.substr(0, 5) == "CNIC:" && line.substr(5) == cnic) {
            found = true;
            temp << line << "\n"; 
            getline(in, line); temp << line << "\n"; 
            getline(in, line); temp << line << "\n"; 
            getline(in, line); temp << line << "\n"; 
            getline(in, line);
            double fileBalance;
            stringstream ss(line.substr(8));
            ss >> fileBalance;

            double amount;
            cout << "Enter withdraw amount: ";
            cin >> amount;

            if (fileBalance >= amount) {
                fileBalance -= amount;
                cout << "Withdraw Successful! New Balance: " << fileBalance << endl;
            } else {
                cout << "Insufficient Balance!\n";
            }
            temp << "Balance:" << fileBalance << "\n";
        } else {
            temp << line << "\n";
        }
    }
    in.close();
    temp.close();
    remove("current.txt");
    rename("temp.txt", "current.txt");
    if(!found) cout << "Account not found!\n";
}

void sendMoney(string senderCnic) {
    string receiverCnic;
    double amount;
    cout << "Enter receiver CNIC: ";
    cin >> receiverCnic;
    cout << "Enter amount to send: ";
    cin >> amount;

    ifstream in("current.txt");
    ofstream temp("temp.txt");
    string line;
    bool senderFound = false, receiverFound = false;
    double senderBal, receiverBal;

    while (getline(in, line)) {
        if (line.substr(0,5) == "CNIC:" && line.substr(5) == senderCnic) {
            senderFound = true;
            temp << line << "\n";
            getline(in, line); temp << line << "\n"; 
            getline(in, line); temp << line << "\n"; 
            getline(in, line); temp << line << "\n"; 
            getline(in, line);
            stringstream ss(line.substr(8));
            ss >> senderBal;

            if (senderBal >= amount) {
                senderBal -= amount;
                cout << "Money Sent Successfully!\n";
            } else {
                cout << "Insufficient Balance, transaction failed.\n";
            }
            temp << "Balance:" << senderBal << "\n";
        }
        else if (line.substr(0,5) == "CNIC:" && line.substr(5) == receiverCnic) {
            receiverFound = true;
            temp << line << "\n";
            getline(in, line); temp << line << "\n"; 
            getline(in, line); temp << line << "\n"; 
            getline(in, line); temp << line << "\n"; 
            getline(in, line);
            stringstream ss(line.substr(8));
            ss >> receiverBal;
            receiverBal += amount;
            temp << "Balance:" << receiverBal << "\n";
        }
        else {
            temp << line << "\n";
        }
    }

    in.close();
    temp.close();
    remove("current.txt");
    rename("temp.txt","current.txt");

    if(!senderFound) cout << "Sender account not found!\n";
    if(!receiverFound) cout << "Receiver account not found!\n";
}

        
    void zakatDeduction(string cnic) {
    ifstream in("current.txt");
    ofstream temp("temp.txt");
    string line;
    bool found = false;
    while (getline(in, line)) {
        if (line.substr(0,5) == "CNIC:" && line.substr(5) == cnic) {
            found = true;
            temp << line << "\n"; 
            getline(in, line); temp << line << "\n"; 
            getline(in, line); temp << line << "\n"; 
            getline(in, line); temp << line << "\n"; 
            getline(in, line); 
            double bal;
            stringstream ss(line.substr(8));
            ss >> bal;

            // Apply zakat if balance > 25000
            if (bal > 25000) {
                double zakat = bal * 0.025;
                bal -= zakat;
                cout << "Zakat Deducted: " << zakat << "\nNew Balance: " << bal << endl;
            } else {
                cout << "Balance kam hai, zakat apply nahi hoti.\n";
            }

            temp << "Balance:" << bal << "\n";
        } else {
            temp << line << "\n";
        }
    }
    in.close();
    temp.close();
    remove("current.txt");
    rename("temp.txt","current.txt");
    if(!found) cout<<"Account not found!\n";
}

    void deposit(string cnic) {
        ifstream in("current.txt");
        ofstream temp("temp.txt");
        string line;
        bool found = false;
        while (getline(in, line)) {
            if (line.substr(0,5) == "CNIC:" && line.substr(5) == cnic) {
                found = true;
                temp << line << "\n"; 
                getline(in, line); temp << line << "\n"; 
                getline(in, line); temp << line << "\n"; 
                getline(in, line); temp << line << "\n"; 
                getline(in, line); 
                double bal;
                stringstream ss(line.substr(8));
                ss >> bal;
                double amount;
                cout << "Enter deposit amount: ";
                cin >> amount;
                bal += amount;
                cout << "Deposit Successful! New Balance: " << bal << endl;
                temp << "Balance:" << bal << "\n";
            } else {
                temp << line << "\n";
            }
        }
        in.close();
        temp.close();
        remove("current.txt");
        rename("temp.txt","current.txt");
        if(!found) cout<<"Account not found!\n";
    }

    void checkDetails(string cnic) {
        ifstream file("current.txt");
        string line;
        bool found = false;
        cout << "\n--- Current Account Details ---\n";
        while (getline(file, line)) {
            if (line.substr(0, 5) == "CNIC:" && line.substr(5) == cnic) {
                found = true;
                cout << line << "\n";
                for (int i = 0; i < 4; i++) {
                    getline(file, line);
                    cout << line << "\n";
                }
                break;
            }
        }
        if (!found) cout << "Account not found!\n";
    }
};

// ------------------ Admin Class ------------------
class Admin : public SavingAccount, public CurrentAccount {
private:
    string username = "admin";
    string password = "1234";

public:
    bool login() {
        string u, p;
        cout << "Enter Admin Username: ";
        cin >> u;
        cout << "Enter Admin Password: ";
        cin >> p;
        if (u == username && p == password) {
            cout << "\n[Admin Login Successful]\n";
            return true;
        } else {
            cout << "Invalid Admin Credentials!\n";
            return false;
        }
    }

    void searchAccountByCNIC(string searchCnic) {
        bool found = false;
        string line;

        ifstream fin1("saving.txt");
        while (getline(fin1, line)) {
            if (line.substr(0, 5) == "CNIC:" && line.substr(5) == searchCnic) {
                cout << "\n[Saving Account Found]\n";
                cout << line << endl;
                for (int i = 0; i < 4; i++) {
                    if (getline(fin1, line)) cout << line << endl;
                }
                found = true;
                break;
            }
        }
        fin1.close();

        if (!found) {
            ifstream fin2("current.txt");
            while (getline(fin2, line)) {
                if (line.substr(0, 5) == "CNIC:" && line.substr(5) == searchCnic) {
                    cout << "\n[Current Account Found]\n";
                    cout << line << endl;
                    for (int i = 0; i < 4; i++) {
                        if (getline(fin2, line)) cout << line << endl;
                    }
                    found = true;
                    break;
                }
            }
            fin2.close();
        }

        if (!found) cout << "No account found with CNIC: " << searchCnic << endl;
    }

    void viewAllAccounts() {
        cout << "\n--- Saving Accounts ---\n";
        ifstream fin1("saving.txt");
        string line;
        while (getline(fin1, line)) {
            cout << line << endl;
        }
        fin1.close();

        cout << "\n--- Current Accounts ---\n";
        ifstream fin2("current.txt");
        while (getline(fin2, line)) {
            cout << line << endl;
        }
        fin2.close();
    }

    void deleteAccount(string delCnic) {
        ifstream in1("saving.txt");
        ofstream temp1("temp.txt");
        string line;
        bool deleted = false;
        while (getline(in1, line)) {
            if (line.substr(0,5) == "CNIC:" && line.substr(5) == delCnic) {
                for (int i = 0; i < 5; i++) getline(in1, line); 
                deleted = true;
            } else {
                temp1 << line << "\n";
            }
        }
        in1.close();
        temp1.close();
        remove("saving.txt");
        rename("temp.txt", "saving.txt");

        ifstream in2("current.txt");
        ofstream temp2("temp2.txt");
        while (getline(in2, line)) {
            if (line.substr(0,5) == "CNIC:" && line.substr(5) == delCnic) {
                for (int i = 0; i < 5; i++) getline(in2, line);
                deleted = true;
            } else {
                temp2 << line << "\n";
            }
        }
        in2.close();
        temp2.close();
        remove("current.txt");
        rename("temp2.txt", "current.txt");

        if (deleted) cout << "Account deleted successfully.\n";
        else cout << "Account not found.\n";
    }
};

// ------------------ Main ------------------
int main() {
    int choice;
    cout << "------------------ Welcome to the Bank ------------------\n";
    cout << "1. Register New Account\n";
    cout << "2. Login to Existing Account\n";
    cout << "3. Admin Login\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch(choice) {
        case 1: {
            int accType;
            cout << "Choose Account Type:\n1. Saving Account\n2. Current Account\nEnter choice: ";
            cin >> accType;
            switch(accType) {
                case 1: {
                    SavingAccount s;
                    s.createAccount();
                    break;
                }
                case 2: {
                    CurrentAccount c;
                    c.createAccount();
                    break;
                }
                default: cout << "Invalid choice!\n"; break;
            }
            break;
        }

        case 2: {
            int accType;
            cout << "Choose Account Type:\n1. Saving Account\n2. Current Account\nEnter choice: ";
            cin >> accType;

            string cnic;
            int pin;
            cout << "Enter CNIC: ";
            cin >> cnic;
            cout << "Enter PIN: ";
            cin >> pin;

            switch(accType) {
                case 1: {
                    SavingAccount s;
                    if (s.login(cnic, pin)) {
                        int opt;
                        do {
                            cout << "\n--- Saving Account Menu ---\n";
                            cout << "1. Deposit\n2. Withdraw\n3. Check Details\n4. Logout\nEnter choice: ";
                            cin >> opt;
                            switch(opt) {
                                case 1: s.deposit(cnic); break;
                                case 2: s.withdraw(cnic); break;
                                case 3: s.checkDetails(cnic); break;
                                case 4: cout << "Logged out.\n"; break;
                                default: cout << "Invalid option!\n"; break;
                            }
                        } while(opt != 4);
                    } else cout << "Invalid CNIC or PIN!\n";
                    break;
                }
                case 2: {
                    CurrentAccount c;
                    if (c.login(cnic, pin)) {
                        int opt;
                        do {
                        cout << "\n--- Current Account Menu ---\n";
                        cout << "1. Deposit\n";
                        cout << "2. Withdraw\n";
                        cout << "3. Send Money\n";
                        cout << "4. Check Details\n";
                        cout << "5. Zakat Deduction\n";   
                        cout << "6. Logout\n";            
                        cout << "Enter choice: ";
                        cin >> opt;
            switch (opt) {
                         case 1: c.deposit(cnic); break;
                         case 2: c.withdraw(cnic); break;
                         case 3: c.sendMoney(cnic); break;
                         case 4: c.checkDetails(cnic); break;
                         case 5: c.zakatDeduction(cnic); break; 
                         case 6: cout << "Logged out.\n"; break;
                         default: cout << "Invalid option!\n"; break;
    }
} while (opt != 6);

                    } else cout << "Invalid CNIC or PIN!\n";
                    break;
                }
                default: cout << "Invalid choice!\n"; break;
            }
            break;
        }

        case 3: {
            Admin a;
            if (a.login()) {
                int opt;
                do {
                    cout << "\n--- Admin Menu ---\n";
                    cout << "1. Search Account by CNIC\n";
                    cout << "2. View All Accounts\n";
                    cout << "3. Delete Account by CNIC\n";
                    cout << "4. Logout\n";
                    cout << "Enter choice: ";
                    cin >> opt;
                    switch(opt) {
                        case 1: {
                            string searchCnic;
                            cout << "Enter CNIC: ";
                            cin >> searchCnic;
                            a.searchAccountByCNIC(searchCnic);
                            break;
                        }
                        case 2: a.viewAllAccounts(); break;
                        case 3: {
                            string delCnic;
                            cout << "Enter CNIC to delete: ";
                            cin >> delCnic;
                            a.deleteAccount(delCnic);
                            break;
                        }
                        case 4: cout << "Admin Logged out.\n"; break;
                        default: cout << "Invalid option!\n"; break;
                    }
                } while(opt != 4);
            }
            break;
        }

        default: cout << "Invalid choice!\n"; break;
    }
    return 0;
}
