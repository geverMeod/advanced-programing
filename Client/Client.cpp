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
using namespace std;
void Client::send(const string str) const {
    //add message closer
    int sent_bytes = ::send(sock, str.c_str(), str.size(), 0);
    if (sent_bytes < 0) {
        perror("error while sending message");
    }
}

string Client::receive() const {
    string msg;
    //add format detection, maybe make this a utility function
    char buffer[1];
    buffer[0] = 0;
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    //cout << "bytes read: " << read_bytes << "\n";
    if (read_bytes < 0) {
        perror("error reading from socket");
    }
    msg.append(buffer);
    return msg;
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