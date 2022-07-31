#pragma once
#include <string>

using namespace std;
class Flower
{
private:
	string type;
	double attributes[4];
	double distance;

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

};
