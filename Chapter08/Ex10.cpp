// Write a function maxv() that returns the largest element of a vector
// argument

#include "../std_lib_facilities.h"

double maxv(const vector<double>& v) {
    double max = v[0];
    for (int i = 1; i < v.size(); ++i) {
        if (v[i] > max) max = v[i];
    }
    return max;
}

int main() {
    vector<double> v1 {3.4, -2.23, 0.0, 55.2, -64.8};
    vector<double> v2 {-5.4, 33.6, 8.7, -99.2, 1.2};
    cout << maxv(v1) << "\n";
    cout << maxv(v2);
}