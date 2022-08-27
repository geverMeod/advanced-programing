#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <string.h>
#include <thread>
#include <pthread.h>
#include <sstream>
#include "Iris.hpp"

using namespace std;
Iris getFlowerFromLine(string line);
vector<Iris> getFlowersFromFile(string name);

int main() {
    //needs to match the client port.
    const int server_port = 5553;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }

    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
    }

    //creat a vector of the classified flowers.
    vector<Iris> classifiedVec = getFlowersFromFile("classified.csv");
    //wait for a client to connect.
    cout << "waiting for connection..." << endl;
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock,  (struct sockaddr *) &client_sin,  &addr_len);
    if (client_sock < 0) {
        perror("error accepting client");
    }
    //
    char buffer[100];
    int expected_data_len = sizeof(buffer);
    while(true){
        int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
        if (read_bytes == 0 || buffer[0] == '\n') {
            break;// connection is closed
        }
        else if (read_bytes < 0) {
            // error
            break;
        }
        string s(buffer);
        //process the line sent from the client.
        Iris f = getFlowerFromLine(s);
        f.classify(classifiedVec, 3, &Iris::euclideanDistance);
        //send the answer to client.
        int sent_bytes = send(client_sock, f.getType().c_str(), f.getType().size()+1, 0);
        if (sent_bytes < 0) {
            perror("error sending to client");
            break;
        }
    }
    close(sock);

    return 0;
}
//this function returns a vector that contains all the flowers from the classified file. 
vector<Iris> getFlowersFromFile(string name)
{
	ifstream classified;
	classified.open(name);
	vector<Iris> classifiedVec;
	while (classified.good()) {
		string line;
		getline(classified, line);
		if (!line.empty()) {
			stringstream lineStream(line);
            string cell;
            Iris f;
            for (int i = 0; i < 4; i++) {
                getline(lineStream, cell, ',');
                f.setAttribute(stod(cell), i);
            }
            getline(lineStream, cell, ',');
            f.setType(cell);
            classifiedVec.push_back(f);
		}
	}
	return classifiedVec;
}
//works for an unclassified flower only, returns a flower object that matches the line string.
Iris getFlowerFromLine(string line){
    stringstream lineStream(line);
    string cell;
    Iris retVal;
	for (int i = 0; i < 4; i++) {
        getline(lineStream, cell, ',');
        retVal.setAttribute(stod(cell), i);
	}
    return retVal;
}