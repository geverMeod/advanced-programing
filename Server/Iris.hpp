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
	
	static bool contains(vector<string> vec, string s);

	int getMaxElementIndex(vector<int> vector);

public:

	static vector<string> getFlowerTypes(vector<Iris> flowerVec);

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

	string const toString() const{
		string retVal("");
		for(double d:attributes){
			retVal.append(to_string(d) + ",");
		}
		retVal.append(type);
		return retVal;
	}

	void setDistance(double distance);

	string classify(vector<Iris> classifiedVec, int k, double (Iris::*distanceFunction)(Iris));
};
