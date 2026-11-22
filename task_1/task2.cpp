// OOP Using C++ - Task 2 (Weeks 7-13)
// Student Result Management System
// Concepts: inheritance, runtime polymorphism (virtual functions), exception handling,
//           file handling, STL vector, STL algorithms and lambda expressions

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
using namespace std;

// ---------- Custom exception for invalid marks ----------
class InvalidMarksException : public runtime_error {
public:
    explicit InvalidMarksException(const string& msg) : runtime_error(msg) {}
};

// ---------- Base class ----------
class Student {
protected:
    int rollNo;
    string name;
public:
    Student(int r = 0, const string& n = "") : rollNo(r), name(n) {}
    virtual ~Student() {}

    int getRollNo() const { return rollNo; }
    string getName() const { return name; }

    // virtual functions -> runtime polymorphism
    virtual void displayDetails() const {
        cout << left << setw(8) << rollNo << setw(18) << name;
    }
    virtual void displayMarks() const {
        cout << "Marks not available for base Student\n";
    }
    virtual int getTotal() const { return 0; }
    virtual string toFileString() const {
        return to_string(rollNo) + "," + name;
    }
};

// ---------- Derived class ----------
class Result : public Student {
private:
    vector<int> marks;   // marks in 3 subjects
    int total;
    double percentage;
    string status;

    void validate(int m) const {
        if (m < 0 || m > 100)
            throw InvalidMarksException("Invalid marks entered: " + to_string(m) +
                                        " (must be between 0 and 100)");
    }
    void compute() {
        total = 0;
        for (int m : marks) total += m;
        percentage = total / static_cast<double>(marks.size());
        bool failed = any_of(marks.begin(), marks.end(), [](int m) { return m < 40; });
        status = failed ? "FAIL" : "PASS";
    }

public:
    Result(int r, const string& n, const vector<int>& m) : Student(r, n), marks(m) {
        for (int x : marks) validate(x);   // may throw
        compute();
    }

    void displayDetails() const override {
        Student::displayDetails();
    }
    void displayMarks() const override {
        for (int m : marks) cout << setw(7) << m;
        cout << setw(8) << total << setw(9) << fixed << setprecision(2) << percentage
             << setw(8) << status << "\n";
    }
    int getTotal() const override { return total; }
    string getStatus() const { return status; }

    string toFileString() const override {
        string s = Student::toFileString();
        for (int m : marks) s += "," + to_string(m);
        return s;
    }
};

// ---------- File handling ----------
void saveToFile(const vector<unique_ptr<Student>>& records, const string& filename) {
    ofstream out(filename);
    if (!out) throw runtime_error("Cannot open file for writing: " + filename);
    for (const auto& s : records) out << s->toFileString() << "\n";
    cout << "Records saved to " << filename << "\n";
}

void loadFromFile(vector<unique_ptr<Student>>& records, const string& filename) {
    ifstream in(filename);
    if (!in) throw runtime_error("Cannot open file for reading: " + filename);
    records.clear();
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string token;
        vector<string> parts;
        while (getline(ss, token, ',')) parts.push_back(token);
        if (parts.size() < 5) continue;
        try {
            vector<int> m = {stoi(parts[2]), stoi(parts[3]), stoi(parts[4])};
            records.push_back(make_unique<Result>(stoi(parts[0]), parts[1], m));
        } catch (const exception& e) {
            cout << "Skipping bad record: " << e.what() << "\n";
        }
    }
    cout << "Records loaded from " << filename << "\n";
}

// ---------- Display helpers ----------
void printHeader() {
    cout << left << setw(8) << "Roll" << setw(18) << "Name"
         << right << setw(7) << "Sub1" << setw(7) << "Sub2" << setw(7) << "Sub3"
         << setw(8) << "Total" << setw(9) << "Percent" << setw(8) << "Result" << "\n";
    cout << string(72, '-') << "\n";
}

void displayAll(const vector<unique_ptr<Student>>& records) {
    if (records.empty()) { cout << "No records to display.\n"; return; }
    printHeader();
    for (const auto& s : records) {
        s->displayDetails();   // runtime polymorphism
        s->displayMarks();
    }
}

// ---------- Add a student with exception handling ----------
void addStudent(vector<unique_ptr<Student>>& records) {
    int roll;
    string name;
    vector<int> m(3);
    cout << "Enter roll number: ";
    cin >> roll;
    cout << "Enter name (no spaces): ";
    cin >> name;
    for (int i = 0; i < 3; i++) {
        cout << "Enter marks for subject " << i + 1 << " (0-100): ";
        cin >> m[i];
    }
    try {
        records.push_back(make_unique<Result>(roll, name, m));
        cout << "Student added successfully.\n";
    } catch (const InvalidMarksException& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

// ---------- Find students above a given total using lambda + STL ----------
void showAbove(const vector<unique_ptr<Student>>& records, int limit) {
    vector<const Student*> selected;
    for (const auto& s : records) selected.push_back(s.get());

    // remove_if with lambda keeps only students with total > limit
    selected.erase(remove_if(selected.begin(), selected.end(),
                   [limit](const Student* s) { return s->getTotal() <= limit; }),
                   selected.end());

    // sort descending by total using lambda
    sort(selected.begin(), selected.end(),
         [](const Student* a, const Student* b) { return a->getTotal() > b->getTotal(); });

    cout << "\nStudents scoring above " << limit << " total marks: "
         << selected.size() << "\n";
    if (selected.empty()) return;
    printHeader();
    for (const Student* s : selected) {
        s->displayDetails();
        s->displayMarks();
    }
}

int main() {
    vector<unique_ptr<Student>> records;
    const string filename = "students.txt";
    int choice;

    do {
        cout << "\n===== Student Result Management System =====\n"
             << "1. Add student\n"
             << "2. Display all students\n"
             << "3. Save records to file\n"
             << "4. Load records from file\n"
             << "5. Show students above a specified total\n"
             << "6. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        try {
            switch (choice) {
                case 1: addStudent(records); break;
                case 2: displayAll(records); break;
                case 3: saveToFile(records, filename); break;
                case 4: loadFromFile(records, filename); break;
                case 5: {
                    int limit;
                    cout << "Enter total marks limit: ";
                    cin >> limit;
                    showAbove(records, limit);
                    break;
                }
                case 6: cout << "Exiting program.\n"; break;
                default: cout << "Invalid choice.\n";
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    } while (choice != 6);

    return 0;
}