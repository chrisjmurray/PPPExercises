// Read five names into a vector<string> name, then prompt the user for 
// the ages of the people named and store the ages in a vector<double> age. 
// Then print out the five (name[i],age[i]) pairs. Sort the names (sort(name
// .begin(),name.end())) and print out the (name[i],age[i]) pairs. The tricky 
// part here is to get the age vector in the correct order to match the sorted 
// name vector. Hint: Before sorting name, take a copy and use that to 
// make a copy of age in the right order after sorting name. 

#include "../std_lib_facilities.h"

vector<string> getnames(int n) {
    vector<string> names {};
    cout << "Enter " << n << " names: ";
    for (int i = 0; i < n; ++i) {
        string name;
        cin >> name;
        names.push_back(name);
    }
    return names;
}

vector<int> getages(const vector<string>& names) {
    vector<int> ages {};
    for (string name : names) {
        int age;
        cout << "Enter an age for " << name << ": ";
        cin >> age;
        ages.push_back(age);
    }
    return ages;
}

void sortbyname(vector<string>& names, vector<int>& ages) {
    //insertion sort that carries ages along for the ride
    for(int i = 1; i < names.size(); ++i) { 
        for(int j = i; j > 0; --j){
            if(names[j] > names[j-1]) break;
            string namecopy = names[j-1];
            names[j-1] = names[j];
            names[j] = namecopy;
            int agecopy = ages[j-1];
            ages[j-1] = ages[j];
            ages[j] = agecopy;
        }
    }
}

void sortbyage(vector<string>& names, vector<int>& ages) {
    vector<string> namesunsorted = names;
    vector<int> agesunsorted = ages;
    sort(ages);
    for (int i = 0; i < ages.size(); ++i) {
        for(int j = 0; j < ages.size(); ++j) {
            if (ages[i] == agesunsorted[j] && names[i] == namesunsorted[j]) {
                names[i] = namesunsorted[j];
                break;
            }
        }
    }
}

void printpairs(const vector<string>& names, const vector<int>& ages){
    cout << "Pairs: ";
    for (int i = 0; i < names.size(); ++i) {
        cout << "(" << names[i] << ", " << ages[i] << ") ";
    }
}

int main() {
    vector<string> names = getnames(5);
    vector<int> ages = getages(names);
    sortbyname(names, ages);
    printpairs(names, ages);
}