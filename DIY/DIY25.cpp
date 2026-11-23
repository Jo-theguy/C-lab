//9.1
#include <iostream>
#include <string>
#include <exception>
using namespace std;

class InsufficientFunds : public exception {
    string msg;
public:
    InsufficientFunds(double balance, double requested) {
        msg = "Insufficient funds: balance " + to_string(balance) +
              ", requested " + to_string(requested);
    }
    const char* what() const noexcept override { return msg.c_str(); }
};

class BankAccount {
    double balance;
public:
    BankAccount(double b) : balance(b) {}
    void deposit(double amt) { balance += amt; }
    void withdraw(double amt) {
        if (amt > balance)
            throw InsufficientFunds(balance, amt);   // instead of returning false
        balance -= amt;
    }
    double getBalance() const { return balance; }
};

int main() {
    BankAccount acc(5000);

    try {
        acc.withdraw(2000);
        cout << "Withdrew 2000, balance = " << acc.getBalance() << endl;

        acc.withdraw(10000);                          // too much -> throws
        cout << "This line is never reached\n";
    }
    catch (const InsufficientFunds& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << "Final balance = " << acc.getBalance() << endl;
    return 0;
}