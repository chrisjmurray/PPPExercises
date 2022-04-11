/*
Write a program that performs as a very simple calculator. Your calculator
should be able to handle the four basic math operations add, subtract,
multiply, and divide on two input values. Your program should prompt
the user to enter three arguments: two double values and a character to
represent an operation. If the entry arguments are 35.6, 24.1, and '+', the
program output should be The sum of 35.6 and 24.1 is 59.7. In Chapter 6
we look at a much more sophisticated simple calculator.
*/

#include "../std_lib_facilities.h"

int main() {
	double val1, val2;
	char operation;
	double result;
	cout << "Calculator input format: value value operation. e.g. 34 42.3 +\n";
	while (cin >> val1 >> val2 >> operation) {
		switch (operation) {
		case '+':
			result = val1 + val2;
			break;
		case '-':
			result = val1 - val2;
			break;
		case '*':
			result = val1 * val2;
			break;
		case '/':
			result = val1 / val2;
			break;
		default:
			break;
		}
		cout << "Result: " << result << "\n";
	}
}