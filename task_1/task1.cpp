#include <iostream>
#include <cstring>
using namespace std;

class Student {
private:
    int rollNo;
    char* name;          
    float marks;

    static int count;    

public:
    
    Student(int r, const char* n, float m) {
        rollNo = r;
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        marks = m;
        count++;
    }

    
    Student(const Student& s) {
        rollNo = s.rollNo;
        name = new char[strlen(s.name) + 1];
        strcpy(name, s.name);
        marks = s.marks;
        count++;
    }

    
    ~Student() {
        delete[] name;
        count--;
    }

    
    int getRollNo() const { return rollNo; }
    const char* getName() const { return name; }
    float getMarks() const { return marks; }

    
    void setMarks(float m) {
        marks = m;
    }
    void setMarks(float m1, float m2, float m3) {   
        marks = (m1 + m2 + m3) / 3.0f;
    }

    
    void display() const {
        cout << "Roll No: " << rollNo << ", Name: " << name
             << ", Marks: " << marks << endl;
    }
    void display(bool showGrade) const {
        display();
        if (showGrade) {
            char grade;
            if (marks >= 90) grade = 'A';
            else if (marks >= 75) grade = 'B';
            else if (marks >= 60) grade = 'C';
            else if (marks >= 40) grade = 'D';
            else grade = 'F';
            cout << "Grade: " << grade << endl;
        }
    }

    
    static int getCount() { return count; }

    
    bool operator>(const Student& other) const {
        return marks > other.marks;
    }

    
    friend void showDetails(const Student& s);
};

int Student::count = 0;

void showDetails(const Student& s) {
    cout << "[Friend] " << s.name << " (Roll " << s.rollNo
         << ") scored " << s.marks << endl;
}

int main() {
    Student s1(101, "Asha", 82.5f);
    Student s2(102, "Ravi", 74.0f);
    Student s3(103, "Meera", 0);

    s3.setMarks(88, 92, 85);   
    s2.setMarks(79.5f);      

    cout << "--- Student Details ---" << endl;
    s1.display();
    s2.display(true);
    s3.display(true);

    cout << "\n--- Friend Function ---" << endl;
    showDetails(s1);

    cout << "\n--- Comparison using > operator ---" << endl;
    if (s1 > s2)
        cout << s1.getName() << " has higher marks than " << s2.getName() << endl;
    else
        cout << s2.getName() << " has higher marks than or equal to " << s1.getName() << endl;

    if (s3 > s1)
        cout << s3.getName() << " has higher marks than " << s1.getName() << endl;
    else
        cout << s1.getName() << " has higher marks than or equal to " << s3.getName() << endl;

    cout << "\nTotal students created: " << Student::getCount() << endl;

    Student* sp = new Student(104, "Kiran", 91.0f);
    cout << "After creating a dynamic object, total students: "
         << Student::getCount() << endl;
    delete sp;
    cout << "After deleting it, total students: " << Student::getCount() << endl;

    return 0;
}