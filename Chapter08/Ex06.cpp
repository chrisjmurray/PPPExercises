// Write versions of the functions from exercise 5, but with a vector<string>.

#include "../std_lib_facilities.h"

void print(vector<string>& vi, string label)
{
    cout << "Label: " << label << "\n";
    for (string i : vi){
        cout << i << " ";
    }
    cout << "\n";
}

vector<string> newreverse(const vector<string>& v) {
    vector<string> v2 {};
    for (int i = v.size()-1; i>=0; i--) {
        v2.push_back(v[i]);
    }
    return v2;
}

void reverseinplace(vector<string>& v) {
    int s = v.size();
    for (int i = 0; i < s/2; ++i) {
        swap(v[i], v[s-i-1]);
    }
}

int main(){
    vector<string> v {"chris", "bob", "kat", "lexi", "dave"};
    print(v, "original vector");
    vector<string> v2 = newreverse(v);
    reverseinplace(v);
    print(v2, "newreverse");
    print(v, "reverseinplace");
}