// Write a function that takes a vector<string> argument and returns a 
// vector<int> containing the number of characters in each string. Also 
// find the longest and the shortest string and the lexicographically first and 
// last string. How many separate functions would you use for these tasks?

#include "../std_lib_facilities.h"

vector<int> numchar(const vector<string>& v) {
    vector<int> nums {};
    for(string s : v){
        nums.push_back(size(s));
    }
    return nums;
}

void sortbyname(vector<string>& names, vector<int>& lens) {
    //insertion sort that carries lengths along for the ride
    for(int i = 1; i < names.size(); ++i) { 
        for(int j = i; j > 0; --j){
            if(names[j] > names[j-1]) break;
            string namecopy = names[j-1];
            names[j-1] = names[j];
            names[j] = namecopy;
            int lencopy = lens[j-1];
            lens[j-1] = lens[j];
            lens[j] = lencopy;
        }
    }
}

void sortbylength(vector<string>& names, vector<int>& lens) {
    //insertion sort that carries names along for the ride
    for(int i = 1; i < lens.size(); ++i) { 
        for(int j = i; j > 0; --j){
            if(lens[j] > lens[j-1]) break;
            string namecopy = names[j-1];
            names[j-1] = names[j];
            names[j] = namecopy;
            int lencopy = lens[j-1];
            lens[j-1] = lens[j];
            lens[j] = lencopy;
        }
    }
}

void printpairs(const vector<string>& names, const vector<int>& lens){
    cout << "Pairs: ";
    for (int i = 0; i < names.size(); ++i) {
        cout << "(" << names[i] << ", " << lens[i] << ") ";
    }
}

int main(){
    vector<string> strings = {"hello", "whatsup", "never", "probly", "notlikely", "sup", "hi"};
    vector<int> lengths = numchar(strings);
    printpairs(strings, lengths);
    sortbylength(strings, lengths);
    printpairs(strings, lengths);
    sortbyname(strings, lengths);
    printpairs(strings, lengths);
}