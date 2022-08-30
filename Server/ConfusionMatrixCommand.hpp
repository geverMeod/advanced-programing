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
        //Create a map containing all predictions and types
        map<string, map<string, double>> typeMap;
        for (int i = 0; i < expectations.size(); i++) {
            if (!typeMap[test[i].getType()].count(predictions[i])) {
                typeMap[test[i].getType()][predictions[i]] = 0;
            }
            typeMap[test[i].getType()][predictions[i]]++;
        }

        vector<string> types;
        for (const auto &pair: typeMap) {
            //Save all test types
            types.push_back(pair.first);
            //sum all predictions
            double sum = 0;
            for (const auto &keys: pair.second) {
                sum += keys.second;
            }
            //Convert the numbers to percentages
            for (const auto &keys: pair.second) {
                typeMap[pair.first][keys.first] = 100 * keys.second / sum;
            }
        }
        //Add missing types
        for (const auto &pair: typeMap) {
            for (const string &type: types) {
                if (!typeMap[pair.first].count(type)) {
                    typeMap[pair.first][type] = 0;
                }
            }
        }
        //Convert the map to a matrix of strings
        vector<vector<string>> matrix;
        for (const auto &predictionPercentage: typeMap) {
            vector<string> currPredictions;
            for (const auto &prediction: predictionPercentage.second) {
                currPredictions.push_back(to_string(prediction.second));
            }
            matrix.push_back(currPredictions);
        }

        ConfusionMatrix m(matrix, types);
        this->getIO()->write(m.toString());
        this->getIO()->write(this->getData()->getClassifier()->toString());
    }
};


#endif //TESTING_CONFUSIONMATRIXCOMMAND_H