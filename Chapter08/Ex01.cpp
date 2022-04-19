// Modify the calculator program from Chapter 7 to make the input stream 
// an explicit parameter (as shown in §8.5.8), rather than simply using cin. 
// Also give the Token_stream constructor (§7.8.2) an istream& parameter 
// so that when we figure out how to make our own istreams (e.g., attached 
// to files), we can use the calculator for those. Hint: Don’t try to copy an 
// istream.

#include "../std_lib_facilities.h"

//Constants---------------------------------------------------------------------
const char number = '8';
const char quit = 'q';
const char print = ';';
const char name = 'a';
const char let = 'L';
const char sqroot = 's';
const char assign = '=';
const char help1 = 'h';
const char help2 = 'H';
const string declkey = "#";
const string sqrtkey = "sqrt";
const string quitkey = "quit";
const string helpkey = "help";
const string prompt = "> ";
const string result = "";
const string constant = "const";

//------------------------------------------------------------------------------


class Variable {
    public:
        string name;
        double value;
        bool constant;
};

class Symbol_table {
    public:
        vector<Variable> var_table;
        double get_value(string s);
        void set_value(string s, double d);
        bool is_declared(string var);
        void define_name(string var, double val, bool isConstant);
};

Symbol_table st;

double Symbol_table::get_value(string s) //return value of the Variable named s
{
    for (const Variable& v : var_table)
        if (v.name == s) return v.value;
    error("get: undefined variable ", s);
}

void Symbol_table::set_value(string s, double d) //set the Variable named s to d
{
    for (Variable& v : var_table)
        if (v.name == s) {
            if (v.constant == true) error(v.name, " is a constant, cannot be reassigned");
            v.value = d;
            return;
        }
    error("set: undefined variable ", s);
}

bool Symbol_table::is_declared(string var) // is var alrady in var_table?
{
    for (const Variable& v : var_table)
        if (v.name == var) return true;
    return false;
}

void Symbol_table::define_name(string var, double val, bool isConstant) // add {var, val} to var_table
{
    if (is_declared(var)) error(var, " declared twice");
    var_table.push_back(Variable{var, val, isConstant});
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
    void clear_buffer();
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------
void Token_stream::clear_buffer(){
    full = false;
    buffer = '0';
}
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
    cin >> noskipws >> ch;
    while (isspace(ch)){
        if (ch == '\n') 
         {
             return Token(print);
         }
         cin >> noskipws >> ch;
    }

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
    case ',':
        return Token(ch);        // let each character represent itself
    case '\n':
        return Token(print);
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
            if (s == declkey) return Token{let};
            while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
            cin.putback(ch);
            if (s == sqrtkey) return Token{sqroot};
            if (s == quitkey) return Token{quit};
            if (s == helpkey) return Token{help1};
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
    while(cin >> noskipws >> ch){
        if (ch == c) return;
    }
}
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------

double expression(Token_stream& ts);    // declaration so that primary() can call expression()

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
double primary(Token_stream& ts)
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
    {
        double d = expression(ts);
        t = ts.get();
        if (t.kind != ')') error("')' expected");
        return d;
    }
    case '{':    // handle '(' expression ')'
    {
        double d = expression(ts);
        t = ts.get();
        if (t.kind != '}') error("'}' expected");
        return d;
    }
    case number: 
        return t.value;   // return the number's value
    case name:
    {
        return st.get_value(t.name);
    }
    case sqroot: 
    {
        double d = primary(ts);
        if (d<0) error("sqrt argument less than 0");
        return sqrt(d);
    }
    case '-':
        return -primary(ts);
    case '+':
        return primary(ts);
    default:
        error("primary expected");
    }
}

//deals with things that bind tighter than term(), such as !
double op(Token_stream& ts) 
{
    double left = primary(ts);
    Token t = ts.get();
    while (true) {
        switch (t.kind) {
        case '!':
            left = factorial(left);
            t = ts.get();
            break;
        case '^':
        {
            double exponent = primary(ts);
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
double term(Token_stream& ts)
{
    double left = op(ts);
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '*':
            left *= op(ts);
            t = ts.get();
            break;
        case '/':
        {
            double d = op(ts);
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = op(ts);
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
double expression(Token_stream& ts)
{
    double left = term(ts);      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream
    
    while (true) {
        switch (t.kind) {
        case '+':
            left += term(ts);    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left += term(ts);    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

double declaration(Token_stream& ts)
{
    Token t = ts.get();
    bool isConstant = false;
    if (t.name == constant) {
        isConstant = true;
    }
    else {
        ts.putback(t);
    }
    t = ts.get();
    if (t.kind != name) error("name expected in declaration");
    string var_name = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=') error("= missing in declaration of ", var_name);

    double d = expression(ts);
    st.define_name(var_name, d, isConstant);
    return d;
}

double assignment(Token_stream& ts)
{
    Token t = ts.get();
    if (t.kind != name) error("name expected in declaration");
    string var_name = t.name;

    Token t2 = ts.get();
    if (t2.kind != ',') error(", missing in assignment of ", var_name);

    double d = expression(ts);
    st.set_value(var_name, d);
    return d;
}

double statement(Token_stream& ts)
{
    Token t = ts.get();
    switch (t.kind) {
        case let:
            return declaration(ts);
        case assign:
            return assignment(ts);
        default:
            ts.putback(t);
            return expression(ts);
    }
}
void help() {
    cout << "Statements follow standard mathematical syntax. Available operations are \n";
    cout << "*,/,+,-,^,!, (),sqrt(). Declare a variable with with keyword let or #, e.g. #x = 3.\n";
    cout << "Precede a declaration with keyword const to make it a constant. \n";
    cout << "statements are terminated with newline or ;. So to put multiple statements \n";
    cout << "on one line, use the semicolon, e.g. 1+2; 3+4;\n";
}
//------------------------------------------------------------------------------
void clean_up_mess(Token_stream& ts) {
    cin.clear();
    ts.clear_buffer();
}

void calculate() {
    Token_stream ts = Token_stream();
    while (cin) {
        try {
            cout << prompt;
            Token t = ts.get();
            while (t.kind == print) t = ts.get();
            if (t.kind == quit) return;
            if (t.kind == help1) {
                help();
                clean_up_mess(ts);
                continue;
            }
            ts.putback(t);
            cout << result << statement(ts) << '\n';
        }
        catch (exception& e) {
            cerr << e.what() << '\n';
            clean_up_mess(ts);
        }
    }
}
int main()
{
    try {
        st.define_name("pi", 3.1415926535, true);
        st.define_name("e", 2.7182818284, true);
        st.define_name("k", 1000, true);

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