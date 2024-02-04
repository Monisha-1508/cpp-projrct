#include <iostream>
#include <vector>

class Account {
protected:
    std::string accountNumber;
    std::string accountHolderName;
    double balance;

public:
    // Constructor
    Account(std::string number, std::string holder, double initialBalance) : accountNumber(number), accountHolderName(holder), balance(initialBalance) {}

    // Member functions
    virtual void deposit(double amount) {
        balance += amount;
        std::cout << "Deposit successful. New balance: $" << balance << std::endl;
    }

    virtual void withdraw(double amount) {
        if (amount > balance) {
            std::cout << "Insufficient funds. Withdrawal unsuccessful." << std::endl;
        } else {
            balance -= amount;
            std::cout << "Withdrawal successful. New balance: $" << balance << std::endl;
        }
    }

    void inquireBalance() const {
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Account Holder: " << accountHolderName << std::endl;
        std::cout << "Current Balance: $" << balance << std::endl;
    }

    std::string getNumber() const {
        return accountNumber;
    }
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    // Constructor
    SavingsAccount(std::string number, std::string holder, double initialBalance, double rate)
        : Account(number, holder, initialBalance), interestRate(rate) {}

    // Override deposit function to add interest for savings account
    void deposit(double amount) override {
        balance += amount + (amount * interestRate / 100);
        std::cout << "Deposit successful. New balance: $" << balance << std::endl;
    }
};

class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    // Constructor
    CurrentAccount(std::string number, std::string holder, double initialBalance, double limit)
        : Account(number, holder, initialBalance), overdraftLimit(limit) {}

    // Override withdraw function to allow overdraft for current account
    void withdraw(double amount) override {
        if (amount > balance + overdraftLimit) {
            std::cout << "Withdrawal unsuccessful. Exceeds overdraft limit." << std::endl;
        } else {
            balance -= amount;
            std::cout << "Withdrawal successful. New balance: $" << balance << std::endl;
        }
    }
};

class Bank {
private:
    std::vector<Account*> accounts;

public:
    // Member functions
    void createAccount(Account* account) {
        accounts.push_back(account);
        std::cout << "Account created successfully." << std::endl;
    }

    Account* findAccount(std::string number) {
        for (auto& account : accounts) {
            if (account->getNumber() == number) {
                return account;
            }
        }
        return nullptr;
    }
};

int main() {
    Bank bank;

    // Creating savings and current accounts
    SavingsAccount johnSavings("123456", "John Doe", 1000.0, 2.5);
    CurrentAccount janeCurrent("789012", "Jane Smith", 500.0, 200.0);

    // Adding accounts to the bank
    bank.createAccount(&johnSavings);
    bank.createAccount(&janeCurrent);

    // Deposits and withdrawals for savings account
    Account* johnAccount = bank.findAccount("123456");
    if (johnAccount) {
        johnAccount->deposit(500.0);
    }

    // Withdrawals for current account
    Account* janeAccount = bank.findAccount("789012");
    if (janeAccount) {
        janeAccount->withdraw(700.0);
        janeAccount->inquireBalance();
    }

    return 0;
}
