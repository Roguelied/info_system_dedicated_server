#ifndef INFO_SYSTEM_DEDICATED_SERVER_SERVER_H
#define INFO_SYSTEM_DEDICATED_SERVER_SERVER_H
#include "Database.h"



class Server {
private:
    static WSADATA wsaData;
    static ADDRINFO hints;
    static ADDRINFO* addrResult;
    static SOCKET ClientSocket;
    static SOCKET ListenSocket;

    static char SendBuffer[2048];
    static char recvBuffer[512];

public:
    static int DeleteIndex;
    static int Initialize();
    static int Listen();

};


#endif //INFO_SYSTEM_DEDICATED_SERVER_SERVER_H
