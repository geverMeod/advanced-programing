#include "Command.hpp"
#pragma once
using namespace std;
class DisplayResultsCommand : public Command {
public:
    void execute() override {
        if (this->getData()->getOutput().size() == 0) {
            this->getIO()->write("Cant display results, data not classified");
            return;
        }
        this->getIO()->write("output:\n");
        for (int i = 0; i < this->getData()->getOutput().size(); i++) {
            this->getIO()->write(to_string(i + 1) + ".\t" + this->getData()->getOutput().at(i));
        }
        this->getIO()->write("Done.");
        this->getIO()->read(); // Waiting for client to press enter.
    }

    DisplayResultsCommand(DefultIO *dio, UserData *data) : Command("display data", dio, data) {}
};