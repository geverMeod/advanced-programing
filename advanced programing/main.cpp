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
	private:
		string type;
		double attributes[4];
		double distance=0;
	public:
		double euclideanDistance(Flower other) {
			double sqrDistance = 0;
			for (int i = 0; i < 4; i++) {
				sqrDistance += (this->attributes[i]-other.attributes[i]) * (this->attributes[i] - other.attributes[i]);
			}
			this->distance = sqrt(sqrDistance);
			return this->distance;
		}
		double manhattanDistance(Flower other) {
			this->distance = 0;
			for (int i = 0; i < 4; i++) {
				this->distance += abs(this->attributes[i] - other.attributes[i]);
			}
			return this->distance;
		}
		double chebyshevDistance(Flower other) {
			double maxDistance = 0;
			for (int i = 0; i < 4; i++) {
				maxDistance = max(abs(this->attributes[i] - other.attributes[i]), maxDistance);
			}
			this->distance = maxDistance;
			return this->distance;
		}
		string getType()
		{
			return this->type;
		}
		void setType(string type)
		{
			this->type = type;
		}
		double* getAttributes()
		{
			return this->attributes;
		}
		void setAttribute(double value, int index)
		{
			if (index >= sizeof(this->attributes)/sizeof(this->attributes[0]))
			{
				return;
			}
			this->attributes[index] = value;
		}
		double getDistance()
		{
			return this->distance;
		}
		void setDistance(double distance)
		{
			this->distance = distance;
		}
};

bool comparison(Flower a, Flower b)
{
	return (a.getDistance() < b.getDistance());
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
		if (flowerTypes.empty() || !contains(flowerTypes, f.getType())) {
			flowerTypes.push_back(f.getType());
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

string classifyAPoint(vector<Flower> classifiedVec, int k, Flower f, double (Flower::*distanceFunction)(Flower))
{
	for (int i = 0; i < classifiedVec.size(); i++) {
		(classifiedVec[i].*distanceFunction)(f);
	}
	vector<string> flowerTypes = getFlowerTypes(classifiedVec);
	sort(classifiedVec.begin(), classifiedVec.end(), comparison);
	vector<int> numOfFlowerType(flowerTypes.size());
	for (int i : numOfFlowerType) i = 0;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < flowerTypes.size(); j++) {
			if (flowerTypes[j]._Equal(classifiedVec[i].getType())) {
				numOfFlowerType[j]++;
			}
		}
	}
	return flowerTypes[getMaxElementIndex(numOfFlowerType)];
}

vector<Flower> getFlowersFromFile(string name)
{
	ifstream classified;
	classified.open(name);
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
				thisFlower.setAttribute(stod(cell), i);
			}
			getline(lineStream, cell, ',');
			thisFlower.setType(cell);
			classifiedVec.push_back(thisFlower);

		}
	}
	return classifiedVec;
}

int main()
{
	int k;
	cout << "please enter the k you want for the KNN: ";
	cin >> k;
	ofstream euclideanFile, manhattenFile, chebyshevFile;
	euclideanFile.open("euclidean_output.csv");
	manhattenFile.open("manhattan_output.csv");
	chebyshevFile.open("chebyshev_output.csv");
	ifstream classified;
	vector<Flower> classifiedVec = getFlowersFromFile("classified.csv");
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
				thisFlower.setAttribute(stod(cell), i);
			}
			euclideanFile << classifyAPoint(classifiedVec, k, thisFlower, &Flower::euclideanDistance) << endl;
			manhattenFile << classifyAPoint(classifiedVec, k, thisFlower, &Flower::manhattanDistance) << endl;
			chebyshevFile << classifyAPoint(classifiedVec, k, thisFlower, &Flower::chebyshevDistance) << endl;
		}
	}
	euclideanFile.close();
	manhattenFile.close();
	chebyshevFile.close();
	return 0;
}

