//8.1
#include <iostream>
using namespace std;

class Account {
protected:
    double balance;
public:
    Account(double b) : balance(b) {}
    virtual double calculateInterest() const = 0;   // pure virtual
    virtual ~Account() {}
};

class Savings : public Account {
public:
    Savings(double b) : Account(b) {}
    double calculateInterest() const override {
        return balance * 0.04;          // 4% rate
    }
};

class Current : public Account {
public:
    Current(double b) : Account(b) {}
    double calculateInterest() const override {
        return balance * 0.01;          // 1% rate
    }
};

int main() {
    Account* accounts[3];
    accounts[0] = new Savings(10000);
    accounts[1] = new Current(25000);
    accounts[2] = new Savings(5000);

    for (int i = 0; i < 3; i++) {
        cout << "Account " << i + 1
             << " interest: " << accounts[i]->calculateInterest() << endl;
    }

    for (int i = 0; i < 3; i++) delete accounts[i];
    return 0;
}