// Write a program that produces the sum of all the numbers in a file of 
// whitespace-separated integers.

#include "../std_lib_facilities.h"

void writeintegers(string filename, int numints) {
    ofstream ost{filename};
    if (!ost) error("can't open output file ", filename);
    for (int i = 0; i < numints; ++i){
        ost << randint(1000) << " ";
    }
}

vector<int> readintegers(string filename) {
    ifstream ist {filename};
    if (!ist) error("can't open input file ", filename);
    vector<int> v {};
    for (int i; ist>>i;) {
        v.push_back(i);
    }
    return v;
}

int sumvector(const vector<int>& v) {
    int sum {0};
    for (int i : v) {
        sum += i;
    }

    return sum;
}

int main() {
    string filename = "Ex01.txt";
    writeintegers(filename, 51);
    vector<int> v = readintegers(filename);
    int sum = sumvector(v);

    cout << "Sum: " << sum;
}