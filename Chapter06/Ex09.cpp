// Write a program that reads digits and composes them into integers. For 
// example, 123 is read as the characters 1, 2, and 3. The program should 
// output 123 is 1 hundred and 2 tens and 3 ones. The number should be 
// output as an int value. Handle numbers with one, two, three, or four 
// digits. Hint: To get the integer value 5 from the character '5' subtract '0', 
// that is, '5' - '0'==5.

#include "../std_lib_facilities.h"

vector<string> magnitudes = {"one", "ten", "hundred", "thousand"};

int main() {
    string num;
    cout << "Enter a number up to four digits: ";
    cin >> num;
    string reversenum;
    for (char ch : num) {
        if (!isdigit(ch)) {
            error("Invalid input");
        }
    }
    int len = num.size();
    if (len > 4) error("Invalid input");
    for (int i = 0; i < len; ++i) {
        if (num[i] == '1') {
            cout << num[i] << " " << magnitudes[len - 1 - i] << " ";
        }
        else {
            cout << num[i] << " " << magnitudes[len - 1 - i] << "s ";
        }
    }
    return 0;
}