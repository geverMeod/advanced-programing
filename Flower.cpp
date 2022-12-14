#include "Flower.hpp"
#include <string>
#include <cmath>
using namespace std;

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

