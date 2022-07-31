// C++ program to find groups of unknown
// Points using K nearest neighbour algorithm.
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Flower.h"

using namespace std;

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
int getMaxElementIndex(vector<int> vector)
{
	//returns the number of which the vector value is the biggest.
	int maxElementIdx = 0;
	for (int i = 0; i < vector.size(); i++)
	{
		if (vector[maxElementIdx] < vector[i]) maxElementIdx = i;
	}
	return maxElementIdx;
}

string classifyAPoint(vector<Flower> classifiedVec, int k, Flower f, double (Flower::*distanceFunction)(Flower))
{
	//this function checks the knn for an unclassified flower and returns its type.
	//the function also gets the distance function to use while calculating the knn.
	for (int i = 0; i < classifiedVec.size(); i++) {
		(classifiedVec[i].*distanceFunction)(f);
	}//we calculate the distance of each flower from the given flower.
	vector<string> flowerTypes = getFlowerTypes(classifiedVec);
	sort(classifiedVec.begin(), classifiedVec.end(), comparison);
	//then we sort the vector according to the distance from the given flower.
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
	// now we know that the knn are the first k elements in the vector
	//so we calculate how many instances there are of each flower and return the type with the most instances.
	return flowerTypes[getMaxElementIndex(numOfFlowerType)];
}

vector<Flower> getFlowersFromFile(string name)
{
	//this function returns a vector that contains all the flowers from the classified file. 
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
void createAndRun(int k)
{
	ofstream euclideanFile, manhattenFile, chebyshevFile;
	euclideanFile.open("euclidean_output.csv");
	manhattenFile.open("manhattan_output.csv");
	chebyshevFile.open("chebyshev_output.csv");
	//creating all the output files
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
			//we get the unclassified flower from the unclasified file and fide its type according to the diffrent distance functions.
		}
	}
	euclideanFile.close();
	manhattenFile.close();
	chebyshevFile.close();
}

int main(int argc, char** argv)
{
	if (argc < 2) {
		cout << "Error, Invalid usage" << endl;
		exit(1);
	}
	int k;
	k = atoi(argv[1]);
	createAndRun(k);
	return 0;
}

