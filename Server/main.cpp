#include <memory>
#include <vector>
#include "Iris.hpp"
#include "thread"
#include "UserData.hpp"
#include "Server.hpp"
#include "DisplayResultsCommand.hpp"
#include "UploadFilesCommand.hpp"
#include "ClassifyDataCommand.hpp"
#include "Command.hpp"
#include "../StandardIO.hpp"
#include "../DefaultIO.hpp"
#include "CLI.hpp"
#include <pthread.h>
void handleClient(int clientSock, Server *server);
void *foo(void* a);
int main(int argc, char* argv[])
{
    StandardIO sio = StandardIO();
    Server server(INADDR_ANY, htons(55555));
    int clientSock = server.acceptClient();
    while (true) {
        int clientSock = server.acceptClient();

        if (clientSock == -1) {
            break;
        }
        pthread_t t;
        thread handlingClient(handleClient, clientSock, &server);
        handlingClient.detach();
    }
    while (server.getClientNum()) {}
    server.closeServerSock();
}

void handleClient(int clientSock, Server *server) {
    UserData data = UserData();
    StandardIO sio = StandardIO();
    vector<unique_ptr<Command>> commands;
    commands.emplace_back(make_unique<UploadFilesCommand>(&sio, &data));
    commands.emplace_back(make_unique<ClassifyDataCommand>(&sio, &data));
    commands.emplace_back(make_unique<DisplayResultsCommand>(&sio, &data));

    CLI cli((DefultIO *)&sio, move(commands));
    cli.start();
    server->removeClient();
}