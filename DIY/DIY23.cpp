//8.2
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Logger {
public:
    virtual void write(const string& msg) = 0;
    virtual ~Logger() {}
};

class ConsoleLogger : public Logger {
public:
    void write(const string& msg) override {
        cout << "[Console] " << msg << endl;
    }
};

class FileLogger : public Logger {
    ofstream file;
public:
    FileLogger(const string& filename) : file(filename, ios::app) {}
    void write(const string& msg) override {
        file << "[File] " << msg << endl;
        cout << "(written to file)\n";
    }
    ~FileLogger() { file.close(); }
};

int main() {
    Logger* logger = nullptr;
    int choice;

    do {
        cout << "\n1. Console logger\n2. File logger\n0. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            delete logger;                       // remove the previous logger
            if (choice == 1) logger = new ConsoleLogger();
            else             logger = new FileLogger("log.txt");

            logger->write("Hello from the logger!");   // same call, different behaviour
        }
    } while (choice != 0);

    delete logger;
    return 0;
}