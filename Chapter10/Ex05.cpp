// Write the function print_year() mentioned in §10.11.2.


#include "../std_lib_facilities.h"

const int not_a_reading = -7777;
const int not_a_month = -1;
constexpr int implausible_min = -200;
constexpr int implausible_max = 200;

vector<string> month_input_tbl = {
    "jan", "feb", "mar", "apr", "may", "jun", "jul",
    "aug", "sep", "oct", "nov", "dec"
};

struct Day {
    vector<double> hour {vector<double>(24, not_a_reading)};
};

struct Month {
    int month {not_a_month};
    vector<Day> day {32};
};

struct Year {
    int year;
    vector<Month> month {12};
};

struct Reading {
    int day;
    int hour;
    double temperature;
};



int month_to_int(string s) {
    for (int i = 0; i < 12; ++i) if (month_input_tbl[i]==s) return i;
    return -1;
}

bool is_valid(const Reading& r){
    if (r.day < 1 || 31 < r.day) return false;
    if (r.hour < 0 || 23 < r.hour) return false;
    if (r.temperature < implausible_min || implausible_max < r.temperature)
        return false;
    return true;
}

void end_of_loop(istream& ist, char term, const string& message) {
    if (ist.fail()) {
        ist.clear();
        char ch;
        if (ist >> ch && ch == term) return;
        error(message);
    }
}

void print_day(ostream& ofs, Day d, int j){
    for (int k = 0; k < d.hour.size(); ++k){
        if (d.hour[k] != not_a_reading){
            ofs << "(" << j << " " << k << " " << d.hour[k] << ") ";
        }
    }
}

void print_month(ostream& ofs, Month m, int i){
    ofs << "{ month " << month_input_tbl[i] << " ";
    for (int j = 0; j < m.day.size(); ++j){
            print_day(ofs, m.day[j], j);
    }
    
    ofs << "} ";
}

void print_year(ostream& ofs, Year y){
    ofs << "{ year " << y.year << " ";
    for (int i = 0; i < y.month.size(); ++i){
        if (y.month[i].month != not_a_month){
            print_month(ofs, y.month[i], i);
        }
    }
    ofs << "}\n";
}

istream& operator>>(istream& is, Reading& r){
    char ch1;
    if (is>>ch1 && ch1 != '(') {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    char ch2;
    int d;
    int h;
    double t;
    is >> d >> h >> t >> ch2;
    if (!is || ch2 != ')') error("bad reading");
    r.day = d;
    r.hour = h;
    r.temperature = t;
    return is;
}

istream& operator>>(istream& is, Month& m){
    char ch = 0;
    if (is >> ch && ch != '{') {
        is.unget();
        is.clear(ios_base::failbit);
        return is;
    }

    string month_marker;
    string mm;
    is >> month_marker >> mm;
    if (!is || month_marker != "month") error("bad start of the month");
    m.month = month_to_int(mm);
    int duplicates = 0;
    int invalids = 0;
    for (Reading r; is >> r;) {
        if (is_valid(r)) {
            if (m.day[r.day].hour[r.hour] != not_a_reading)
                ++duplicates;
            m.day[r.day].hour[r.hour] = r.temperature;
        }
        else ++invalids;
    }
    if (invalids) error("invalid readings in month", invalids);
    if (duplicates) error("duplicate readings in month", duplicates);
    end_of_loop(is,'}',"bad end of month");
    return is;
}

istream& operator>>(istream& is, Year& y) {
    char ch;
    is >> ch;
    if (ch!='{') {
        is.unget();
        is.clear(ios::failbit);
        return is;
    }

    string year_marker;
    int yy;
    is >> year_marker >> yy;
    if (!is || year_marker != "year") error("bad start of year");
    y.year = yy;

    while(true) {
        Month m;
        if(!(is>>m)) break;
        y.month[m.month] = m;
    }

    end_of_loop(is,'}',"bad end of year");
    return is;
}

int main () {
    string iname = "Ex05in.txt";
    ifstream ifs {iname};
    if (!ifs) error("can't open input file", iname);

    ifs.exceptions(ifs.exceptions()|ios_base::badbit); //through for bad()

    // open an output file:
    string oname = "Ex05out.txt";
    ofstream ofs {oname};
    if (!ofs) error("can't open output file", oname);

    //read an arbitrary number of years
    vector<Year> ys;
    while(true) {
        Year y;
        if (!(ifs>>y)) break;
        ys.push_back(y);
    }
    cout << "read " << ys.size() << " years of readings\n";

    for (Year& y : ys) print_year(ofs,y);
    return 0;
}