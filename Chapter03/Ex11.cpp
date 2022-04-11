// Write a program that prompts the user to enter some number of pennies 
// (1-cent coins), nickels (5-cent coins), dimes (10-cent coins), quarters 
// (25-cent coins), half dollars (50-cent coins), and one-dollar coins 
// (100-cent coins). Query the user separately for the number of each size 
// CHAPTER 3 POSTSCRIPT 87
// coin, e.g., “How many pennies do you have?” Then your program should 
// print out something like this:
// You have 23 pennies.
// You have 17 nickels.
// You have 14 dimes.
// You have 7 quarters.
// You have 3 half dollars.
// The value of all of your coins is 573 cents.
//  Make some improvements: if only one of a coin is reported, make the 
// output grammatically correct, e.g., 14 dimes and 1 dime (not 1 dimes). 
// Also, report the sum in dollars and cents, i.e., $5.73 instead of 573 cents.

#include "../std_lib_facilities.h"

class Coin {
    public:
        string singular;
        string plural;
        int number;
        double singleValue;
        void queryNumber();
        double getValue();
        void printNumber();
        Coin(string s, string p, double sv);
};

Coin::Coin(string s, string p, double sv){
    singular = s;
    plural = p;
    singleValue = sv;
    queryNumber();
}

double Coin::getValue() {
    return number*singleValue;
}

void Coin::queryNumber() {
    cout << "How many " << plural << " do you have? ";
    cin >> number;
}

void Coin::printNumber() {
    if (number == 1) {
        cout << "You have 1 " << singular << "\n";
        
    }
    else {
        cout << "You have " << number << " " << plural << "\n";;
    }
}


int main() {
    double totalValue;
    vector<Coin> coins = {Coin("penny", "pennies", .01), Coin("nickel", "nickels", .05), Coin("dime", "dimes", .1),
                          Coin("quarter", "quarters", .25), Coin("half-dollar", "half-dollars", .5), 
                          Coin("dollar coin", "dollar coins", 1.00)};
    for(Coin c : coins){
        totalValue += c.getValue();
    }
    for(Coin c : coins){
        c.printNumber();
    }
    cout << "The total value of your coins is $" << totalValue;
    return 0;
}