/*
Make a vector holding the ten string values "zero", "one", . . . "nine".
Use that in a program that converts a digit to its corresponding
spelled-out value; e.g., the input 7 gives the output seven. Have the same
program, using the same input loop, convert spelled-out numbers into
their digit form; e.g., the input seven gives the output 7.
*/

#include "../std_lib_facilities.h"

int main() {
	vector<string> spelledNums = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	vector<string> digitNums = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
	string query;

	while (cin >> query) {
		if (query == "x") break;

		for (int i = 0; i < 10; ++i) {
			if (query == spelledNums[i]) cout << digitNums[i] << '\n';
			else if (query == digitNums[i]) cout << spelledNums[i] << '\n';
		}
	}
}