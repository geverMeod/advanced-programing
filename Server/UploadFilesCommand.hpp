#include "Command.hpp"
#include "vector"
#include "Iris.hpp"
#include <fstream>
#include <sstream>
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
            this->getData()->setUnclassified(getIrisVecFromFile(input, false));
        }
        catch (exception &e) {
            this->getIO()->write("Invalid file");
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
    string cell;
    Iris retVal;
	for (int i = 0; i < 4; i++) {
        getline(lineStream, cell, ',');
        retVal.setAttribute(stod(cell), i);
	}
    if(isClassified){
        getline(lineStream, cell, ',');
        retVal.setType(cell);
    }
    return retVal;
}
//this function returns a vector that contains all the flowers from the classified/unclassified file. 
vector<Iris> getIrisVecFromFile(string fileName, bool isClassified)
{
	ifstream classified;
	classified.open(fileName);
    if(!classified.is_open()){
        throw std::runtime_error("Could not open file");
    }
	vector<Iris> classifiedVec;
	while (classified.good()) {
		string line;
		getline(classified, line);
		if (!line.empty()) {
            classifiedVec.push_back(getIrisFromLine(line,isClassified));
		}
	}
	return classifiedVec;
}
