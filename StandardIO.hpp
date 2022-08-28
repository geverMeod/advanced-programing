#include "DefaultIO.hpp"
#include "iostream"
#include "string"

#pragma once

using namespace std;
class StandardIO : DefultIO
{
private:
    /* data */
public:
    StandardIO() = default;
    ~StandardIO() = default;
    string read() override{
        string s;
        getline(cin, s);
        return s;
    }
    void write(string s) override{
        cout << s << endl;
    }
};