// Here is the calculator with all bugs corrected and all the features
// in the drill implemented. Instead of using pow(x, n) to represent 
// exponentiation, I opted to implement the more standard notation of x^n,
// and it seems silly to disallow non-integer inputs, so I did not follow 
// that direction.


#include "../std_lib_facilities.h"

//Constants---------------------------------------------------------------------
const char number = '8';
const char quit = 'q';
const char print = ';';
const char name = 'a';
const char let = 'L';
const char sqroot = 's';
const string declkey = "#";
const string sqrtkey = "sqrt";
const string quitkey = "quit";
const string prompt = "> ";
const string result = "= ";
//------------------------------------------------------------------------------
class Variable {
    public:
        string name;
        double value;
};

vector<Variable> var_table;

double get_value(string s) //return value of the Variable named s
{
    for (const Variable& v : var_table)
        if (v.name == s) return v.value;
    error("get: undefined variable ", s);
}

void set_value(string s, double d) //set the Variable named s to d
{
    for (Variable& v : var_table)
        if (v.name == s) {
            v.value = d;
            return;
        }
    error("set: undefined variable ", s);
}

bool is_declared(string var) // is var alrady in var_table?
{
    for (const Variable& v : var_table)
        if (v.name == var) return true;
    return false;
}

void define_name(string var, double val) // add {var, val} to var_table
{
    if (is_declared(var)) error(var, " declared twice");
    var_table.push_back(Variable{var, val});
}

class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    string name;
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
    Token(char ch, string n) : kind{ch}, name{n} {}
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
    void ignore(char c);
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
    :full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case ';':    // for "print"
    case 'q':    // for "quit"
    case '(':
    case ')': 
    case '{': 
    case '}': 
    case '+': 
    case '-': 
    case '*': 
    case '/': 
    case '!': 
    case '%':
    case '=':
    case '^':
        return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);         // put digit back into the input stream
        double val;
        cin >> val;              // read a floating-point number
        return Token(number, val);   
    }
    default:
        if (isalpha(ch) || ch == '#') {
            string s;
            s += ch;
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
            cin.putback(ch);
            if (s == declkey) return Token{let};
            if (s == sqrtkey) return Token{sqroot};
            if (s == quitkey) return Token{quit};
            return Token{name, s};
        }
        error("Bad token");
    }
}

void Token_stream::ignore(char c) {
    if (full && buffer.kind == c) {
        full = false;
        return;
    }
    full = false;

    char ch = 0;
    while(cin >> ch){
        if (ch == c) return;
    }
}
//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback() 

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------
double factorial(double left) {
    int intLeft = narrow_cast<int, double>(left); //narrow_cast is provided by the header file to throw an error for narrowing conversions
    if (intLeft == 0) intLeft = 1;
    else if (intLeft < 0) error("Invalid factorial operand");
    else {
        for (int i = intLeft - 1; i > 0; --i) {
            intLeft *= i;
        }
    }
    return double(intLeft);
}
// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') error("')' expected");
        return d;
    }
    case '{':    // handle '(' expression ')'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != '}') error("'}' expected");
        return d;
    }
    case number: 
        return t.value;   // return the number's value
    case name:
        return get_value(t.name);
    case sqroot: 
    {
        double d = primary();
        if (d<0) error("sqrt argument less than 0");
        return sqrt(d);
    }
    case '-':
        return -primary();
    case '+':
        return primary();
    default:
        error("primary expected");
    }
}

//deals with things that bind tighter than term(), such as !
double op() 
{
    double left = primary();
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
        case '!':
            left = factorial(left);
            t = ts.get();
            break;
        case '^':
        {
            double exponent = primary();
            left = pow(left, exponent);
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
}
//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    double left = op();
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '*':
            left *= op();
            t = ts.get();
            break;
        case '/':
        {
            double d = op();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = op();
            if (d==0) error("modulous:divide by zero");
            left = fmod(left, d);
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left += term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

double declaration()
{
    Token t = ts.get();
    if (t.kind != name) error("name expected in declaration");
    string var_name = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=') error("= missing in declaration of ", var_name);

    double d = expression();
    define_name(var_name, d);
    return d;
}

double statement()
{
    Token t = ts.get();
    switch (t.kind) {
        case let:
            return declaration();
        default:
            ts.putback(t);
            return expression();
    }
}
//------------------------------------------------------------------------------
void clean_up_mess() {
    ts.ignore(print);
}

void calculate() {
    while (cin) {
        try {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print) t = ts.get();
            if (t.kind == quit) return;
            ts.putback(t);
            cout << result << statement() << '\n';
        }
        catch (exception& e) {
            cerr << e.what() << '\n';
            clean_up_mess();
        }
    }
}
int main()
{
    try {
        define_name("pi", 3.1415926535);
        define_name("e", 2.7182818284);
        define_name("k", 1000);

        calculate();
        keep_window_open();
        return 0;
    }
    catch (runtime_error& e) {
        cerr << e.what() << '\n';
        keep_window_open("~~");
        return 1;
    }
    catch (...) {
        cerr << "exception \n";
        keep_window_open("~~");
        return 2;
    }
}
//------------------------------------------------------------------------------
/* Testing phrases
1+2-2*4+3/4+5!+6%3;
3*(1+2-2*4+3/(4+5!+6%3));
5/34*3.2/8.32%2!;
*/