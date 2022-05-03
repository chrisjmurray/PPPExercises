//x 5. This exercise and the next few require you to design and implement a
//         Book class, such as you can imagine as part of software for a library. Class
//         Book should have members for the ISBN, title, author, and copyright 
//         date. Also store data on whether or not the book is checked out. Create 
//         functions for returning those data values. Create functions for checking 
//         a book in and out. Do simple validation of data entered into a Book; for 
//         example, accept ISBNs only of the form n-n-n-x where n is an integer and 
//         x is a digit or a letter. Store an ISBN as a string.
//x 6. Add operators for the Book class. Have the == operator check whether 
//         the ISBN numbers are the same for two books. Have != also compare 
//         the ISBN numbers. Have a << print out the title, author, and ISBN on 
//         separate lines.
//x 7. Create an enumerated type for the Book class called Genre. Have the 
//         types be fiction, nonfiction, periodical, biography, and children. Give 
//         each book a Genre and make appropriate changes to the Book constructor and member functions.
//x 8. Create a Patron class for the library. The class will have a user's name, 
//         library card number, and library fees (if owed). Have functions that access 
//         this data, as well as a function to set the fee of the user. Have a helper 
//         function that returns a Boolean (bool) depending on whether or not the 
//         user owes a fee.
//x 9. Create a Library class. Include vectors of Books and Patrons. Include a 
//         struct called Transaction. Have it include a Book, a Patron, and a Date
//         from the chapter. Make a vector of Transactions. Create functions to add 
//         books to the library, add patrons to the library, and check out books. 
//         Whenever a user checks out a book, have the library make sure that both 
//         the user and the book are in the library. If they aren't, report an error. 
//         Then check to make sure that the user owes no fees. If the user does, 
//         report an error. If not, create a Transaction, and place it in the vector of 
//         Transactions. Also write a function that will return a vector that contains 
//         the names of all Patrons who owe fees.

#include "Ex05-09.h"

//constructors for Book
Book::Book(string title, string author, string isbn, Genre genre, Chrono::Date copyright_date) 
{
    if (!is_book(title, author, isbn, copyright_date)) error("invalid parameters for Book");
    _title = title;
    _author = author;
    _isbn = isbn;
    _genre = genre;
    _copyright_date = copyright_date;
}

Book::Book()
{
    _title = "None";
    _author = "None";
    _isbn = "0-0-0-0";
    _genre = Genre::nogenre;
    _copyright_date = Chrono::Date(); //default is (y/m/d) 2001, 01, 01
}

void Book::checkout() {
    if (!_available) error("checkout(): book alaready checked out");
    _available = false;
}

void Book::checkin() {
    if (_available) error("checkin(): book already checked in");;
    _available = true;
}

//helper functions
bool is_book(string title, string author, string isbn, Chrono::Date copyright_date) 
{
    //Extra parameters exist because in a program meant for release to the public, I would
    //want to validate all book info
    if  (!regex_match(isbn, regex(RE_ISBN_VALID))) return false;
    return true;
}

bool operator==(const Book& a, const Book& b) 
{
    return (a.isbn() == b.isbn());
}

bool operator!=(const Book& a, const Book& b)
{
    return (!(a.isbn() == b.isbn()));
}

ostream& operator<<(ostream& os, const Book& b)
{
    return os << "\nTitle: " << b.title()
                << "\nAuthor: " << b.author()
                << "\nGenre: " << genrelabels[int(b.genre())]
                << "\nISBN: " << b.isbn();
}

//Patron definitions

//Patron constructor
Patron::Patron(string name, string cardnumber)
{
    _name = name;
    _cardnumber = cardnumber;
}

void Patron::addfee(float fee)
{
    if (fee<0) error("addfee(): cannot add negative fee");
    _feesdue += fee;
}

void Patron::subtractfee(float paid)
{
    if (paid<0) error("subtractfee(): cannot subtract negative fee");
    _feesdue -= paid;
}

bool operator==(const Patron& a, const Patron& b)
{
    return (a.cardnumber() == b.cardnumber());
}

bool operator!=(const Patron& a, const Patron& b)
{
    return (!(a == b));
}

ostream& operator<<(ostream& os, const Patron& p)
{
    return os << "\nName: " << p.name()
                << "\nCardnumber: " << p.cardnumber()
                << "\nFees Due: " << p.feesdue();
}

//Library definitions
Library::Library(){}

bool Library::bookexists(Book book)
{
    for(Book b : _books){
        if (b == book) return true;
    }
    return false;
}

bool Library::patronexists(Patron patron)
{
    for (Patron p : _patrons) {
        if (patron == p) return true;
    }
    return false;
}
void Library::addbook(Book book)
{
    if (bookexists(book)) error("addbook(): book already exists");
    _books.push_back(book);
}

void Library::addpatron(Patron patron)
{
    if (patronexists(patron)) error("addpatron(): patron already exists");
    _patrons.push_back(patron);
}

void Library::checkout(Book book, Patron patron, Chrono::Date date)
{
    if (!bookexists(book)) error("checkout(): book does not exist");
    if (!book.available()) error("checkout(): book already checkedout");
    if (!patronexists(patron)) error("checkout(): patron does not exist");
    if (patron.isfees()) error("checkout(): patron owes fees");
    Transaction t {book, patron, date};
    _transactions.push_back(t);
}

vector<Patron> Library::owesfees()
{
    vector<Patron> owingpatrons {};
    for (Patron p : _patrons) {
        if (p.isfees()) owingpatrons.push_back(p);
    }
    return owingpatrons;
}
