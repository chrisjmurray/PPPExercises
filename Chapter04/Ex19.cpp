//  Write a program where you first enter a set of name-and-value pairs, such 
// as Joe 17 and Barbara 22. For each pair, add the name to a vector called 
// names and the number to a vector called scores (in corresponding positions,
// so that if names[7]=="Joe" then scores[7]==17). Terminate input 
// with NoName 0. Check that each name is unique and terminate with an 
// error message if a name is entered twice. Write out all the (name,score) 
// pairs, one per line.

#include "../std_lib_facilities.h"

int main () {
    vector<string> names;
    vector<int> scores;

    cout << "Input names and ages, one pair at a time: ";
    while (cin) {
        string name;
        int score;
        cin >> name >> score;
        if (name == "NoName" && score == 0) {
            break;
        }
        if (count(names.begin(), names.end(), name)) {
            error("Entered name not unique");            
        }
        else {
            names.push_back(name);
            scores.push_back(score);
        }
    }
    for (int i = 0; i < names.size(); ++i) {
        cout << names[i] << " " << scores[i] << "\n";
    }
}