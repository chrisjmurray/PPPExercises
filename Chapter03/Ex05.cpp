// Modify the Ex04 to ask the user to enter floating-point values 
// and store them in double variables.

#include "../std_lib_facilities.h"

int main() {
    double val1, val2;
    cout << "Enter two integer values: ";
    cin >> val1 >> val2;
    cout << "Smaller: " << min(val1, val2);
    cout << "\nLarger: " << max(val1, val2);
    cout << "\nSum: " << val1 + val2;
    cout << "\nDifference: " << abs(val1-val2);
    cout << "\nProduct: " << val1*val2;
    cout << "\nRatio: " << abs(val1*val2)/(val1*val2)*abs(val1) << ":" << abs(val2);
    // the extra work in the above line is to format the ratio in a more presentable way.
}

