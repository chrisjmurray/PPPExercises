// How many bytes are there in an int? In a double? In a bool? Do not use
// sizeof except to verify your answer

//int - 4 bytes
//double - 8 bytes
//bool - 1 byte

#include "../std_lib_facilities.h"

int main() {
    int x[2] {1,2};
    double y[2] {1,2};
    bool z[2] {true, true};
    cout << "int: " << &x[0] << " " << &x[1];
    cout << "\ndouble: " << &y[0] << " " << &y[1];
    cout << "\nbool: " << &z[0] << " " << &z[1];

    cout << "\n\nint size: " << sizeof(int);
    cout << "\ndouble size: " << sizeof(double);
    cout << "\nbool size: " << sizeof(bool);
}