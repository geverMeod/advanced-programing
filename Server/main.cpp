#include <memory>
#include <vector>
#include "Iris.hpp"
#include "thread"
#include "UserData.hpp"
#include "Server.hpp"
#include "DisplayResultsCommand.hpp"
#include "UploadFilesCommand.hpp"
#include "ClassifyDataCommand.hpp"
#include "ConfusionMatrixCommand.hpp"
#include "AlgorithemSettingsCommand.hpp"
#include "Command.hpp"
#include "../StandardIO.hpp"
#include "../SocketIO.hpp"
#include "CLI.hpp"
#include <pthread.h>
void handleClient(int clientSock, Server *server);
void *foo(void* a);
int main(int argc, char* argv[])
{
    Server server(INADDR_ANY, htons(55537));
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
    UserData data = UserData();
    SocketIO sio = SocketIO(clientSock);
    vector<unique_ptr<Command>> commands;
    commands.emplace_back(make_unique<UploadFilesCommand>(&sio, &data));
    commands.emplace_back(make_unique<AlgorithemSettingsCommand>(&sio, &data));
    commands.emplace_back(make_unique<ClassifyDataCommand>(&sio, &data));
    commands.emplace_back(make_unique<DisplayResultsCommand>(&sio, &data));
    //download results
    commands.emplace_back(make_unique<ConfusionMatrixCommand>(&sio, &data));

    CLI cli((DefultIO *)&sio, move(commands));
    cli.start();
    server->removeClient();
}