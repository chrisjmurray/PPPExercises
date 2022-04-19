// Create a vector of Fibonacci numbers and print them using the function 
// from exercise 2. To create the vector, write a function, fibonacci(x,y,v,n), 
// where integers x and y are ints, v is an empty vector<int>, and n is the 
// number of elements to put into v; v[0] will be x and v[1] will be y. A Fibonacci 
// number is one that is part of a sequence where each element is the 
// sum of the two previous ones. For example, starting with 1 and 2, we get 
// 1, 2, 3, 5, 8, 13, 21, . . . . Your fibonacci() function should make such a 
// sequence starting with its x and y arguments.

#include "../std_lib_facilities.h"

void fibonacci(int x, int y, vector<int>& v, int n){
    if (n < 0 || x < 0 || y < 0 || v.size() > 0) error("fibonacci(): Invalid parameter");
    if (n == 0){
        return;
    }
    if (n == 1) {
        v.push_back(x);
        return;
    }
    if (n == 2) {
        v.push_back(x);
        v.push_back(y);
        return;
    }
    else {
        v.push_back(x);
        v.push_back(y);
        for(int i = 2; i < n; ++i) {
            v.push_back(v[i-1]+v[i-2]);
        }
    }

}

void print(vector<int>& vi, string label)
{
    cout << "Label: " << label << "\n";
    for (int i : vi){
        cout << i << "\n";
    }
}

int main() {
    vector<int> v {};
    fibonacci(1, 1, v, 50);
    print(v, "Fibonacci");
}

// 4. An int can hold integers only up to a maximum number. 
// Find an approximation of that maximum number by using fibonacci().

// values become erroneous around 2 billion