#include "Command.hpp"
#include "UserData.hpp"
#include "algorithm"
#include <memory>
#include "../utilityFunctions.hpp"
#pragma once


class AlgorithemSettingsCommand : public Command
{

public:
    AlgorithemSettingsCommand(DefultIO *dio, UserData *data) : Command("Algorithe Settings", dio, data) {}

    void execute(){
        this->getIO()->write(this->getData()->getSettingsString());
        string msg;
        msg = this->getIO()->read();
        if (msg.compare(""))
        {
            return;
        }
        
    }
};
