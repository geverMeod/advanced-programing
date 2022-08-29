#include <unistd.h>
#include "cstring"
#include <iostream>

#include "Server.hpp"
using namespace std;
Server::Server(in_addr_t ip, in_port_t port){
    readAddr = sockaddr_in();
    socketId = socket(AF_INET, SOCK_STREAM, 0);
    if (socketId < 0)
    {
        perror("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = ip;
    sin.sin_port = port;

    if (bind(socketId, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }

    if (listen(socketId, this->maxQueueSize) < 0) {
        perror("error listening to a socket");
    }

    memset(&timeVal, 0, sizeof(timeVal));
    // Timeout in seconds.
    timeVal.tv_sec = 120;

    FD_ZERO(&readfds);
    FD_SET(socketId, &readfds);

    //wait for a client to connect.
    cout << "waiting for connection..." << endl; 
}

int Server::acceptClient(){
    if (select(socketId + 1, &readfds, nullptr, nullptr, &timeVal) < 0) {
        perror("selection error");
    }
    if (FD_ISSET(socketId, &readfds)) {
        unsigned int addrLen = sizeof(this->readAddr);
        int sock = accept(socketId, (struct sockaddr *) &readAddr, &addrLen);
        if (sock < 0) {
            perror("error accepting client");
        }
        this->clientNum++;
        return sock;
    }
    return -1;
}

void Server::removeClient()
{
    this->clientNum--;
}

void Server::closeServerSock() const
{
    close(this->socketId);
}

int Server::getClientNum() const
{
    return this->clientNum;
}