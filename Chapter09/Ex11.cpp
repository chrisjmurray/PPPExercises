// Design and implement a set of useful helper functions for the Date class 
// with functions such as next_workday() (assume that any day that is not 
// a Saturday or a Sunday is a workday) and week_of_year() (assume that 
// week 1 is the week with January 1 in it and that the first day of a week is 
// a Sunday).

#include "Chrono.h"

namespace Chrono {

    int daysinmonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    int daysinmonthleap[13] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
    string days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    
    // member function definitions 
    Date::Date(int yy, Month mm, int dd)
        : y{yy}, m{mm}, d{dd}
    {
        if (!is_date(yy,mm,dd)) throw Invalid{};
    }

    const Date& default_date()
    {
        static Date dd {2001, Month::jan, 1};
        return dd;
    }

    Date::Date()
        :y{default_date().year()},
        m{default_date().month()},
        d{default_date().day()}
        {
        }
    
    void Date::add_day(int n)
    {
        if (n < 0) error("add_day(): only positive integers allowed");
        int daysinfouryears = 1461;
        add_year(n/daysinfouryears*4);
        n = n % daysinfouryears;
        while (n > 0) {
            int dd = d + 1;
            int mm = int(m);
            if (d == 31 && m == Month::dec){
                d = 1;
                m = Month::jan;
                ++y;
            }
            else if (leapyear(y)){
                if (dd > daysinmonthleap[mm]){
                    d = 1;
                    m = static_cast<Month>(mm+1);
                }
                else {
                    ++d;
                }
            }
            else{
                if (dd > daysinmonth[mm]){
                    d = 1;
                    m = static_cast<Month>(mm+1);
                }
                else {
                    ++d;
                }
            }
            --n;
        }
    }

    void Date::add_month(int n)
    {
        if (n < 0) error("add_month(): only positive integers allowed");
        int mm = n+int(m);
        add_year(mm/12);
        mm = mm%12;
        if (mm == 0) mm = 12;
        m = static_cast<Chrono::Month>(mm);

        if (d > daysinmonth[mm]) {
            if (leapyear(y) && m == Month::feb) d = 29;
            else d = daysinmonth[mm];
        }
    }

    void Date::add_year(int n)
    {
        if (m==Month::feb && d==29 && !leapyear(y+n)) { // beware of leap years!
            m = Month::mar;
            d = 1;
        }
        y += n;
    }
    //helper functions:

    bool is_date(int y, Month m, int d)
    {
        //assume that y is valid

        if (d<=0) return false; // d must be positive
        if (m<Month::jan || Month::dec<m) return false;

        int days_in_month = 31;

        switch (m) {
            case Month::feb:
                days_in_month = (leapyear(y))?29:28;
                break;
            case Month::apr: case Month::jun: case Month::sep: case Month::nov:
                days_in_month = 30;
                break;
        }

        if (days_in_month<d) return false;

        return true;
    }
    //Exercise 10
    bool leapyear(int y)
    {
        if (y%4 != 0) return false;
        if (y%100 != 0) return true;
        if (y%400 == 0) return true;
        return false;
    }

    bool operator==(const Date& a, const Date& b)
    {
        return a.year() == b.year()
            && a.month() == b.month()
            && a.day() == b.day();
    }

    bool operator!=(const Date& a, const Date& b)
    {
        return !(a == b);
    }

    ostream& operator<<(ostream& os, const Date& d)
    {
        return os << '(' << d.year() << ',' << int(d.month()) << ',' << d.day() << ')';
    }

    istream& operator>>(istream& is, Date& dd)
    {
        int y, m, d;
        char ch1, ch2, ch3, ch4;
        is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
        if(!is) return is;
        if (ch1!='(' || ch2!=',' || ch3!=',' || ch4!=')') {
            is.clear(ios_base::failbit);
            return is;
        }

        dd = Date(y, Month(m), d);

        return is;
    }

    //next 3 functions are for exercise 11
    

    Day day_of_week(const Date& d)
    {
        //jan 1, 1970 was a thursday
        if (d.year() < 1970) {
            error("day_of_week: Invalid date");
        }
        int numdays = 0;
        Date dd = Date(1970, Month::jan, 1);
        while (dd != d) {
            ++numdays;
            dd.add_day(1);
        }
        numdays = (numdays+4)%7; //3 because our reference day is a thursday while Day enum starts on sunday
        return static_cast<Day>(numdays);
    }

    Date next_Sunday(const Date& d)
    {
        Chrono::Day currentday = day_of_week(d);
        int daynum = int(currentday);
        int diff = 7-daynum;
        Chrono::Date dd = d;
        dd.add_day(diff);
        return dd;
    }

    Date next_weekday(const Date& d)
    {
        Chrono::Day currentday = day_of_week(d);
        int daynum = int(currentday);
        int addday;
        if (daynum == 5) {
            addday = 3;
        }
        else if (daynum == 6) {
            addday = 2;
        }
        else {
            addday = 1;
        }
        Chrono::Date dd = d;
        dd.add_day(addday);
        return dd;
    }
    int week_of_year(const Date& d){
        int numdays {0};
        Chrono::Date dd {d.year(), Month::jan, 1};
        while(dd != d) {
            ++numdays;
            dd.add_day(1);
        }

        return numdays/7 + 1;
    }
}

int main()
{
    //Test addmonth()
    // cout << "Testing addmonth()\n";
    // Chrono::Date d = Chrono::Date(2022, Chrono::Month::apr, 30);
    // cout << "\nd: " << d;
    // for (int i = 0; i < 100; ++i){
    //     int x = randint(100);
    //     d.add_month(x);
    //     cout << "\n+" << x << ": " << d;
    // }

    // cout << "Testing add_day()\n";
    // Chrono::Date e = Chrono::Date();
    // vector<int> testints {10, 28423, 342, 3, 20, 1, 448};
    // for (int x : testints) {
    //     cout << "\nd: " << e;
    //     e.add_day(x);
    //     cout << "\n+" << x << ": " << e;
    // }

    //Test day_of_week()
    Chrono::Date today = Chrono::Date(2022, Chrono::Month::may, 2);
    
    Chrono::Day day = day_of_week(today);
    cout << Chrono::days[int(day)];   
    Chrono::Date nextsunday = Chrono::next_Sunday(today);
    cout << nextsunday;
}