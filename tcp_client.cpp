#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>
#include "Flower.hpp"
using namespace std;


int main(int argc, char** argv){
	if (argc < 3) {
		cout << "Error, Invalid usage" << endl;
		exit(1);
	}
    string inputFile = argv[1];
    string outputFile = argv[2];
    ifstream unclassified;
    unclassified.open(inputFile);
    ofstream classifiedOutput;
    classifiedOutput.open(outputFile);
    const char* ip_address = "127.0.0.1";
    const int port_no = 5553;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);

    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }
    while (unclassified.good()) {  
        string line;
        getline(unclassified, line);
        if (line.empty()){
            break;
        }
        int data_len = line.length();
        int sent_bytes = send(sock, line.c_str(), data_len, 0);
        if (sent_bytes < 0) {
            perror("error while sending message");
            break;
        }
        char buffer[1000];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            break;
        }
        else if (read_bytes < 0) {
            perror("error, could not read server massage");
            break;
        }
        else {
            classifiedOutput << buffer << endl;
        }
    }
    close(sock);


    return 0;
}