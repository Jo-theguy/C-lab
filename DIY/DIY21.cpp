//7.3

#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
public:
    Person(string n = "Unknown") : name(n) {
        cout << "Person constructor (" << name << ")\n";
    }
    void show() const { cout << "Name: " << name << endl; }
};

class Student : virtual public Person {
protected:
    int rollNo;
public:
    Student(string n, int r) : Person(n), rollNo(r) {
        cout << "Student constructor\n";
    }
};

class Employee : virtual public Person {
protected:
    int empId;
public:
    Employee(string n, int e) : Person(n), empId(e) {
        cout << "Employee constructor\n";
    }
};

class TA : public Student, public Employee {
public:
    // The most derived class constructs the virtual base directly
    TA(string n, int r, int e)
        : Person(n), Student(n, r), Employee(n, e) {
        cout << "TA constructor\n";
    }
    void display() const {
        show();   // no ambiguity, only one Person subobject
        cout << "Roll No: " << rollNo << ", Emp ID: " << empId << endl;
    }
};

int main() {
    TA t("Keertana", 91, 5001);
    t.display();
    return 0;
}