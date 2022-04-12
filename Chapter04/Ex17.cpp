// Write a program that finds the min, max, and mode of a sequence of 
// strings.

// I pretty much copy/pasted my code from last exercise and changed the names/types of variables
// to fit. I also created a random string generator

#include "../std_lib_facilities.h"

int chmin = 97;
int chmax = 122;

struct strcount {
    string str;
    int count;
};

bool sortbycount(const strcount &a, const strcount &b) {
    return (a.count > b.count);
}

string randstring(int len) {
    string str;
    for(int i = 0; i < len; ++i){
        str += static_cast<char>(randint(chmin,chmax));
    }
    return str;
}

int main() {
    vector<string> strings;
    int numssize, randmin, randmax;

    //query user for multiset parameters
    cout << "I will generate the multiset for you. How many entries? ";
    cin >> numssize;
    cout << "Minimum length of string? ";
    cin >> randmin;
    cout << "Maximum length of string? ";
    cin >> randmax;

    for (int i = 0; i < numssize; ++i) {
        strings.push_back(randstring(randint(randmin, randmax)));
    }

    sort(strings);

    cout << "Multiset values: ";
    for (string s : strings) {
        cout << s << " ";
    }
    //find the multiplicity of each value in the multiset
    vector<strcount> sc;
    string val = strings[0];
    sc.push_back(strcount {val, 1});
    for (int i = 1; i < strings.size(); ++i) {
        if (strings[i] == sc.back().str){
            sc.back().count++;
        }
        else {
            sc.push_back(strcount {strings[i], 1});
        }
    }

    sort(sc.begin(), sc.end(), sortbycount);
    //find the values with the highest multiplicity
    
    int modecount = sc[0].count;
    vector<string> modes {sc[0].str};
    if (modecount != 1)
    {
        for (int i = 1; i < sc.size(); ++i) {
            if (sc[i].count == sc[0].count){
                modes.push_back(sc[i].str);
            }
            else {
                break;
            }
        }
    }
    

    cout << "\n\nMax: " << strings.back();
    cout << "\nMin: " << strings[0];
    cout << "\nModes: ";
    if (modecount == 1){
        cout << "no modes";
    }
    else {
        for (string s : modes) {
            cout << s << " ";
        }
    }
    return 0;
}