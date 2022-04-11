/*
Read a sequence of double values into a vector. Think of each value as
the distance between two cities along a given route. Compute and print
the total distance (the sum of all distances). Find and print the smallest
and greatest distance between two neighboring cities. Find and print the
mean distance between two neighboring cities
*/

#include "../std_lib_facilities.h"

int main() {
	vector<double> distances;

	for (double distance; cin >> distance;) {
		distances.push_back(distance);
	}

	//find total distance
	double totalDistance = 0;
	for (double x : distances) {
		totalDistance += x;
	}
	//find smallest and greatest distance
	sort(distances);
	double smallestDistance = distances.front();
	double greatestDistance = distances.back();

	//find the mean of the distances
	double meanDistance = totalDistance / distances.size();

	//print info
	cout << "Total distance: " << totalDistance;
	cout << "\nShortest distance: " << smallestDistance;
	cout << "\nGreatest distance: " << greatestDistance;
	cout << "\nMean distance: " << meanDistance;
}