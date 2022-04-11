// Write a program to test an integer value to determine if it is odd or 
// even. As always, make sure your output is clear and complete. In other 
// words, don’t just output yes or no. Your output should stand alone, 
// like The value 4 is an even number

#include "../std_lib_facilities.h"

int main() {
    int val;
    cout << "Enter an integer to test its parity: ";
    cin >> val;
    string result = (val%2)? "odd":"even";
    cout << "The value " << val << " is an " << result << " number";
}