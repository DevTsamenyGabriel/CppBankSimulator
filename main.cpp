#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Account {
protected:
    string customerName;
    long long accountNumber{};
    string accountType;

public:
    void setAccountDetails() {
        cout << "Enter Customer Name: ";
        // Clear leftover newline before getline
        cin >> ws;
        getline(cin, customerName);

        cout << "Enter Account Number: ";
        cin >> accountNumber;
    }

    void displayAccountDetails() const {
        cout << "\n--- Account Details ---" << endl;
        cout << "Customer Name: " << customerName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Type: " << accountType << endl;
    }
};

class CurrentAccount : public Account {
private:
    double balance{};
    double minimumBalance{};
    double serviceCharge{};

public:
    void setCurrentAccountDetails() {
        setAccountDetails();
        accountType = "Current";

        cout << "Enter Initial Balance for Current Account: ";
        cin >> balance;

        cout << "Enter Minimum Balance required for Current Account: ";
        cin >> minimumBalance;

        cout << "Enter Service Charge for Current Account (if balance falls below minimum): ";
        cin >> serviceCharge;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit of $" << fixed << setprecision(2) << amount << " successful." << endl;
        } else {
            cout << "Deposit amount must be positive." << endl;
        }
    }

    void displayBalance() const {
        cout << "Current Account Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Withdrawal amount must be positive." << endl;
            return;
        }

        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawal of $" << fixed << setprecision(2) << amount << " successful." << endl;
            checkMinimumBalance();
        } else {
            cout << "Insufficient balance for withdrawal." << endl;
        }
    }

    void checkMinimumBalance() {
        if (balance < minimumBalance) {
            // Apply charge only if there is enough balance to deduct
            if (balance >= serviceCharge) {
                balance -= serviceCharge;
                cout << "WARNING: Balance is below minimum required ($" << fixed << setprecision(2)
                     << minimumBalance << ")." << endl;
                cout << "Service charge of $" << fixed << setprecision(2)
                     << serviceCharge << " imposed." << endl;
            } else {
                cout << "WARNING: Balance is below minimum required ($" << fixed << setprecision(2)
                     << minimumBalance << ")." << endl;
                cout << "Service charge could not be imposed due to insufficient funds." << endl;
            }
            displayBalance();
        } else {
            cout << "Minimum balance maintained. No service charge imposed." << endl;
        }
    }

    void displayChequeBookInfo() const {
        cout << "Cheque book facility: Available." << endl;
    }
};

class SavingsAccount : public Account {
private:
    double balance{};
    double minimumBalance{};
    double interestRate{};

public:
    void setSavingsAccountDetails() {
        setAccountDetails();
        accountType = "Savings";

        cout << "Enter Initial Balance for Savings Account: ";
        cin >> balance;

        cout << "Enter Minimum Balance required for Savings Account: ";
        cin >> minimumBalance;

        cout << "Enter Annual Interest Rate for Savings Account (e.g., 0.05 for 5%): ";
        cin >> interestRate;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit of $" << fixed << setprecision(2) << amount << " successful." << endl;
        } else {
            cout << "Deposit amount must be positive." << endl;
        }
    }

    void displayBalance() const {
        cout << "Savings Account Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    void calculateAndDepositInterest() {
        double interestEarned = balance * interestRate;
        balance += interestEarned;
        cout << "Interest of $" << fixed << setprecision(2) << interestEarned << " deposited." << endl;
        displayBalance();
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Withdrawal amount must be positive." << endl;
            return;
        }

        if (balance >= amount) {
            balance -= amount;
            cout << "Withdrawal of $" << fixed << setprecision(2) << amount << " successful." << endl;
            checkMinimumBalance();
        } else {
            cout << "Insufficient balance for withdrawal." << endl;
        }
    }

    void checkMinimumBalance() const {
        if (balance < minimumBalance) {
            cout << "WARNING: Balance is below minimum required ($" << fixed << setprecision(2)
                 << minimumBalance << ")." << endl;
            cout << "Please deposit funds to meet the minimum balance." << endl;
            displayBalance();
        } else {
            cout << "Minimum balance maintained. No issues." << endl;
        }
    }

    void displayChequeBookInfo() const {
        cout << "Cheque book facility: Not Available." << endl;
    }
};

int main() {
    CurrentAccount myCurrentAccount;
    SavingsAccount mySavingsAccount;

    cout << "--- Setting up Current Account ---" << endl;
    myCurrentAccount.setCurrentAccountDetails();
    myCurrentAccount.displayAccountDetails();
    myCurrentAccount.displayChequeBookInfo();
    myCurrentAccount.displayBalance();

    cout << "\n--- Performing Current Account Operations ---" << endl;
    myCurrentAccount.deposit(500.00);
    myCurrentAccount.displayBalance();
    myCurrentAccount.withdraw(200.00);
    myCurrentAccount.displayBalance();
    myCurrentAccount.checkMinimumBalance();

    cout << "\n--- Demonstrating Current Account Service Charge ---" << endl;
    myCurrentAccount.withdraw(1000.00);
    myCurrentAccount.displayBalance();
    myCurrentAccount.checkMinimumBalance();

    cout << "\n\n--- Setting up Savings Account ---" << endl;
    mySavingsAccount.setSavingsAccountDetails();
    mySavingsAccount.displayAccountDetails();
    mySavingsAccount.displayChequeBookInfo();
    mySavingsAccount.displayBalance();

    cout << "\n--- Performing Savings Account Operations ---" << endl;
    mySavingsAccount.deposit(1000.00);
    mySavingsAccount.displayBalance();
    mySavingsAccount.calculateAndDepositInterest();
    mySavingsAccount.displayBalance();
    mySavingsAccount.withdraw(300.00);
    mySavingsAccount.displayBalance();
    mySavingsAccount.checkMinimumBalance();

    cout << "\n--- Demonstrating Savings Account Minimum Balance Check ---" << endl;
    mySavingsAccount.withdraw(2000.00);
    mySavingsAccount.displayBalance();
    mySavingsAccount.checkMinimumBalance();

    return 0;
}
