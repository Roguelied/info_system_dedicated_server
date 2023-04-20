#ifndef INFO_SYSTEM_DEDICATED_SERVER_SERVER_H
#define INFO_SYSTEM_DEDICATED_SERVER_SERVER_H
#include "Utility.h"


class Server {
private:
    static WSADATA wsaData;
    static ADDRINFO hints;
    static ADDRINFO* addrResult;
    static SOCKET ClientSocket;
    static SOCKET ListenSocket;

    static char SendBuffer[512];
    static char recvBuffer[512];

public:

    static int Initialize();
    static int Listen();

};

ADDRINFO* Server::addrResult = NULL;
SOCKET Server::ClientSocket = INVALID_SOCKET;
SOCKET Server::ListenSocket = INVALID_SOCKET;

#endif //INFO_SYSTEM_DEDICATED_SERVER_SERVER_H
