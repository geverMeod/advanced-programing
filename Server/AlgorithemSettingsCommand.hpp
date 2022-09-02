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
    AlgorithemSettingsCommand(DefultIO *dio, UserData *data) : Command("Algorithem Settings", dio, data) {}

    void execute()
    {
        this->getIO()->write(this->getData()->getSettingsString());
        string msg;
        //if the message is empty it means the client pressed enter
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
            this->getIO()->write("Invalid values");
            return;
        }
        try
        {
            newK = stoi(part);
            //K has to be a number bitween 1 and 10. If K is bitween 1 and 9 the size of the K part of the message must be 1, likewise if K is 10 the the size must be 2.
            if (!(0 < newK && ((newK <= 9 && part.size() == 1)||(newK == 10 && part.size() == 2))))
            {
                this->getIO()->write("Invalid value for K, must be between 1 and 10");
                return;
            }
        }
        catch (const exception &e)
        {
            this->getIO()->write("Invalid value for K, input a number");
            return;
        }
        getline(ss,part);
        //setDistanceFunction returns 0 if part does not contain a dostance function like needed.
        if (!(this->getData()->setDistanceFunction(part)))
        {
            this->getIO()->write("Invalid value for the distance function");
            return;
        }
        this->getData()->setK(newK);
        
    }
};
