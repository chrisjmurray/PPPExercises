// Design a program that asks users for two numbers, asks them whether 
// they want to calculate permutations or combinations, and prints out the 
// result. This will have several parts. Do an analysis of the above 
// requirements. Write exactly what the program will have to do. Then, go into 
// the design phase. Write pseudo code for the program, and break it into 
// sub-components. This program should have error checking. Make sure 
// that all erroneous inputs will generate good error messages

#include "../std_lib_facilities.h"


int permutation(int n, int k) {
    if (n < 0) throw runtime_error("permutation(): n < 0");
    if (k > n) throw runtime_error("permutation(): k > n");
    if (n == 0) return 1;
    int result = n;
    for(int i = n - 1; i > (n - k); --i) {
        result = i*result;
    }
    return result;    
}

int combination(int n, int k) {
    int result = permutation(n, k);
    for (int i = 1; i <= k; ++i) {
        result = result/i;
    }
    return result;
}

int main () {
    cout << "Enter two natural numbers: ";
    int n, k;
    cin >> n >> k;
    cout << "Enter 1 or 2 for the number permutations or combinations, respectively: ";
    int i;
    cin >> i;
    try {
        if (i == 1) {
            cout << "Permutations: " << permutation(n, k);
        }
        else if (i == 2) {
            cout << "Combinations: " << combination(n, k);
        }
    } catch (runtime_error& e) {
        cout << "Error: " <<e.what() << "\n";
    }
}