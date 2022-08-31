#include "Command.hpp"
#include "UserData.hpp"
#include <algorithm>
#include <memory>
#include "../utilityFunctions.hpp"
#include <sstream>
#include <string>
#pragma once

using namespace std;
class AlgorithemSettingsCommand : public Command
{

public:
    AlgorithemSettingsCommand(DefultIO *dio, UserData *data) : Command("Algorithe Settings", dio, data) {}

    void execute()
    {
        this->getIO()->write(this->getData()->getSettingsString());
        string msg;
        msg = this->getIO()->read();
        if (msg.empty())
        {
            return;
        }
        stringstream ss(msg);
        string part;

        int newK = 0;

        if (!getline(ss, part, ' '))
        {
            perror("Invalid values");
            return;
        }
        try
        {
            if (0 < stoi(part) && stoi(part) < 10)
            {
                newK = stoi(part);
            }
        }
        catch (const exception &e)
        {
            perror("Invalid value for K");
            return;
        }
        if (!(this->getData()->setDistanceFunction(ss.str())))
        {
            perror("Invalid value for the distance function");
            return;
        }
        this->getData()->setK(newK);
        
    }
};
