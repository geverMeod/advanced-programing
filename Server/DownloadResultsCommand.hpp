#include "sstream"
#include <string>
#include "UserData.hpp"
#include "Command.hpp"
#include "../DefaultIO.hpp"
#pragma once

using namespace std;
class DownloadResultsCommand : public Command {

public:
    DownloadResultsCommand(DefultIO *dio, UserData *data) : Command("download data", dio, data) {}

    void execute() override{
        //simmilar to DisplayResultsCommand, we write all the desired text into a massage with unique text in it
        //  and send it to the client for downloading.
         if (this->getData()->getOutput().empty()) {
            this->getIO()->write("Cant return results, data not classified");
            return;
        }
        this->getIO()->write("Please enter path for the output file");
        string outputPath = this->getIO()->read();
        stringstream msg;
        msg << "FILE ~";
        for (int i = 0; i < this->getData()->getOutput().size(); i++) {
            msg << (to_string(i + 1) + ".\t" + this->getData()->getOutput().at(i)) << "\n";
        }
        msg << "~ PATH ~" << outputPath << "~";
        this->getIO()->write(msg.str());
        this->getIO()->read();
    }
};