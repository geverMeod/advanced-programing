// C++ program to find groups of unknown
// Points using K nearest neighbour algorithm.
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

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

string classifyAPoint(vector<Flower> arr, int k, Flower f)
{
	//hamon gus
	for (int i = 0; i < arr.size(); i++) {
		arr[i].calcDistance(f);
	}
		
	mysort(arr.begin(), arr.end(), comparison);
	vector<string> flowerTypes;
	for (Flower f : arr) {
		if (flowerTypes.empty()||!f.type._Equal(flowerTypes.())) {
			flowerTypes.push_back(f.type);
		}
	}
	vector<int> numOfFlowerType(flowerTypes.size());
	for (int i : numOfFlowerType) i = 0;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < flowerTypes.size(); j++) {
			if (flowerTypes[j]._Equal(arr[i].type)) {
				numOfFlowerType[j]++;
			}
		}
	}
	int maxElementIdx = 0;
	for (int i = 0; i < numOfFlowerType.size(); i++)
	{
		if (numOfFlowerType[maxElementIdx] < numOfFlowerType[i]) maxElementIdx = i;
	}
	return flowerTypes[maxElementIdx];
}

int main()
{
	ifstream classified;
	classified.open("classified.csv");
	vector<Flower> classifiedVec;
	while (classified.good()) {
		string cell;
		string line;
		Flower thisFlower;
		stringstream lineStream;
		getline(classified, line);
		if (!line.empty()) {
			lineStream.str(line);
			for (int i = 0; i < 4; i++) {
				getline(lineStream, cell, ',');
				thisFlower.attributes[i] = stod(cell);
			}
			getline(lineStream, cell, ',');
			thisFlower.type = cell;
			classifiedVec.push_back(thisFlower);
			
		}
	}
	ifstream unclassified;
	unclassified.open("Unclassified.csv");
	while (unclassified.good()) {
		string cell;
		string line;
		Flower thisFlower;
		stringstream lineStream;
		getline(unclassified, line);
		if (!line.empty()) {
			lineStream.str(line);
			for (int i = 0; i < 4; i++) {
				getline(lineStream, cell, ',');
				thisFlower.attributes[i] = stod(cell);
			}
			cout << classifyAPoint(classifiedVec, 3, thisFlower) << endl;
		}
	}
	return 0;
}

