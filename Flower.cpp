#include "Flower.hpp"
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

bool Flower::comparison(Flower a, Flower b)
{
	return (a.getDistance() < b.getDistance());
}
bool Flower::contains(vector<string> vec, string s) {
	for (string x : vec) {
		if (x.compare(s) == 0) return true;
	}
	return false;
}
int Flower::getMaxElementIndex(vector<int> vector){
	//returns the number of which the vector value is the biggest.
	int maxElementIdx = 0;
	for (int i = 0; i < vector.size(); i++)
	{
		if (vector[maxElementIdx] < vector[i]) maxElementIdx = i;
	}
	return maxElementIdx;
}
vector<string> Flower::getFlowerTypes(vector<Flower> flowerVec){
	//returns all the flower types in a vector of flowers.
	//in our database it returns all the iris types there are.
	vector<string> flowerTypes;
	for (Flower f : flowerVec) {
		if (flowerTypes.empty() || !contains(flowerTypes, f.getType())) {
			flowerTypes.push_back(f.getType());
		}
	}
	return flowerTypes;
}
void Flower::classify(vector<Flower> classifiedVec, int k, double (Flower::*distanceFunction)(Flower)){
	//this function checks the knn for an unclassified flower and changes its type.
	//the function also gets the distance function to use while calculating the knn.
	for (int i = 0; i < classifiedVec.size(); i++) {
		(classifiedVec[i].*distanceFunction)(*this);
	}//we calculate the distance of each flower from the given flower.
	vector<string> flowerTypes = getFlowerTypes(classifiedVec);
	sort(classifiedVec.begin(), classifiedVec.end(), comparison);
	//then we sort the vector according to the distance from the given flower.
	vector<int> numOfFlowerType(flowerTypes.size());
	for (int i : numOfFlowerType) i = 0;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < flowerTypes.size(); j++) {
			if (flowerTypes[j].compare(classifiedVec[i].getType()) == 0) {
				numOfFlowerType[j]++;
			}
		}
	}
	// now we know that the knn are the first k elements in the vector
	//so we calculate how many instances there are of each flower and change the flower type to the type with the most instances.
	this->setType(flowerTypes[getMaxElementIndex(numOfFlowerType)]);
}
double Flower::euclideanDistance(Flower other) {
	//the function calculates the distance between 2 flowers using the euclidean way
	double sqrDistance = 0;
	for (int i = 0; i < 4; i++) {
		sqrDistance += (this->attributes[i] - other.attributes[i]) * (this->attributes[i] - other.attributes[i]);
	}
	this->distance = sqrt(sqrDistance);
	return this->distance;
}
double Flower::manhattanDistance(Flower other) {
	//the function calculates the distance between 2 flowers using the manhattan way
	this->distance = 0;
	for (int i = 0; i < 4; i++) {
		this->distance += abs(this->attributes[i] - other.attributes[i]);
	}
	return this->distance;
}
double Flower::chebyshevDistance(Flower other) {
	//the function calculates the distance between 2 flowers using the chebyshev way
	double maxDistance = 0;
	for (int i = 0; i < 4; i++) {
		maxDistance = max(abs(this->attributes[i] - other.attributes[i]), maxDistance);
	}
	this->distance = maxDistance;
	return this->distance;
}

void Flower::setType(string type) {
	this->type = type;
}

void Flower::setAttribute(double value, int index) {
	if (index >= sizeof(this->attributes) / sizeof(this->attributes[0])) {
		return;
	}
	this->attributes[index] = value;
}
void Flower::setDistance(double distance) {
	this->distance = distance;
}

