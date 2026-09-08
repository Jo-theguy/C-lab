#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    cout << "Enter a word: ";
    cin >> s;
    cout << "The given string is: " << s.length() << endl;
    for (char c : s)
     cout << (char)toupper(c) << endl;
    bool pal;
size_t i=0, j = s.size() - 1;

    for (i=0; i < j; ++i, --j)
    {
        if (s[i] != s[j])
        {
            pal = false;
            cout << "The given string is not a palindrome" << endl;
            break;
        }
    
    else
        cout << s << " is not palindrome" << endl;
    }

    size_t pos = s.find("AD");
    

    if (pos==1)
        cout << "The substring 'AD' is found in the string"  << endl;
    else
        cout << "The substring 'AD' is not found in the string" << endl;

    return 0;
}