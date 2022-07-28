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
	public:
		double distance;
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

int classifyAPoint(vector<Flower> arr, int k, Flower f)
{
	//hamon gus
	for (int i = 0; i < arr.size(); i++)
		arr[i].calcDistance(f);
	sort(arr.begin(), arr.end(), comparison);
	int numOf = 0;
	int freq2 = 0;
}

int main()
{
	const int n = 17; 
	vector<Flower> arr;
	int k = 3;
	return 0;
}
