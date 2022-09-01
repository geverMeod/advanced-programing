#include "Command.hpp"
#include "vector"
#include "Iris.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#pragma once

using namespace std;
vector<Iris> getIrisVecFromFile(string fileName, bool isClassified);
Iris getIrisFromLine(string line, bool isClassified);
class UploadFilesCommand : public Command {
public:
    void execute() override {
        this->getIO()->write("Please upload your local train csv file");
        string input = this->getIO()->read();
        if (input.empty()) {
            this->getIO()->write("Invalid file");
            return;
        }
        try {
            this->getData()->setTrainingData(getIrisVecFromFile(input, true));
        }
        catch (invalid_argument &e) {
            this->getIO()->write("Invalid argumants in file: ");
            this->getIO()->write(e.what());
            return;
        }
        catch (exception &e) {
            this->getIO()->write("Invalid file");
            return;
        }
        this->getIO()->write("Upload Complete.");
        this->getIO()->write("Please upload your local test csv file");
        input = this->getIO()->read();
        if (input.empty()) {
            this->getIO()->write("Invalid file");
            return;
        }
        try {
            this->getData()->setUnclassified(getIrisVecFromFile(input, true));
        }
        catch (invalid_argument &e) {
            this->getIO()->write("Invalid argumants in file: ");
            this->getIO()->write(e.what());
            return;
        }
        catch (exception &e) {
            this->getIO()->write("Invalid file");
            return;
        }
        if(this->getData()->getTrainingData().at(0).getAttributes().size() != this->getData()->getUnclassified().at(0).getAttributes().size()){
            this->getIO()->write("Training data and test attributes dont match");
            return;
        }
        this->getIO()->write("Upload Complete");
    }

    UploadFilesCommand(DefultIO *dio, UserData *data) :
            Command("upload an unclassified csv data file", dio, data) {}
};
//returns a flower object that matches the line string.
Iris getIrisFromLine(string line, bool isClassified){
    stringstream lineStream(line);
    vector<string> irisAttributes;
    string cell;
    Iris retVal;
    while(getline(lineStream, cell, ',')){
        irisAttributes.push_back(cell);
    }
    if (irisAttributes.size() < 2) {
        throw invalid_argument("Iris should have at least one attribute");
    }
	for (int i = 0; i < irisAttributes.size() - 1; i++) {
        retVal.pushAttribute(stod(irisAttributes.at(i)));
	}
    if(isClassified){
        retVal.setType(irisAttributes.at(irisAttributes.size() - 1));
    }
    return retVal;
}
//this function returns a vector that contains all the flowers from the classified/unclassified file. 
vector<Iris> getIrisVecFromFile(string fileName, bool isClassified)
{
	ifstream classified;
	classified.open(fileName);
    if(!classified.is_open()){
        throw runtime_error("Could not open file");
    }
	vector<Iris> retVal;
	while (classified.good()) {
		string line;
		getline(classified, line);
		if (!line.empty()) {
            Iris current = getIrisFromLine(line,isClassified);
            if(retVal.size() > 1 && current.getAttributes().size() != retVal.at(0).getAttributes().size()){
                throw invalid_argument("All irises should have the same number of attributes");
            }
            retVal.push_back(current);
		}
	}
	return retVal;
}
