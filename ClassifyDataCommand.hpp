#include "Command.hpp"
#include "thread"
#pragma once

using namespace std;
class ClassifyDataCommand : public Command {
    public:
        
        
        ClassifyDataCommand(DefultIO* dio, UserData* data) : Command("classify data", dio, data) {}

        void execute() override{
            if (this->getData()->getUnclassified().empty())
            {
                this->getIO()->write("Please upload files first");
                return;
            }
             this->getIO()->write("Started classifying");
            //  thread classify([this] { this->getData()->classify(); });
            thread classify(&UserData::classify, this->getData());
            classify.detach();
        }
};