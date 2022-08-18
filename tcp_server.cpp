#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <string>
#include <sstream>
#include "Flower.hpp"

using namespace std;
Flower getFlowerFromLine(string line);
vector<Flower> getFlowersFromFile(string name);
int main() {

    const int server_port = 5553;
    //gal hage
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }//gal hage

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }
    // int zero = 1;
    // if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &zero, sizeof(int)) < 0) {
    //     perror("error encountered when changing socket options");
    // }
    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
    }
    vector<Flower> classifiedVec = getFlowersFromFile("classified.csv");
    cout << "waiting for connection..." << endl;
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock,  (struct sockaddr *) &client_sin,  &addr_len);
    if (client_sock < 0) {
        perror("error accepting client");
    }
    
    char buffer[1000];
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
        
        Flower f = getFlowerFromLine(s);
        
        f.classify(classifiedVec, 3, &Flower::euclideanDistance);

        int sent_bytes = send(client_sock, f.getType().c_str(), f.getType().size()+1, 0);

        if (sent_bytes < 0) {
            perror("error sending to client");
            break;
        }
    }
    close(sock);

    return 0;
}
vector<Flower> getFlowersFromFile(string name)
{
	//this function returns a vector that contains all the flowers from the classified file. 
	ifstream classified;
	classified.open(name);
	vector<Flower> classifiedVec;
	while (classified.good()) {
		string line;
		getline(classified, line);
		if (!line.empty()) {
			stringstream lineStream(line);
            string cell;
            Flower f;
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
//works for an unclassified flower only.
Flower getFlowerFromLine(string line){
    stringstream lineStream(line);
    string cell;
    Flower retVal;
	for (int i = 0; i < 4; i++) {
        getline(lineStream, cell, ',');
        retVal.setAttribute(stod(cell), i);
	}
    return retVal;
}