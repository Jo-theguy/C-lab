//9.2 
#include <iostream>
using namespace std;

class Overflow {
public:
    const char* what() const { return "Stack Overflow: stack is full"; }
};

class Underflow {
public:
    const char* what() const { return "Stack Underflow: stack is empty"; }
};

class Stack {
    int arr[3];
    int top;
public:
    Stack() : top(-1) {}
    void push(int x) {
        if (top == 2) throw Overflow();
        arr[++top] = x;
    }
    int pop() {
        if (top == -1) throw Underflow();
        return arr[top--];
    }
};

int main() {
    Stack s;

    try {
        s.push(10);
        s.push(20);
        s.push(30);
        cout << "Pushed 10, 20, 30\n";
        s.push(40);                                  // overflow
    }
    catch (const Overflow& e) {
        cout << "Caught: " << e.what() << endl;
    }

    try {
        for (int i = 0; i < 4; i++)                  // 4th pop underflows
            cout << "Popped: " << s.pop() << endl;
    }
    catch (const Underflow& e) {
        cout << "Caught: " << e.what() << endl;
    }

    return 0;
}