// Modify the store_temps.cpp program from exercise 2 to include a temperature
// suffix c for Celsius or f for Fahrenheit temperatures. Then modify the 
// temp_stats.cpp program to test each temperature, converting the 
// Celsius readings to Fahrenheit before putting them into the vector.

//  write a program that reads the data from raw_temps.txt created in exercise 
//  2 into a vector and then calculates the mean and median temperatures 
//  in your data set. Call this program temp_stats.cpp

#include "../std_lib_facilities.h"

float fahrabszero = -459.67;
float celsabszero = -273.15;

struct Reading {
    int hour;
    float temp;
};

bool randomBool() {
   return rand() > (RAND_MAX / 2);
}

void writerandreadings(int numreadings, string filename){
    ofstream ost{filename};
    if (!ost) error("can't open output file ", filename);
    for (int i = 0; i < numreadings; ++i){
        int randhour = randint(1,24);
        float randfloat = rand()/static_cast<float>(RAND_MAX);
        if (randomBool()) {
            float randtemp = randfloat*1000 + fahrabszero;
            randtemp = round(randtemp*100) / 100;
            ost << randhour << " " << randtemp << 'f' << "\n";
        }
        else {
            float randtemp = randfloat*800 + celsabszero;
            randtemp = round(randtemp*100) / 100;
            ost << randhour << " " << randtemp << 'c' << "\n";
        }

    }
}

void writereadings(vector<Reading> rs, string filename){
    ofstream ost{filename};
    if (!ost) error("can't open output file ", filename);
    for (Reading r : rs){
        ost << r.hour << " " << r.temp << 'f' <<"\n";
    }
}

istream& operator>>(istream& is, Reading& r){
    int hour;
    float temp;
    char corf;
    is >> hour >> temp >> corf;
    if (corf == 'c'){
        temp = temp*9/5+32;
    }
    r.hour = hour;
    r.temp = temp;
    return is;
}

vector<Reading> getreadings(string filename) {
    ifstream ist {filename};
    if (!ist) error("can't open input file ", filename);
    vector<Reading> rs {};
    for (Reading r; ist >> r;){
        rs.push_back(r);
    }

    return rs;
}

float readingmean(const vector<Reading>& v){
    float sum = 0;
    int size = v.size();
    if (size == 0) error("readingmean(): vector empty");
    for (Reading r : v) {
        sum += r.temp;
    }

    return sum/size;
}
void sortbytemp(vector<Reading>& v){
    if (v.size() == 0) error("sortbytemp(): vector empty");
    for(int i = 1; i < v.size(); ++i){
        for(int j = i; j >= 0; --j) {
            if(v[j].temp > v[j-1].temp) break;
            swap(v[j].temp, v[j-1].temp);
            swap(v[j].hour, v[j-1].hour);
        }
    }
}
float readingmedian(const vector<Reading>& v){
    int size = v.size();
    if (size == 0) error("sortbytemp(): vector empty");
    float median;
    vector<Reading> v2 = v;
    sortbytemp(v2);
    
    if (size%2 == 0) {
        median = v2[size/2].temp*.5 + v2[size/2-1].temp*.5;
    }
    else {
        median = v2[size/2].temp;
    }  
    return median; 
}

int main(){
    string filename = "raw_temps.txt";
    writerandreadings(10, filename);
    vector<Reading> v = getreadings(filename);
    vector<Reading> v2 = v;
    string sortedfilename = "sorted_raw_temps.txt";
    sortbytemp(v2);
    writereadings(v2, sortedfilename);
    cout << "Mean Temp: " << readingmean(v);
    cout << "\nMedian Temp: " << readingmedian(v);

    return 0;
}