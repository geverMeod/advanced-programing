#pragma once
#include <string>
#include "DefaultIO.hpp"
using namespace std;
class Command
{
private:
	string description;
    DefultIO* dio;

public:

	string getDescription() {
		return this->description;
	}
	void setDescription(string description);

    virtual void execute() = 0;

};
