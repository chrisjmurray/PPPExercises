// Write a function, char* strdup(const char*), that copies a C-style string 
// into memory it allocates on the free store. Do not use any standard library 
// functions. 

#include "../std_lib_facilities.h"

char* strdup(const char* c) {
    char* cc = new char[strlen(c)];
    cc = const_cast<char*>(c);
    return cc;
}

int main() {
    char c[8] = "sup dog";
    cout << c << '\n';
    char* cc = strdup(c);
    cout << cc;
}