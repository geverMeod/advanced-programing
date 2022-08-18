#include "Flower.hpp"
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;
//a comparison method used to sort the flowers by distance.
bool Flower::comparison(Flower a, Flower b)
{
	return (a.getDistance() < b.getDistance());
}
//returns true if the str vector contains s.
bool Flower::contains(vector<string> vec, string s) {
	for (string x : vec) {
		if (x.compare(s) == 0) return true;
	}
	return false;
}
//returns the index of the largest element in the int vector.
int Flower::getMaxElementIndex(vector<int> vector){
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
	//this function checks the knn for an this flower and classifies it, we assume this flower is not classified.
	//the function gets the distance function to use while calculating the knn.
	for (int i = 0; i < classifiedVec.size(); i++) {
		(classifiedVec[i].*distanceFunction)(*this);
	}//we calculate the distance of each flower from this flower.
	vector<string> flowerTypes = getFlowerTypes(classifiedVec);
	sort(classifiedVec.begin(), classifiedVec.end(), comparison);
	//then we sort the vector according to the distance from this flower.
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
	// now we know that the knn are the first k elements in the vector so we count
	// how many instances there are of each type and classify this flower to be of the type with the most instances.
	this->setType(flowerTypes[getMaxElementIndex(numOfFlowerType)]);
}
double Flower::euclideanDistance(Flower other) {
	//the function calculates the euclidean distance between 2 flowers
	double sqrDistance = 0;
	for (int i = 0; i < 4; i++) {
		sqrDistance += (this->attributes[i] - other.attributes[i]) * (this->attributes[i] - other.attributes[i]);
	}
	this->distance = sqrt(sqrDistance);
	return this->distance;
}
double Flower::manhattanDistance(Flower other) {
	//the function calculates the manhattan distance between 2 flowers.
	this->distance = 0;
	for (int i = 0; i < 4; i++) {
		this->distance += abs(this->attributes[i] - other.attributes[i]);
	}
	return this->distance;
}
double Flower::chebyshevDistance(Flower other) {
	//the function calculates the chebyshev distance between 2 flowers.
	double maxDistance = 0;
	for (int i = 0; i < 4; i++) {
		maxDistance = max(abs(this->attributes[i] - other.attributes[i]), maxDistance);
	}
	this->distance = maxDistance;
	return this->distance;
}
//setters
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

