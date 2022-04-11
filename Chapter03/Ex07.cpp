// Do exercise 6, but with three string values. So, if the user enters the 
// values Steinbeck, Hemingway, Fitzgerald, the output should be Fitzgerald, 
// Hemingway, Steinbeck.

#include "../std_lib_facilities.h"

int main() {
    string val1, val2, val3;
    cout << "Enter 3 single word strings to be sorted: ";
    cin >> val1 >> val2 >> val3;
    if (val2 < val1) {
        swap(val1, val2);
    }
    if (val3 < val1) {
        swap(val1, val3);
    }
    if (val3 < val2) {
        swap(val2, val3);
    }
    cout << val1 << ", " << val2 << ", " << val3;
}