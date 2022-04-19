// Write two functions that reverse the order of elements in a vector<int>. 
// For example, 1, 3, 5, 7, 9 becomes 9, 7, 5, 3, 1. The first reverse function 
// should produce a new vector with the reversed sequence, leaving its original 
// vector unchanged. The other reverse function should reverse the 
// elements of its vector without using any other vectors (hint: swap).

#include "../std_lib_facilities.h"

void print(vector<int>& vi, string label)
{
    cout << "Label: " << label << "\n";
    for (int i : vi){
        cout << i << " ";
    }
    cout << "\n";
}

vector<int> newreverse(const vector<int>& v) {
    vector<int> v2 {};
    for (int i = v.size()-1; i>=0; i--) {
        v2.push_back(v[i]);
    }
    return v2;
}

void reverseinplace(vector<int>& v) {
    int s = v.size();
    for (int i = 0; i < s/2; ++i) {
        swap(v[i], v[s-i-1]);
    }
}

int main(){
    vector<int> v {1,2,3,4,5,6,7,8,9, 10};
    print(v, "original vector");
    vector<int> v2 = newreverse(v);
    reverseinplace(v);
    print(v2, "newreverse");
    print(v, "reverseinplace");
}