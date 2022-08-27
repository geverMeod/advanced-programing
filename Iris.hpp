#pragma once
#include <string>
#include <vector>

using namespace std;
class Iris
{
private:
	string type;
	double attributes[4];
	double distance;

	static bool comparison(Iris a, Iris b);
	
	bool contains(vector<string> vec, string s);

	vector<string> getFlowerTypes(vector<Iris> flowerVec);

	int getMaxElementIndex(vector<int> vector);

public:

	double euclideanDistance(Iris other);

	double manhattanDistance(Iris other);

	double chebyshevDistance(Iris other);

	string getType() {
		return this->type;
	}

	void setType(string type);

	double* getAttributes() {
		return this->attributes;
	}

	void setAttribute(double value, int index);

	double getDistance() {
		return this->distance;
	}

	void setDistance(double distance);

	void classify(vector<Iris> classifiedVec, int k, double (Iris::*distanceFunction)(Iris));
};
