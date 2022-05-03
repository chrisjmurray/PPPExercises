// 13. Design and implement a rational number class, Rational. A rational 
// number has two parts: a numerator and a denominator, for example, 5/6 
// (five-sixths, also known as approximately .83333). Look up the definition 
// if you need to. Provide assignment, addition, subtraction, multiplication, 
// division, and equality operators. Also, provide a conversion to double. 
// Why would people want to use a Rational class?

#include "../std_lib_facilities.h"

class Rational {
    public:
        Rational(int nn, int dd); // n for numerator, d for denominator
        double todouble();
        int numerator() const {return n;}
        int denominator() const {return d;}
        void reduce();
    private:
        int n;
        int d;
};

//function for gcd taken from https://www.tutorialspoint.com/cplusplus-program-to-find-gcd
int gcd(int a, int b) {
   if (b == 0)
   return a;
   return gcd(b, a % b);
}

Rational::Rational(int nn, int dd) {
    if (dd == 0) error("Rational(): cannot have a zero denominator");
    n = nn;
    d = dd;
}

void Rational::reduce() {
    int g = gcd(n, d);
    n = n/g;
    d = d/g;
}
Rational operator*(const Rational& a, const Rational& b) {
    Rational c {a.numerator()*b.numerator(), a.denominator()*b.denominator()};
    return c;
}

Rational operator/(const Rational& a, const Rational& b) {
    Rational c = Rational(b.denominator(), b.numerator());
    return a*c;
}

Rational operator+(const Rational& a, const Rational& b) {
    Rational aa = a*Rational(b.denominator(), b.denominator());
    Rational bb = b*Rational(a.denominator(), a.denominator());
    int cnumer = aa.numerator()+bb.numerator();
    int cdenom = aa.denominator();
    return Rational(cnumer, cdenom);
}

Rational operator-(const Rational& a, const Rational& b) {
    Rational minusb = Rational(-b.numerator(), b.denominator());
    return a+minusb;
}

bool operator==(const Rational& a, const Rational& b) {
    Rational c = a;
    c.reduce();
    Rational d = b;
    d.reduce();

    return (c.numerator() == d.numerator() && c.denominator() == d.denominator());
}

bool operator!=(const Rational& a, const Rational& b) {
    return !(a==b);
}

ostream& operator<<(ostream& os, const Rational& r){
    return os << r.numerator() << "/" << r.denominator();
}

int main() {
    Rational a = Rational(-4, 3);
    Rational b = Rational(48,36);
    Rational mult = a*b;
    mult.reduce();
    Rational divi = a/b;
    divi.reduce();
    Rational add = a+b;
    add.reduce();
    Rational minu = a-b;
    minu.reduce();
    cout << "*: " << mult;
    cout << "\n/: " << divi;
    cout << "\n+: " << add;
    cout << "\n-: " << minu;
    cout << "\n==: " << int(a==b);
    cout << "\n!=: " << int(a != b);
    return 0;
}
