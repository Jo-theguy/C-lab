//9.3

#include <iostream>
#include <exception>
using namespace std;

class MathError : public exception {
public:
    const char* what() const noexcept override { return "Math error"; }
};

class DivideByZero : public MathError {
public:
    const char* what() const noexcept override { return "Division by zero"; }
};

double divide(double a, double b) {
    if (b == 0) throw DivideByZero();
    return a / b;
}

int main() {
    cout << "--- WRONG order: base class first ---\n";
    try {
        divide(10, 0);
    }
    catch (const MathError& e) {                 // catches DivideByZero too
        cout << "MathError handler caught: " << e.what() << endl;
    }
    catch (const DivideByZero& e) {              // never reached
        cout << "DivideByZero handler caught: " << e.what() << endl;
    }

    cout << "\n--- CORRECT order: derived class first ---\n";
    try {
        divide(10, 0);
    }
    catch (const DivideByZero& e) {              // specific first
        cout << "DivideByZero handler caught: " << e.what() << endl;
    }
    catch (const MathError& e) {                 // general after
        cout << "MathError handler caught: " << e.what() << endl;
    }

    return 0;
}