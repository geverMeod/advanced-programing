#include "DefaultIO.hpp"
#include "string"
#include "Server/Server.hpp"
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <regex>

class SocketIO : public DefultIO
{
private:
    int sock;
public:
    explicit SocketIO(int sock) : sock(sock) {}

    string SocketIO::read() {
        string msg;
        //add format detection, maybe make this a utility function
        char buffer[1];
        buffer[0] = 0;
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);
        if (read_bytes < 0) {
            perror("error reading from socket");
        }
        msg.append(buffer);
        return msg;
    }

    void SocketIO::write(string msg) {
        int sent_bytes = ::send(sock, msg.c_str(), msg.size(), 0);
        if (sent_bytes < 0) {
            perror("error while sending message");
        }
    }

    ~SocketIO()
    {
        close(this->sock);
    }
};
