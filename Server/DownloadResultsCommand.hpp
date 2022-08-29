#include "sstream"
#include <string>
#include "UserData.hpp"
#include "Command.hpp"
#include "DefaultIO.hpp"
#pragma once

using namespace std;
class DownloadResultsCommand : public Command {

public:
    DownloadResultsCommand(DefultIO *dio, UserData *data) : Command("download data", dio, data) {}

    void execute() override{
         if (this->getData()->getOutput().empty()) {
            this->getIO()->write("Cant return results, data not classified");
            return;
        }
        this->getIO()->write("Please enter path for the output file");
        string outputPath = this->getIO()->read();
        this->getIO()->write("Enter path for the output file");
        
    }
};