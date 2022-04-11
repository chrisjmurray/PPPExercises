// Write a program that takes an operation followed by two operands and 
// outputs the result. For example:
// + 100 3.14
// * 4 5
//  Read the operation into a string called operation and use an 
// if-statement to figure out which operation the user wants, for example, 
// if (operation=="+"). Read the operands into variables of type double. 
// Implement this for operations called +, –, *, /, plus, minus, mul, and div 
// with their obvious meanings.

#include "../std_lib_facilities.h"

int main() {
    string operation;
    double val1, val2;
    cout << "Enter an operator followed by 2 operands: ";
    cin >> operation >> val1 >> val2;
    if (operation == "+" || operation == "plus") {
        cout << val1 + val2;
    }
    if (operation == "-" || operation == "minus") {
        cout << val1 - val2;
    }
    if (operation == "*" || operation == "mul") {
        cout << val1 * val2;
    }
    if (operation == "/" || operation == "div") {
        cout << val1 / val2;
    }
    
    return 0;
}