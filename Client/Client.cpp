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
    //add format detection;
    char buffer[100];
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    if (read_bytes == 0){
        this->close();
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
    sin.sin_port = htons(port);

    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }
    //loop through all the lines of the unclassified file.
    // while (unclassified.good()) {  
    //     string line;
    //     getline(unclassified, line);
    //     if (line.empty()){ 
    //         break;
    //     }
    //     int data_len = line.length();
    //     int sent_bytes = send(sock, line.c_str(), data_len, 0);
    //     if (sent_bytes < 0) {
    //         perror("error while sending message");
    //         break;
    //     }
    //     char buffer[100];
    //     int expected_data_len = sizeof(buffer);
    //     int read_bytes = recv(sock, buffer, expected_data_len, 0);
    //     if (read_bytes == 0){
    //         //conection closed.
    //         break;
    //     }
    //     else if (read_bytes < 0) {
    //         perror("error, could not read server massage");
    //         break;
    //     }
    //     else {
    //         //write the flower type to the output file.
    //         classifiedOutput << buffer << endl;
    //     }
    // }
    // close(sock);
    // return 0;
}
void Client::close() const {
    ::close(this->sock);
}