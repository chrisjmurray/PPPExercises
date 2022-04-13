/*
Write a grammar for bitwise logical expressions. A bitwise logical 
expression is much like an arithmetic expression except that the operators
are ! (not), ~ (complement), & (and), | (or), and ^ (exclusive or). Each
operator does its operation to each bit of its integer operands (see 25.5).
! and ~ are prefix unary operators. A ^ binds tighter than a | (just as *
binds tighter than +) so that x|y^z means x|(y^z) rather than (x|y)^z. The
& operator binds tighter than ^ so that x^y&z means x^(y&z).
*/

#include "../std_lib_facilities.h"

class Token {
public:
	char kind;
	int value;
	Token(char ch)    // make a Token from a char
		:kind(ch), value(0) { }
	Token(char ch, int val)     // make a Token from a char and a double
		:kind(ch), value(val) { }
};

class Token_stream {
public:
	Token_stream();   // make a Token_stream that reads from cin
	Token get();      // get a Token (get() is defined elsewhere)
	void putback(Token t);    // put a Token back
private:
	bool full;        // is there a Token in the buffer?
	Token buffer;     // here is where we keep a Token put back using putback()
};

Token_stream::Token_stream()
	:full(false), buffer(0) {}

void Token_stream::putback(Token t) {
	if (full) error("Buffer is full");
	buffer = t;
	full = true;
}

Token Token_stream::get() {
	if (full) {
		full = false;
		return buffer;
	}
	char ch;
	cin >> ch;

	switch (ch) {
	case ';':
	case 'q':
	case '!': case '~': case '|': case '^': case '&': case '(': case ')':
		return Token(ch);
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);         // put digit back into the input stream
		int val;
		cin >> val;            
		return Token('#', val);   // let '#' represent "a number"
	}
	default:
		error("Bad Token");
	}
}

Token_stream ts;

int expression();

int primary() {
	Token t = ts.get();

	switch (t.kind) {
	case '!': case '~':
	{
		int i = primary();
		return ~i;
	}
	case '(':
	{
		int i = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected)");
		return i;
	}
	case '#':
		return t.value;
	default:
		error("primary expected");
	}
}

int secondary() {
	int left = primary();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '&':
			left &= primary();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

int tertiary() {
	int left = secondary();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '^':
			left ^= secondary();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

int expression() {
	int left = tertiary();
	Token t = ts.get();

	while (true) {
		switch (t.kind) {
		case '|':
			left |= tertiary();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

int main() {
	try
	{
		int val = 0;
		while (cin) {
			Token t = ts.get();
			if (t.kind == 'q') break; // 'q' for quit
			if (t.kind == ';') {       // ';' for "print now"
				cout << "=" << val << '\n';
				val = 0;
			}
			else {
				ts.putback(t);
				val = expression();
			}

		}
		keep_window_open();
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch (...) {
		cerr << "Oops: unknown exception!\n";
		keep_window_open();
		return 2;
	}
}