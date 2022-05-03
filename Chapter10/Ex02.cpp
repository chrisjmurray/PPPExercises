// Write a program that creates a file of data in the form of the temperature 
// Reading type defined in §10.5. For testing, fill the file with at least 50 
// “temperature readings.” Call this program store_temps.cpp and the file it 
// creates raw_temps.txt.

#include "../std_lib_facilities.h"

string filename = "raw_temps.txt";
float fahrabszero = -459.67;

void writerandreadings(int numreadings){
    ofstream ost{filename};
    if (!ost) error("can't open output file ", filename);
    for (int i = 0; i < numreadings; ++i){
        int randhour = randint(1,24);
        float randfloat = rand()/static_cast<float>(RAND_MAX);
        float randtemp = randfloat*1000 + fahrabszero;
        randtemp = round(randtemp*100) / 100;
        ost << randhour << " " << randtemp << "\n";
    }
}

int main() {
    writerandreadings(50);
}