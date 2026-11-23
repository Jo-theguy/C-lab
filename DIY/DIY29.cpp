//10.2
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream infile("in.txt");
    if (!infile) {
        cerr << "Error opening in.txt for reading!" << endl;
        return 1;
    }

    ofstream outfile("out.txt");
    if (!outfile) {
        cerr << "Error opening out.txt for writing!" << endl;
        infile.close();
        return 1;
    }

    string line;
    int line_num = 1;

    while (getline(infile, line)) {
        outfile << line_num << ": " << line << endl;
        line_num++;
    }

    infile.close();
    outfile.close();

    cout << "Successfully copied and line-numbered " << line_num - 1 << " lines to out.txt." << endl;

    return 0;
}