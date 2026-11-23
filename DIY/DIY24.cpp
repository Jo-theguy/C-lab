//8.3

#include <iostream>
using namespace std;

class Base {
public:
    Base() { cout << "Base constructor\n"; }
#ifdef FIXED
    virtual ~Base() { cout << "Base destructor\n"; }   // FIX
#else
    ~Base() { cout << "Base destructor\n"; }           // BUG: not virtual
#endif
};

class Derived : public Base {
    int* data;
public:
    Derived() {
        data = new int[100];             // Derived allocates memory
        cout << "Derived constructor (allocated 100 ints)\n";
    }
    ~Derived() {
        delete[] data;
        cout << "Derived destructor (memory freed)\n";
    }
};

int main() {
    Base* p = new Derived();
    delete p;                            // deleting through a Base pointer
    return 0;
}