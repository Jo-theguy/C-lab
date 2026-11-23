//10.3
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Student {
public:
    string name;
    double marks;
};

int main() {
    // Step 1: Write sample student data to a file (optional simulation step)
    {
        ofstream outfile("students.txt");
        outfile << "Alice 85.5\n";
        outfile << "Bob 92.0\n";
        outfile << "Charlie 88.0\n";
        outfile << "Diana 95.5\n";
    }

    // Step 2: Read records back into a vector of Student objects
    ifstream infile("students.txt");
    if (!infile) {
        cerr << "Error opening students.txt for reading!" << endl;
        return 1;
    }

    vector<Student> students;
    string name;
    double marks;

    while (infile >> name >> marks) {
        students.push_back({name, marks});
    }
    infile.close();

    if (students.empty()) {
        cout << "No student records found." << endl;
        return 0;
    }

    // Step 3: Find and print the topper
    int topper_index = 0;
    for (size_t i = 1; i < students.size(); ++i) {
        if (students[i].marks > students[topper_index].marks) {
            topper_index = i;
        }
    }

    cout << "Topper: " << students[topper_index].name 
         << " with " << students[topper_index].marks << " marks." << endl;

    return 0;
}