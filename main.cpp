#include <memory>
#include <vector>
#include "Iris.hpp"
#include "thread"
#include "UserData.hpp"
#include "Server.h"
#include "DisplayResultsCommand.hpp"
#include "UploadFilesCommand.hpp"
#include "ClassifyDataCommand.hpp"
#include "Command.hpp"
#include "StandardIO.hpp"
#include "DefaultIO.hpp"
#include "CLI.hpp"
#pragma once

void handleClient(int clientSock, Server *server);

int main(int argc, char* argv[])
{
    Server server(INADDR_ANY, htons(5555));
    int clientSock = server.acceptClient();

     while (true) {
        int clientSock = server.acceptClient();

        if (clientSock == -1) {
            break;
        }
        std::thread handlingClient(handleClient, clientSock, &server);
        handlingClient.detach();
    }
    while (server.getClientNum()) {}
    server.closeServerSock();
}
void handleClient(int clientSock, Server *server) {
    UserData data();
    StandardIO sio();
    vector<Command> commands;
    commands.push_back(UploadFilesCommand((DefultIO *)&sio, (UserData*) &data));
    commands.push_back(ClassifyDataCommand((DefultIO *)&sio, (UserData*) &data));
    commands.push_back(DisplayResultsCommand((DefultIO *)&sio, (UserData*) &data));

    CLI cli((DefultIO *)&sio, std::move(commands));
    cli.start();
    server->removeClient();
}