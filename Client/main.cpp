#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include "Client.hpp"
#include <thread>

void handleMessage(const string &msg, Client *client);

void receiving(Client *client);

int main() {
    Client client(inet_addr("127.0.0.1"), htons(55542));//error writing to sock is displayed wrong
    thread thread(receiving, &client);
    while (true) {
        string response;
        getline(cin, response);
        client.send(response);
    }
}

void receiving(Client *client) {
    while (true) {
        const string msg = client->receive();
        handleMessage(msg, client);
    }
}

void handleMessage(const string &msg, Client *client) {
    if (msg == "exit") {
        client->close();
        exit(0);
    }
    cout << msg << endl;
}
