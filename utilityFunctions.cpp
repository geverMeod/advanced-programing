#include "utilityFunctions.hpp"
#include <netinet/in.h>
#include <cstring>
#define END_MESSAGE "~end~"
using namespace std;
string receive(int socket){
    string packet;
    string endMessage = END_MESSAGE;
    //Read until ending is detected
    char buffer[1];
    while (!equal(endMessage.rbegin(), endMessage.rend(), packet.rbegin())) {
        buffer[0] = 0;
        int read_bytes = ::recv(socket, buffer, 1, 0);
        if (read_bytes < 0) {
            perror("error writing to sock");
        }
        packet.append(buffer);
    }
    string msg = packet.substr(0, packet.length() - 5);
    return msg;
}
void send(int socket, string msg){
    string packet = msg + END_MESSAGE;
    //Send the string through the socket
    size_t sent_bytes = ::send(socket, packet.c_str(), strlen(packet.c_str()), 0);
    if (sent_bytes < 0) {
        perror("error sending message");
    }
}