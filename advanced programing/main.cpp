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
				sqrDistance += (attributes[i]-other.attributes[i]) * (attributes[i] - other.attributes[i]);
			}
			distance = sqrt(sqrDistance);
			return distance;
		}
		double manhettenDistance(Flower other) {
			distance = 0;
			for (int i = 0; i < 4; i++) {
				distance += abs(attributes[i] - other.attributes[i]);
			}
			return distance;
		}
		double chebyshevDistance(Flower other) {
			double maxDistance = 0;
			for (int i = 0; i < 4; i++) {
				maxDistance = max(attributes[i] - other.attributes[i], maxDistance);
			}
			distance = maxDistance;
			return distance;
		}

};

bool comparison(Flower a, Flower b)
{
	return (a.distance < b.distance);
}

bool contains(vector<string> vec, string s) {
	for (string x : vec) {
		if (x._Equal(s)) return true;
	}
	return false;
}
vector<string> getFlowerTypes(vector<Flower> flowerVec)
{
	vector<string> flowerTypes;
	for (Flower f : flowerVec) {
		if (flowerTypes.empty() || !contains(flowerTypes, f.type)) {
			flowerTypes.push_back(f.type);
		}
	}
	return flowerTypes;
}
int getMaxElementIndex(vector<int> vector)
{
	int maxElementIdx = 0;
	for (int i = 0; i < vector.size(); i++)
	{
		if (vector[maxElementIdx] < vector[i]) maxElementIdx = i;
	}
	return maxElementIdx;
}

string classifyAPoint(vector<Flower> classifiedVec, int k, Flower f)
{
	//hamon gus
	for (int i = 0; i < classifiedVec.size(); i++) {
		classifiedVec[i].calcDistance(f);
	}
	vector<string> flowerTypes = getFlowerTypes(classifiedVec);
	sort(classifiedVec.begin(), classifiedVec.end(), comparison);
	vector<int> numOfFlowerType(flowerTypes.size());
	for (int i : numOfFlowerType) i = 0;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < flowerTypes.size(); j++) {
			if (flowerTypes[j]._Equal(classifiedVec[i].type)) {
				numOfFlowerType[j]++;
			}
		}
	}
	return flowerTypes[getMaxElementIndex(numOfFlowerType)];
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

