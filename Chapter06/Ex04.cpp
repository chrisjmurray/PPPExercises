/* Define a class Name_value that holds a string and a value. Rework 
exercise 19 in Chapter 4 to use a vector<Name_value> instead of 
two vectors.

Problem Statement from Ch4Ex19:
Write a program where you first enter a set of name-and-value pairs, such
as Joe 17 and Barbara 22. For each pair, add the name to a vector called
names and the number to a vector called scores (in corresponding positions, 
so that if names[7]=="Joe" then scores[7]==17). Terminate input
with NoName 0. Check that each name is unique and terminate with an
error message if a name is entered twice. Write out all the (name,score)
pairs, one per line.
*/

#include "../std_lib_facilities.h"

class Name_value {
public:
	string name;
	int value;
	Name_value(string str, int i)
		:name(str), value(i) { };
};

vector<Name_value> getPairs() {
	vector<Name_value> outVec = {};
	while (cin) {
		string name;
		cin >> name;
		for (Name_value x : outVec) {
			if (x.name == name) error("Duplicate name entered");
		}

		int val;
		cin >> val;
		if (name == "NoName" && val == 0) break;
		outVec.push_back(Name_value(name, val));
	}
	return outVec;
}

void printVec(vector<Name_value> vec) {
	for (Name_value x : vec) {
		cout << x.name << " " << x.value << endl;
	}
}

int main() {
	try {
		vector<Name_value> vec = getPairs();
		printVec(vec);
	} 
	catch (exception& e) {
		cout << e.what();
	}
}