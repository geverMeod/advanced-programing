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
    std::vector<std::unique_ptr<Command>> commands;
    commands.push_back(std::make_unique<UploadFilesCommand>(&sio, &data));
    commands.push_back(std::make_unique<ClassifyDataCommand>(&sio, &data));
    commands.push_back(std::make_unique<DisplayResultsCommand>(&sio, &data));

    CLI cli(&sio, std::move(commands));
    cli.start();
    server->disconnectClient();
}