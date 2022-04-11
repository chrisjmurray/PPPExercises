/*
Create a program to find all the prime numbers between 1 and 100. There
is a classic method for doing this, called the Sieve of Eratosthenes. If
you don't know that method, get on the web and look it up. Write your
program using this method.

Modify the program described in the previous exercise to take an input
value max and then find all prime numbers from 1 to max.
*/

#include "../std_lib_facilities.h"

int main() {
	int upperLimit;
	cout << "What is the upper limit of your prime search? ";
	cin >> upperLimit;
	upperLimit += 1; //correction because we're using the value of the index to represent the number
	//1 for not prime. 0 for prime.
	vector<int> primes(upperLimit);
	primes[0] = 1; //zero is not prime
	primes[1] = 1; //one is not prime
	
	//Here lies the sieve.
	for (int i = 0; i < upperLimit; ++i) {
		if (primes[i]==0) {
			int j = 2;
			while (j * i < upperLimit) {
				primes[i * j] = 1;
				++j;
			}
		}
	}
	for (int i = 0; i < upperLimit; ++i) {
		if (primes[i]==0) cout << i << "\n";
	}

	return 0;
}