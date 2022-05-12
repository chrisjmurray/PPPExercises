// Write a function, void to_lower(char* s), that replaces all uppercase 
// characters in the C-style string s with their lowercase equivalents. For 
// example, Hello, World! becomes hello, world!. Do not use any standard 
// library functions. A C-style string is a zero-terminated array of characters, 
// so if you find a char with the value 0 you are at the end.

#include "../std_lib_facilities.h"

void to_lower(char* s) {
    int n = 0;
    while(s[n] != 0) {
        if (s[n] >= 'A' && s[n] <= 'Z'){
            s[n] += 32;
        }
        ++n;
    }
}

int main() {
    char s[]{"TEsting tHIS sTrIng ABCDEFGHIJKLMNOPQRSTUVWXYZ8239F;;ADS"};
    to_lower(s);
    cout << s;
    return 0;
}