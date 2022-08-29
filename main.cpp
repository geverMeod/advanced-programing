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
        thread handlingClient(handleClient, clientSock, &server);
        handlingClient.detach();
    }
    while (server.getClientNum()) {}
    server.closeServerSock();
}
void handleClient(int clientSock, Server *server) {
    UserData data();
    StandardIO sio();
    vector<unique_ptr<Command>> commands;
    commands.emplace_back(make_unique<UploadFilesCommand>((DefultIO *)&sio, (UserData*) &data));
    commands.emplace_back(make_unique<ClassifyDataCommand>((DefultIO *)&sio, (UserData*) &data));
    commands.emplace_back(make_unique<DisplayResultsCommand>((DefultIO *)&sio, (UserData*) &data));

    CLI cli((DefultIO *)&sio, commands);
    cli.start();
    server->removeClient();
}