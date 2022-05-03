// Replace Name_pair::print() with a (global) operator << and define ==
// and != for Name_pairs.

#include "../std_lib_facilities.h"

class Name_pairs{
    public:
        Name_pairs();
        void read_names(); //prompts and reads in names
        void read_ages(); //prompts per name and reads in a name for each
        void printpairs(); //prints out (name[i], age[i]) for each pair. one per line
        void sortbyname(); //sorts the vectors by name
        vector<string> getnames();
        vector<int> getages();
    private:
        vector<string> names;
        vector<int> ages;
};

vector<string> Name_pairs::getnames(){
    return names;
}

vector<int> Name_pairs::getages(){
    return ages;
}

void Name_pairs::read_names(){
    cout << "Enter names (enter quit) to finish: ";
    names = {};
    while(cin) {
        string input;
        cin >> input;
        if(input == "quit") {
            break;
        }
        names.push_back(input);
    }
}

void Name_pairs::read_ages(){
    if (size(names) == 0) {
        cout << "There are no names";
    }
    
    for (string name : names){
        cout << "Enter an age for " << name << ": ";
        int age;
        cin >> age;
        if (age < 0) error("invalid age");
        ages.push_back(age);
    }
}

void Name_pairs::sortbyname() {
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

void Name_pairs::printpairs() {
    if (names.size() != ages.size()) error("vectors different size");
    for (int i = 0; i < names.size(); ++i) {
        cout << "(" << names[i] << ", " << ages[i] << ") " << "\n";
    }
}

ostream& operator<<(ostream& os, Name_pairs np){
    vector<int> ages = np.getages();
    vector<string> names = np.getnames();
    if (names.size() != ages.size()) error("vectors different size");
    for (int i = 0; i < names.size(); ++i) {
        os << "(" << names[i] << ", " << ages[i] << ") " << "\n";
    }
    return os;
}

bool operator==(Name_pairs& np1, Name_pairs& np2) {
    np1.sortbyname();
    np2.sortbyname();
    vector<int> ages1 = np1.getages();
    vector<int> ages2 = np2.getages();
    vector<string> names1 = np1.getnames();
    vector<string> names2 = np2.getnames();
    
    if ((names1.size() != ages1.size()) || (names2.size() != ages2.size())) {
        error("invalid vectors");
    }

    if (names1.size() != names2.size()) return false;


    for(int i = 0; i < names1.size(); ++i){
        if ((names1[i] != names2[i]) || (ages1[i] != ages2[i])) return false;
    }
    return true;
}

bool operator!=(Name_pairs& np1, Name_pairs& np2){
    return !(np1 == np2);
}

Name_pairs::Name_pairs(){
    read_names();
    read_ages();
}

int main() {
    Name_pairs np1 {};
    Name_pairs np2 {};


    cout << np1;
    cout << np2;

    bool equals = (np1==np2);
    bool notequals = (np1!=np2);
    cout << "\n" << "== : " << equals;
    cout << "\n" << "!= : " << notequals;

    return 0;
}