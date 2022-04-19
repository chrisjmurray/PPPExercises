// Write a function print() that prints a vector of ints to cout. Give it two 
// arguments: a string for “labeling” the output and a vector.

#include "../std_lib_facilities.h"

void print(vector<int>& vi, string label)
{
    cout << "Label: " << label << "\n";
    for (int i : vi){
        cout << i << "\n";
    }
}

int main() {
    vector<int> v {1,2,3,4,5,6,4,345,2234,2};
    print(v, "supdog");
}