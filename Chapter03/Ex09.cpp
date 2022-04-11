//  Write a program that converts spelled-out numbers such as “zero” and 
// “two” into digits, such as 0 and 2. When the user inputs a number, the 
// program should print out the corresponding digit. Do it for the values 0, 
// 1, 2, 3, and 4 and write out "not a number I know" if the user enters 
// something that doesn’t correspond, such as "stupid computer!"

#include "../std_lib_facilities.h"

int main() {
    int val;
    cout << "Enter a number to be spelled out: ";
    cin >> val;
    string result;
    switch (val) {
        case 0:
            result = "zero";
            break;
        case 1:
            result = "one";
            break;
        case 2:
            result = "two";
            break;
        case 3:
            result = "three";
            break;
        case 4:
            result = "four";
            break;
        default:
            result = "not a number I know";
    }
    cout << result;

    return 0;
}