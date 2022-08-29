#pragma once
#include <netinet/in.h>
#include <string>
using namespace std;
class Client {
private:
    int sock;
    struct sockaddr_in sin;
public:
    string receive() const;

    void send(const string) const;

    void close() const;

    Client(in_addr_t, in_port_t);

    ~Client() = default;
};
