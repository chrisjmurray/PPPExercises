#include "Chrono.h"
#include <regex>

const string RE_ISBN_VALID = "^\\d-\\d-\\d-[\\dA-Za-z]$"; // this validates ISBNs of the format specified in the 
                                 // problem statement, not ISBNs of the real-world 
                                 // format
enum class Genre {
    nogenre, fiction, nonfiction, periodical, biography, children
};
vector<string> genrelabels {"none", "fiction", "nonfiction", "periodical", "biography", "children"};

class Book {
    public:
        class Invalid {}; // to throw as an exception if initializing values are invalid
        Book(string title, string author, string isbn, Genre genre, Chrono::Date copyright_date);
        Book();
        //getters
        string title() const { return _title; }
        string author() const { return _author; }
        string isbn() const { return _isbn; }
        Genre genre() const {return _genre; }
        Chrono::Date copyright_date() const { return _copyright_date; }
        bool available() const { return _available; }
        //modifiers
        void checkout(); // check the book out of the library
        void checkin(); // check the book back into the library


    private:
        string _isbn;
        string _title;
        string _author;
        Chrono::Date _copyright_date;
        Genre _genre;
        bool _available = true; //false if book is checked out
};
//helper functions for class Book
bool is_book(string title, string author, string isbn, Chrono::Date copyright_date);
bool operator==(const Book& a, const Book& b);
bool operator!=(const Book& a, const Book& b);
ostream& operator<<(ostream& os, const Book& b);

class Patron {
    public:
        Patron(string name, string cardnumber);
        string name() const {return _name;}
        string cardnumber() const {return _cardnumber;}
        float feesdue() const {return _feesdue;}
        void addfee(float fee);
        void subtractfee(float paid);
        bool isfees() const {return bool(_feesdue);}
    private:
        string _name;
        string _cardnumber;
        float _feesdue;
};

struct Transaction {
    Book book;
    Patron patron;
    Chrono::Date date;
};

class Library {
    public:
        Library();
        void addbook(Book book);
        void addpatron(Patron patron);
        bool bookexists(Book book);
        bool patronexists(Patron patron);
        void checkout(Book book, Patron patron, Chrono::Date date);
        vector<Patron> owesfees();
    private:
        vector<Book> _books{};
        vector<Patron> _patrons{};
        vector<Transaction> _transactions{};
};