#include <memory>
#include <vector>
#include "Iris.hpp"
#include "thread"
#include "UserData.hpp"
#include "Server.h"
#include "DisplayResultsCommand.hpp"
#include "UploadFilesCommand.hpp"
#include "ClassifyDataCommand.hpp"
#include "StandardIO.hpp"

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
    StandardIO io();
    std::vector<std::unique_ptr<Command>> commands;
    commands.push_back(std::make_unique<UploadFilesCommand>(&io, &data));
    commands.push_back(std::make_unique<ClassifyDataCommand>(&io, &data));
    commands.push_back(std::make_unique<DisplayResultsCommand>(&io, &data));

    CLI<Iris> cli(&io, std::move(commands));
    cli.run();
    server->disconnectClient();
}