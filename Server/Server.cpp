#include <unistd.h>
#include "cstring"
#include <iostream>

#include "Server.hpp"
using namespace std;
Server::Server(in_addr_t ip, in_port_t port) {
    readAddr = sockaddr_in();
    socketId = socket(AF_INET, SOCK_STREAM, 0);
    //return if the socket creation failed
    if (socketId < 0)
    {
        perror("error creating socket");
        return;
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = ip;
    sin.sin_port = port;
    //return if the socket binding failed
    if (bind(socketId, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
        return;
    }
    //return if there is an error while listning to sockets.
    if (listen(socketId, this->maxQueueSize) < 0) {
        perror("error listening to a socket");
        return;
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
    //select is used to get a time limit for the socket.
    if (select(socketId + 1, &readfds, nullptr, nullptr, &timeVal) < 0) {
        perror("selection error");
    }
    if (FD_ISSET(socketId, &readfds)) {
        unsigned int addrLen = sizeof(this->readAddr);
        //accepting a new client
        int sock = accept(socketId, (struct sockaddr *) &readAddr, &addrLen);
        if (sock < 0) {
            perror("error accepting client");
        }
        this->clientNum++;
        cout << "accepted a new client\n"; 
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