#pragma once
#include <string>

using namespace std;
class DefultIO
{
public:
    virtual string read() = 0;
    virtual void write(string) = 0;
};
