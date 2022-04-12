// In the drill, you wrote a program that, given a series of numbers, found 
// the max and min of that series. The number that appears the most times 
// in a sequence is called the mode. Create a program that finds the mode of 
// a set of positive integers.

#include "../std_lib_facilities.h"


struct valcount {
    int val;
    int count;
};

bool sortbycount(const valcount &a, const valcount &b) {
    return (a.count > b.count);
}

int main() {
    vector<int> nums;
    int numssize;
    int randmax;
    int randmin;

    //query user for multiset parameters
    cout << "I will generate the multiset for you. How many entries? ";
    cin >> numssize;
    cout << "Minimum value? ";
    cin >> randmin;
    cout << "Maximum value? ";
    cin >> randmax;
    
    for (int i = 0; i < numssize; ++i) {
        nums.push_back(randint(randmin, randmax));
    }

    sort(nums);

    cout << "Multiset values: ";
    for (int n : nums) {
        cout << n << " ";
    }
    //find the multiplicity of each value in the multiset
    vector<valcount> vc;
    int val = nums[0];
    vc.push_back(valcount {val, 1});
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] == vc.back().val){
            vc.back().count++;
        }
        else {
            vc.push_back(valcount {nums[i], 1});
        }
    }

    sort(vc.begin(), vc.end(), sortbycount);
    //find the values with the highest multiplicity
    vector<int> modes {vc[0].val};
    int modecount = vc[0].count;
    for (int i = 1; i < vc.size(); ++i) {
        if (vc[i].count == vc[0].count){
            modes.push_back(vc[i].val);
        }
        else {
            break;
        }
    }

    cout << "\n\nMin: " << nums[0];
    cout << "\nMax: " << nums.back();
    cout << "\nModes: ";

    if (modecount == 1){
        cout << "no modes";
    }
    else {
        for (int n : modes) {
            cout << n << " ";
        }
    }
    return 0;

}