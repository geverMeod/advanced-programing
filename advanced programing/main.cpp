// C++ program to find groups of unknown
// Points using K nearest neighbour algorithm.
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

class Flower
{
public:
	string type;
	double attributes[4];
	double distance;
public:
	double distance; // distance to wanted data-point
	double calcDistance(Flower other) {
		double sqrDistance = 0;
		for (int i = 0; i < 4; i++) {
			sqrDistance += attributes[i] * attributes[i];
		}
		distance = sqrt(sqrDistance);
		return distance;
	}

};

bool comparison(Flower a, Flower b)
{
	return (a.distance < b.distance);
}


int classifyAPoint(vector<Flower> arr, int n, int k, Flower f)
{
	// Fill distances of all points from p
	for (int i = 0; i < n; i++)
		arr[i].calcDistance(f);

	// Sort the Points by distance from p
	sort(arr.begin(), arr.end(), comparison);
	int numOf = 0;
	int freq2 = 0;
	for (int i = 0; i < k; i++)
	{
		if (arr[i].type.)
			freq1++;
		else if (arr[i].type == 1)
			freq2++;
	}

	return (freq1 > freq2 ? 0 : 1);
}


int main()
{
	const int n = 17; // Number of data points
	vector<Flower> arr;

	/*Testing Point*/
	Flower p;

	// Parameter to decide group of the testing point
	int k = 3;
	printf("The value classified to unknown point"
		" is %d.\n", classifyAPoint(arr, n, k, p));
	return 0;
}
