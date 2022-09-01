#pragma once
#include <string>
#include <vector>

using namespace std;
class Iris
{
private:
	//the type of the iris
	string type;
	//a vector of the iris attributes
	vector<double> attributes;
	//saves the return value of the last time the distance function was invoked
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

	vector<double> getAttributes() {
		return this->attributes;
	}
	void pushAttribute(double att){
		this->attributes.push_back(att);
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
