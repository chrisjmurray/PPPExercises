// Write a program in C++ that converts from miles to kilometers. Your 
// program should have a reasonable prompt for the user to enter a number 
// of miles. Hint: There are 1.609 kilometers to the mile.

#include "../std_lib_facilities.h"

int main() {
    double miles;
    cout << "Enter a number of miles to be converted into kilometers: ";
    cin >> miles;
    cout << miles << " m -> " << miles*1.609 << " km";

    return 0;
}