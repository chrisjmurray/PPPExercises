/*
Modify the mini calculator from exercise 5 to accept (just) single-digit
numbers written as either digits or spelled out.
*/

#include "../std_lib_facilities.h"

double strToDouble(string strVal) {
	vector<string> spelledNums = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	vector<string> digitNums = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

	for (int i = 0; i < 10; ++i) {
		if (strVal == spelledNums[i]) return i;
		if (strVal == digitNums[i]) return i;
		if (i == 9) return -1; //returns -1 to signal that the string wasn't found in the vector
	}
}

int main() {
	string strVal1, strVal2;
	char operation;
	double result;
	cout << "Calculator input format: value value operation. e.g. four three +\nOnly accepts spelled out single digits for values\n";
	while (cin >> strVal1 >> strVal2 >> operation) {
		double val1 = strToDouble(strVal1);
		double val2 = strToDouble(strVal2);
		
		//this line provides an exit from the program, strToDouble returns -1 if value input is undefined.
		if (val1 == -1 || val2 == -1) break;

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