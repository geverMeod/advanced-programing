#pragma once
#include <string>
#include <vector>

using namespace std;
class Flower
{
private:
	string type;
	double attributes[4];
	double distance;

	static bool comparison(Flower a, Flower b);
	
	bool contains(vector<string> vec, string s);

	vector<string> getFlowerTypes(vector<Flower> flowerVec);

	int getMaxElementIndex(vector<int> vector);

public:

	double euclideanDistance(Flower other);

	double manhattanDistance(Flower other);

	double chebyshevDistance(Flower other);

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

	void classify(vector<Flower> classifiedVec, int k, double (Flower::*distanceFunction)(Flower));
};
