/*
 * Simple ATM Machine — C++ OOP Project
 * Author: Deborah Musuamba
 * GitHub: github.com/Deborahmk
 * Description: A console-based ATM simulation using Object-Oriented
 *              Programming concepts: classes, objects, loops, and functions.
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;

// ─── Transaction Class ────────────────────────────────────────────────────────
class Transaction {
public:
    string type;
    double amount;
    double balanceAfter;
    string date;

    Transaction(string t, double a, double b) {
        type = t;
        amount = a;
        balanceAfter = b;
        // Get current date/time
        time_t now = time(0);
        char* dt = ctime(&now);
        date = string(dt).substr(0, 24);
    }
};

// ─── Account Class ────────────────────────────────────────────────────────────
class Account {
private:
    string ownerName;
    string accountNumber;
    string pin;
    double balance;
    vector<Transaction> history;

public:
    // Constructor
    Account(string name, string accNum, string pinCode, double initialBalance) {
        ownerName = name;
        accountNumber = accNum;
        pin = pinCode;
        balance = initialBalance;
    }

    // Getters
    string getName() { return ownerName; }
    string getAccountNumber() { return accountNumber; }
    double getBalance() { return balance; }

    // PIN verification
    bool verifyPin(string inputPin) {
        return pin == inputPin;
    }

    // Deposit
    bool deposit(double amount) {
        if (amount <= 0) {
            cout << "\n  ❌ Invalid deposit amount. Must be greater than $0.\n";
            return false;
        }
        balance += amount;
        history.push_back(Transaction("DEPOSIT", amount, balance));
        cout << "\n  ✅ Deposit successful!\n";
        cout << "  Amount deposited : $" << fixed << setprecision(2) << amount << "\n";
        cout << "  New balance      : $" << fixed << setprecision(2) << balance << "\n";
        return true;
    }

    // Withdraw
    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "\n  ❌ Invalid withdrawal amount. Must be greater than $0.\n";
            return false;
        }
        if (amount > balance) {
            cout << "\n  ❌ Insufficient funds!\n";
            cout << "  Available balance: $" << fixed << setprecision(2) << balance << "\n";
            cout << "  Requested amount : $" << fixed << setprecision(2) << amount << "\n";
            return false;
        }
        balance -= amount;
        history.push_back(Transaction("WITHDRAWAL", amount, balance));
        cout << "\n  ✅ Withdrawal successful!\n";
        cout << "  Amount withdrawn : $" << fixed << setprecision(2) << amount << "\n";
        cout << "  Remaining balance: $" << fixed << setprecision(2) << balance << "\n";
        return true;
    }

    // Transfer
    bool transfer(Account& recipient, double amount) {
        if (amount <= 0) {
            cout << "\n  ❌ Invalid transfer amount.\n";
            return false;
        }
        if (amount > balance) {
            cout << "\n  ❌ Insufficient funds for transfer!\n";
            return false;
        }
        balance -= amount;
        recipient.balance += amount;
        history.push_back(Transaction("TRANSFER OUT to " + recipient.getName(), amount, balance));
        recipient.history.push_back(Transaction("TRANSFER IN from " + ownerName, amount, recipient.balance));
        cout << "\n  ✅ Transfer successful!\n";
        cout << "  Amount transferred: $" << fixed << setprecision(2) << amount << "\n";
        cout << "  Transferred to    : " << recipient.getName() << "\n";
        cout << "  Your new balance  : $" << fixed << setprecision(2) << balance << "\n";
        return true;
    }

    // Show balance
    void showBalance() {
        cout << "\n  ┌─────────────────────────────────┐\n";
        cout << "  │         ACCOUNT BALANCE         │\n";
        cout << "  ├─────────────────────────────────┤\n";
        cout << "  │  Account  : " << accountNumber << "          │\n";
        cout << "  │  Owner    : " << left << setw(22) << ownerName << "│\n";
        cout << "  │  Balance  : $" << fixed << setprecision(2) << setw(21) << right << balance << "│\n";
        cout << "  └─────────────────────────────────┘\n";
    }

    // Show transaction history
    void showHistory() {
        cout << "\n  ┌──────────────────────────────────────────────────────────┐\n";
        cout << "  │                  TRANSACTION HISTORY                    │\n";
        cout << "  ├──────────────────────────────────────────────────────────┤\n";
        if (history.empty()) {
            cout << "  │  No transactions yet.                                    │\n";
        } else {
            for (int i = history.size() - 1; i >= 0 && i >= (int)history.size() - 5; i--) {
                cout << "  │  " << left << setw(35) << history[i].type;
                cout << " $" << fixed << setprecision(2) << setw(10) << right << history[i].amount << "  │\n";
                cout << "  │  Balance after: $" << fixed << setprecision(2) << setw(10) << history[i].balanceAfter;
                cout << "                     │\n";
                cout << "  │  " << left << setw(54) << history[i].date << "│\n";
                if (i > 0) cout << "  ├──────────────────────────────────────────────────────────┤\n";
            }
        }
        cout << "  └──────────────────────────────────────────────────────────┘\n";
    }
};

// ─── ATM Class ────────────────────────────────────────────────────────────────
class ATM {
private:
    vector<Account> accounts;
    Account* currentAccount;
    bool isLoggedIn;

    void printHeader() {
        cout << "\n";
        cout << "  ╔══════════════════════════════════════╗\n";
        cout << "  ║        WELCOME TO DM BANK ATM        ║\n";
        cout << "  ║   Author: Deborah Musuamba           ║\n";
        cout << "  ║   github.com/Deborahmk               ║\n";
        cout << "  ╚══════════════════════════════════════╝\n\n";
    }

    void printDivider() {
        cout << "  ──────────────────────────────────────\n";
    }

public:
    ATM() {
        currentAccount = nullptr;
        isLoggedIn = false;

        // Pre-loaded sample accounts
        accounts.push_back(Account("Deborah Musuamba", "ACC001", "1234", 5000.00));
        accounts.push_back(Account("John Smith",       "ACC002", "5678", 2500.00));
        accounts.push_back(Account("Sarah Johnson",    "ACC003", "9012", 7800.00));
    }

    // Find account by number
    Account* findAccount(string accNum) {
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccountNumber() == accNum) {
                return &accounts[i];
            }
        }
        return nullptr;
    }

    // Login
    bool login() {
        printHeader();
        string accNum, pin;
        int attempts = 0;

        while (attempts < 3) {
            cout << "  Enter account number: ";
            cin >> accNum;

            Account* acc = findAccount(accNum);
            if (!acc) {
                cout << "  ❌ Account not found. Try: ACC001, ACC002, ACC003\n\n";
                attempts++;
                continue;
            }

            cout << "  Enter PIN: ";
            cin >> pin;

            if (acc->verifyPin(pin)) {
                currentAccount = acc;
                isLoggedIn = true;
                cout << "\n  ✅ Login successful! Welcome, " << acc->getName() << "!\n";
                return true;
            } else {
                attempts++;
                cout << "  ❌ Incorrect PIN. Attempts remaining: " << (3 - attempts) << "\n\n";
            }
        }

        cout << "\n  🔒 Too many failed attempts. Card blocked.\n";
        return false;
    }

    // Main ATM menu
    void showMenu() {
        int choice;
        do {
            printDivider();
            cout << "\n  ATM MAIN MENU\n\n";
            cout << "  1. Check Balance\n";
            cout << "  2. Deposit\n";
            cout << "  3. Withdraw\n";
            cout << "  4. Transfer\n";
            cout << "  5. Transaction History\n";
            cout << "  6. Logout\n\n";
            cout << "  Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    currentAccount->showBalance();
                    break;

                case 2: {
                    double amount;
                    cout << "\n  Enter deposit amount: $";
                    cin >> amount;
                    currentAccount->deposit(amount);
                    break;
                }

                case 3: {
                    double amount;
                    cout << "\n  Enter withdrawal amount: $";
                    cin >> amount;
                    currentAccount->withdraw(amount);
                    break;
                }

                case 4: {
                    string recipientAcc;
                    double amount;
                    cout << "\n  Enter recipient account number: ";
                    cin >> recipientAcc;
                    Account* recipient = findAccount(recipientAcc);
                    if (!recipient) {
                        cout << "  ❌ Recipient account not found.\n";
                    } else if (recipient->getAccountNumber() == currentAccount->getAccountNumber()) {
                        cout << "  ❌ Cannot transfer to your own account.\n";
                    } else {
                        cout << "  Enter transfer amount: $";
                        cin >> amount;
                        currentAccount->transfer(*recipient, amount);
                    }
                    break;
                }

                case 5:
                    currentAccount->showHistory();
                    break;

                case 6:
                    cout << "\n  ✅ Logged out successfully. Thank you, ";
                    cout << currentAccount->getName() << "!\n";
                    cout << "  Please take your card. Have a great day!\n\n";
                    isLoggedIn = false;
                    currentAccount = nullptr;
                    break;

                default:
                    cout << "\n  ❌ Invalid option. Please enter 1-6.\n";
            }
        } while (choice != 6);
    }

    // Run the ATM
    void run() {
        char another;
        do {
            if (login()) {
                showMenu();
            }
            cout << "  Would you like to use the ATM again? (y/n): ";
            cin >> another;
            cout << "\n";
        } while (another == 'y' || another == 'Y');

        cout << "  Thank you for using DM Bank ATM. Goodbye!\n\n";
    }
};

// ─── Main ─────────────────────────────────────────────────────────────────────
int main() {
    ATM atm;
    atm.run();
    return 0;
}
