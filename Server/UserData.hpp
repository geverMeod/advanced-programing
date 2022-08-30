#pragma once
#include "Iris.hpp"
using namespace std;
class UserData {
private:
    //classified training data
    vector<Iris> trainingData;
    //user data to be classified
    vector<Iris> unclassified;
    //the classified output
    vector<string> output;
    //all of the iris types in the output, calculated in the classify method
    vector<string> irisTypes;

    double distanceFunction(Iris); 
    int k;

public:
    UserData() :
        trainingData(), unclassified(), output(){}

    void classify() {
        output.clear();
        output.resize(unclassified.size());
        for (int i = 0; i < unclassified.size(); i++){
            output.at(i) = unclassified.at(i).classify(trainingData, 3, &Iris::euclideanDistance);//add more distance functions
        }
        irisTypes = Iris::getFlowerTypes(trainingData);
    }

    const vector<Iris> getTrainingData() const {
        return trainingData;
    }

    void setTrainingData(vector<Iris> v) {
        trainingData = v;
    }

    const vector<Iris> getUnclassified() const {
        return unclassified;
    }

    void setUnclassified(vector<Iris> v) {
        unclassified = v;
    }
    //get the clssified output vector
    const vector<string> getOutput(){
        return output;
    } 

    vector<string> getIrisTypes(){
        return this->irisTypes;
    }
};
