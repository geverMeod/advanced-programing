// C++ program to find groups of unknown
// Points using K nearest neighbour algorithm.
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
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

template <class _RanIt, class _Pr>
_CONSTEXPR20 void mysort(const _RanIt _First, const _RanIt _Last, _Pr _Pred) { // order [_First, _Last)
	_Adl_verify_range(_First, _Last);
	const auto _UFirst = _Get_unwrapped(_First);
	const auto _ULast = _Get_unwrapped(_Last);
	_Sort_unchecked(_UFirst, _ULast, _ULast - _UFirst, _Pass_fn(_Pred));
}

bool comparison(Flower a, Flower b)
{
	return (a.distance < b.distance);
}

int classifyAPoint(vector<Flower> arr, int k, Flower f)
{
	//hamon gus
	for (int i = 0; i < arr.size(); i++) {
		arr[i].calcDistance(f);
	}
		
	mysort(arr.begin(), arr.end(), comparison);
	int numOf = 0;
	int freq2 = 0;
	return 0;
}

int main()
{
	ifstream classified;
	classified.open("classified.csv");
	vector<Flower> classifiedVec = new vector<Flower>();
	while (classified.good()) {
		string line;
		getline(classified,line, ',');
		cout << line << endl;
	}
	const int n = 17; 
	vector<Flower> arr;
	int k = 3;
	return 0;
}

