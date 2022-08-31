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

    string distanceFunction;

    int k;

public:
    UserData() :
        trainingData(), unclassified(), output(), k(5), distanceFunction("EUC"){}

    void classify() {
        output.clear();
        output.resize(unclassified.size());
        for (int i = 0; i < unclassified.size(); i++){
            if (distanceFunction.compare("EUC"))
            {
                output.at(i) = unclassified.at(i).classify(trainingData, k, &Iris::euclideanDistance);
            } else if (distanceFunction.compare("MAN"))
            {
                output.at(i) = unclassified.at(i).classify(trainingData, k, &Iris::manhattanDistance);
            } else if (distanceFunction.compare("CHE"))
            {
                output.at(i) = unclassified.at(i).classify(trainingData, k, &Iris::chebyshevDistance);
            } 
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
    string getDistanceFunction(){
        return this->distanceFunction;
    }
    int setDistanceFunction(string s){
        if (!(s.compare("EUC")||s.compare("MAN")||s.compare("CHE"))){
            return 0;
        }
        this->distanceFunction = s;
        return 1;
    }
    int getK(){
        return this->k;
    }
    void setK(int newK){
        this->k = newK;
    }
    string getSettingsString(){
        return "The current KNN paramethers are: k = " + to_string(this->getK()) +
                                ", distance metric = " + this->getDistanceFunction();
    }
};
