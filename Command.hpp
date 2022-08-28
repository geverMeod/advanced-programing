#pragma once
#include <string>
#include "DefaultIO.hpp"
#include "UserData.hpp"
using namespace std;
class Command
{
private:
	string description;
    DefultIO* dio;
	UserData *data;
public:

	string getDescription() const {
		return this->description;
	}

	DefultIO *getIO() const{
		return this->dio;
	}

	UserData *getData() const {
		return data;
	}

	Command (string description, DefultIO *dio, UserData *data) :
		description(description), dio(dio), data(data) {}
    
	virtual void execute() = 0;

	virtual ~Command() = default;
};
