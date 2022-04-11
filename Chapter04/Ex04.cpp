/*
Write a program to play a numbers guessing game. The user thinks of a
number between 1 and 100 and your program asks questions to figure
out what the number is (e.g., Is the number you are thinking of less than
50?). Your program should be able to identify the number after asking
no more than seven questions. Hint: Use the < and <= operators and the
if-else construct.
*/

#include "../std_lib_facilities.h"

int main() {
	int max = 100;  
	int min = 1;   

	cout << "Think of an integer between " << min << " and " << max << '\n';

	while (min != max) {
        int guess = (max + min + 1) / 2;
		cout << "Is your number lower than "<<guess<<"? (y/n) ";
        char inp;
        cin >> inp;
        if (inp == 'y') {
            max = guess-1;
        }
        else {
            min = guess;
        }
	}
	cout << "Is your number " << min << "?";
}