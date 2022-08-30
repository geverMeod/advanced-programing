#include "Command.hpp"
#include <vector>
#include <string>
#include "Iris.hpp"
#include <map>

#pragma once

class ConfusionMatrixCommand : public Command{
public:
    ConfusionMatrixCommand(DefultIO *dio, UserData *data) : 
        Command("display algorithm confusion matrix", dio, data) {}

    void execute() override {
        vector<Iris> expectations = this->getData()->getUnclassified();
        vector<string> predictions = this->getData()->getOutput();
        vector<string> irisTypes = this->getData()->getIrisTypes();
        if (predictions.empty() || irisTypes.empty()) {
            this->getIO()->write("Classify first");
            return;
        }
        //Create a map containing all types and their expectations,
        //at this stage the double value is the count of the predictions
        map<string, map<string, double>> typeCountMap;
        for (int i = 0; i < expectations.size(); i++) {
            string type = expectations.at(i).getType();
            if (!typeCountMap[type].count(predictions[i])) {
                typeCountMap[type][predictions[i]] = 0.0;
            }
            typeCountMap[type][predictions[i]] += 1.0;
        }
        for (const pair<string, map<string, double>> &p: typeCountMap) {
            //sum all predictions
            double sum = 0.0;
            for (const pair<string, double> &keys: (p.second)) {
                sum += keys.second;
            }
            //Convert the numbers to percentages
            for (const pair<string, double> &keys: p.second) {
                typeCountMap[p.first][keys.first] = 100 * keys.second / sum;
            }
        }
        //Add missing types
        for (const pair<string, map<string, double>> &p: typeCountMap) {
            for (const string &type: irisTypes) {
                if (!p.second.count(type)) { //maybe a problam here
                    typeCountMap[p.first][type] = 0;
                }
            }
        }
        //Convert the map to a 2d vector of strings
        // vector<vector<string>> confusionMatrix;
        // for (const pair<string, map<string, double>> &predictionPercentage: typeCountMap) {
        //     vector<string> typePredictions;
        //     for (const pair<string, double> &prediction: predictionPercentage.second) {
        //         typePredictions.push_back(to_string(prediction.second));
        //     }
        //     confusionMatrix.push_back(typePredictions);
        // }
        string confusionMatrixStr("\t\t");
        for(string type: irisTypes){
            confusionMatrixStr.append(type + "\t");
        }
        confusionMatrixStr.append("\n");
        for(string expectationType: irisTypes){
            confusionMatrixStr.append(expectationType + "\t");
            for(string predictionType: irisTypes){
                confusionMatrixStr.append(to_string(typeCountMap[expectationType][predictionType]) + "\t");
            }
            confusionMatrixStr.append("\n");
        }
        this->getIO()->write(confusionMatrixStr);
        //this->getIO()->write(this->getData()->getClassifier()->toString());
    }
};
