// Design and implement a Name_pairs class holding (name,age) pairs where 
// name is a string and age is a double. Represent that as a vector<string>
// (called name) and a vector<double> (called age) member. Provide an input 
// operation read_names() that reads a series of names. Provide a read_
// ages() operation that prompts the user for an age for each name. Provide 
// a print() operation that prints out the (name[i],age[i]) pairs (one per line) 
// in the order determined by the name vector. Provide a sort() operation 
// that sorts the name vector in alphabetical order and reorganizes the age
// vector to match. Implement all “operations” as member functions. Test 
// the class (of course: test early and often).

#include "../std_lib_facilities.h"

class Name_pairs{
    public:
        Name_pairs();
        void read_names(); //prompts and reads in names
        void read_ages(); //prompts per name and reads in a name for each
        void printpairs(); //prints out (name[i], age[i]) for each pair. one per line
        void sortbyname(); //sorts the vectors by name
    private:
        vector<string> names;
        vector<int> ages;
};

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

Name_pairs::Name_pairs(){
    read_names();
    read_ages();
}

int main() {
    Name_pairs np {};

    np.sortbyname();
    np.printpairs();

    return 0;
}