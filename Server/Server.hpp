#include <netinet/in.h>
#include "string"
#pragma once
class Server
{
private:
    int clientNum = 0;
    int socketId;
    int maxQueueSize = 5;
    struct sockaddr_in readAddr;
    fd_set readfds;
    struct timeval timeVal;
public:
    Server(in_addr_t ip, in_port_t port);

    int acceptClient();
        
    void removeClient();

    void closeServerSock() const;

    ~Server() = default;

    int getClientNum() const;
};

