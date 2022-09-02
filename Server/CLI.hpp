#pragma once
#include <utility>
#include <vector>
#include "Command.hpp"
#include <memory>
using namespace std;
class CLI {
private:
    DefultIO *dio;
    vector<unique_ptr<Command>> commands;

    void printCommandMenu() {
        string msg = "Welcome to the KNN Classifier Server. Please choose an option:";
        for (int i = 0; i < commands.size(); i++) {
            msg.append("\n" + to_string(i + 1) + ". " + (commands.at(i))->getDescription());
        }
        msg.append("\n" + to_string(commands.size() + 1) + ". exit");
        dio->write(msg);
    }

public:
    CLI(DefultIO *dio, vector<unique_ptr<Command>> commands) : dio(dio), commands(move(commands)) {
    }

    void start() {
        while (true) {
            printCommandMenu();
            string optionStr = dio->read();
            int option;
            try {
                option = stoi(optionStr) - 1;
            }
            catch (const exception &e) {
                dio->write("Please enter a number");
                continue;
            }
            if (option < 0 || option > commands.size()) {
                dio->write("Invalid command, input a number between 1 and " + to_string(commands.size() + 1));
                continue;
            }
            if (option == commands.size()) {
                dio->write("exit");
                break;
            }
            commands.at(option)->execute();
        }
    }
};
