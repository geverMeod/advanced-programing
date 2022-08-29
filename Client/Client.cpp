#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>
#include "Client.hpp"
#include "../utilityFunctions.hpp"
using namespace std;
void Client::send(const string str) const {
    ::send(sock, str);
}

string Client::receive() const {
    //add format detection, maybe make this a utility function
    return ::receive(sock);
}
Client::Client(in_addr_t ip, in_port_t port) : sock(socket(AF_INET, SOCK_STREAM, 0)), sin(){
    if (sock < 0) {
        perror("error creating socket");
    }
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = ip;
    sin.sin_port = port;

    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }
}
void Client::close() const {
    ::close(this->sock);
}