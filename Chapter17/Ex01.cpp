// What is the output format of pointer values on your implementation? 
// Hint: Don’t read the documentation.

//Output was in hex format
#include <iostream>

int main() {
    int* x = new int{5};
    std::cout << "Output for pointer x: " << x;
    delete x;
    
    return 0;
}