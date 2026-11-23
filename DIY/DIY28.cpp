//10.1
#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

int main() {
    ifstream infile("nums.txt");
    if (!infile) {
        cerr << "Error opening nums.txt for reading!" << endl;
        return 1;
    }

    int count = 0;
    long long sum = 0;
    int min_val = INT_MAX;
    int max_val = INT_MIN;
    int num;

    while (infile >> num) {
        count++;
        sum += num;
        if (num < min_val) min_val = num;
        if (num > max_val) max_val = num;
    }

    infile.close();

    if (count == 0) {
        cout << "The file is empty or contains no valid integers." << endl;
    } else {
        cout << "Count: " << count << endl;
        cout << "Sum: " << sum << endl;
        cout << "Min: " << min_val << endl;
        cout << "Max: " << max_val << endl;
    }

    return 0;
}