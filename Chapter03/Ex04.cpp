// Write a program that prompts the user to enter two integer values. Store 
// these values in int variables named val1 and val2. Write your program to 
// determine the smaller, larger, sum, difference, product, and ratio of these 
// values and report them to the user.

#include "../std_lib_facilities.h"

int main() {
    int val1, val2;
    cout << "Enter two integer values: ";
    cin >> val1 >> val2;
    cout << "Smaller: " << min(val1, val2);
    cout << "\nLarger: " << max(val1, val2);
    cout << "\nSum: " << val1 + val2;
    cout << "\nDifference: " << abs(val1-val2);
    cout << "\nProduct: " << val1*val2;
    cout << "\nRatio: " << abs(val1*val2)/(val1*val2)*abs(val1) << ":" << abs(val2);
    // the extra work in the above line is to format the ratio in a more presentable way.

    return 0;
}