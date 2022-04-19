// Write a function that finds the smallest and the largest element of a vector
// argument and also computes the mean and the median. Do not use global 
// variables. Either return a struct containing the results or pass them back 
// through reference arguments. Which of the two ways of returning several 
// result values do you prefer and why?

// In this case, I prefer returning a struct containing the results. It makes it 
// easier to keep track of the data

#include "../std_lib_facilities.h"

struct stats{
    double min;
    double max;
    double mean;
    double median;
};
double maxv(const vector<double>& v) {
    double max = v[0];
    for (int i = 1; i < v.size(); ++i) {
        if (v[i] > max) max = v[i];
    }
    return max;
}
double minv(const vector<double>& v) {
    double min = v[0];
    for (int i = 1; i < v.size(); ++i) {
        if (v[i] < min) min = v[i];
    }
    return min;
}
double meanv(const vector<double>& v){
    double sum {0.0};
    for (double d : v) {
        sum += d;
    }

    return sum/v.size();
}
double medianv(vector<double> v) {
    sort(v);
    if (v.size()%2){
        int i = (v.size()-1)/2;
        return v[i];
    }
    else {
        int i = v.size()/2;
        return (v[i]+v[i-1])/2;
    }
}
stats getstats(const vector<double> v){
    if (v.size() == 0 )  error("getstat(): empty vector");
    return stats{minv(v), maxv(v), meanv(v), medianv(v)};
}

int main() {
    vector<double> v1 {3.4, -2.23, 0.0, 55.2};
    vector<double> v2 {-5.4, 33.6, 8.7, -99.2, 1.2};
    stats s1 = getstats(v1);
    cout << s1.min << " " << s1.max << " " << s1.mean << " " << s1.median;
}