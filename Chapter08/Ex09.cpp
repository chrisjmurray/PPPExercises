// write a function that given two vector<double>s price and weight computes 
// a value (an “index”) that is the sum of all price[i]*weight[i]. Make 
// sure to have weight.size()==price.size()

#include "../std_lib_facilities.h"

double priceweightindex(const vector<double>& prices, const vector<double>& weights){
    if (weights.size() != prices.size()) error("priceweightindex(): vectors different sizes");

    double index{0.0};
    for (int i = 0; i < weights.size(); ++i) {
        index += weights[i]*prices[i];
    }
    return index;
}

int main() {
    vector<double> weights {3.4, 2.23, 433.1, 55.2, 64.8};
    vector<double> prices {5.4, 33.6, 8.7, 99.2, 1.2};
    cout << priceweightindex(prices, weights);
}