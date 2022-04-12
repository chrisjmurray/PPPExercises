// Write a program to solve quadratic equations. A quadratic equation is of 
// the form ax^2 + bx + c = 0.
// If you don’t know the quadratic formula for solving such an expression, 
// do some research. Remember, researching how to solve a problem is often necessary 
// before a programmer can teach the computer how to solve 
// it. Use doubles for the user inputs for a, b, and c. Since there are two 
// solutions to a quadratic equation, output both x1 and x2.

#include "../std_lib_facilities.h"
int main() {
    cout << "Enter the coefficients from the form a*x^2+b*x+c = 0: ";
    double a, b, c;
    cin >> a >> b >> c;
    double underroot = pow(a, 2) - 4*a*c;
    if (underroot < 0) {
        cout << "No real zeroes";
        return 0;
    }
    double root1 = (-b+pow(underroot, .5))/(2*a);
    double root2 = (-b-pow(underroot, .5))/(2*a);
    cout <<"Roots: " << root1 << ", " << root2;
}