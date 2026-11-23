//7.2 
#include <iostream>
#include <string>
using namespace std;

class Shape {
protected:
    string name;
public:
    Shape(string n) : name(n) {
        cout << "Shape constructor  (name = " << name << ")\n";
    }
    ~Shape() { cout << "Shape destructor\n"; }
};

class Polygon : public Shape {
protected:
    int sides;
public:
    Polygon(string n, int s) : Shape(n), sides(s) {
        cout << "Polygon constructor (sides = " << sides << ")\n";
    }
    ~Polygon() { cout << "Polygon destructor\n"; }
};

class Rectangle : public Polygon {
    double area;
public:
    Rectangle(string n, int s, double a) : Polygon(n, s), area(a) {
        cout << "Rectangle constructor (area = " << area << ")\n";
    }
    ~Rectangle() { cout << "Rectangle destructor\n"; }
};

int main() {
    Rectangle r("Rectangle", 4, 50.0);
    cout << "--- object created, now leaving main ---\n";
    return 0;
}