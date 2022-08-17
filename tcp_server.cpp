#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {

    const int server_port = 5550;
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
    int zero = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &zero, sizeof(int)) < 0) {
        perror("error encountered when changing socket options");
    }
    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
    }
    cout << "waiting for connection..." << endl;
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock,  (struct sockaddr *) &client_sin,  &addr_len);

    if (client_sock < 0) {
        perror("error accepting client");
    }

    char buffer[4096];
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
        else {
            cout << "client message: " << buffer;
        }

        int sent_bytes = send(client_sock, buffer, read_bytes, 0);

        if (sent_bytes < 0) {
            perror("error sending to client");
            break;
        }
    }
    close(sock);

    return 0;
}