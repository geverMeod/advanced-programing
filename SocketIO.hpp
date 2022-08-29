#include "DefaultIO.hpp"
#include "utilityFunctions.hpp"
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

    string read() {
        return receive(sock);
    }

    void write(string msg) {
        send(sock, msg);
    }

    ~SocketIO()
    {
        close(this->sock);
    }
};
