#include "utilityFunctions.hpp"
#include <netinet/in.h>
#include <cstring>
#include <stdexcept>
#define END_MESSAGE "~end~"
using namespace std;
//recive message from socket
string receive(int socket){
    string packet;
    string endMessage = END_MESSAGE;
    //Read until ending is detected
    char buffer[1];
    while (!equal(endMessage.rbegin(), endMessage.rend(), packet.rbegin())) {
        buffer[0] = 0;
        int read_bytes = ::recv(socket, buffer, 1, 0);
        if (read_bytes < 0) {
           throw runtime_error("error reciving from sock");
        }
        packet.append(buffer);
    }
    string msg = packet.substr(0, packet.length() - 5);
    return msg;
}
//send message to socket
void send(int socket, string msg){
    string packet = msg + END_MESSAGE;
    //Send the string through the socket
    size_t sent_bytes = ::send(socket, packet.c_str(), strlen(packet.c_str()), 0);
    if (sent_bytes < 0) {
        throw runtime_error("error writing to sock");
    }
}