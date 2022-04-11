/*
Write a program that takes an input value n and then finds the first n
primes.
*/

#include "../std_lib_facilities.h"

int main() {
	vector<int> foundPrimes = {2};
	int n;

	cout << "How many primes would you like to find? ";
	cin >> n;

	if (n == 1) cout << 2;
	else {
		int i = 2;
		while (foundPrimes.size() < n) {
			++i;
			bool divisible = false;

			//this loop checks to see if any of the found primes thus far are factors
			//of i. if yes, i is not prime, go to next break out and go to next i.
			for (int x : foundPrimes) {
				if (i % x == 0) {
					divisible = true;
					break;
				}
			}
			//add i to vector since no divisors were found
			if (!divisible) foundPrimes.push_back(i);
		}
	}

	for (int x : foundPrimes) {
		cout << x << '\n';
	}
	return 0;
}