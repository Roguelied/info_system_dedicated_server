#include "Server.h"

int Server::Initialize() {

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "WSAStartup failed";
        return -1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; //семейтво протоколов //ipv4 ethernet
    hints.ai_socktype = SOCK_STREAM; //тип сокета
    hints.ai_protocol = IPPROTO_TCP; //tcp протокол
    hints.ai_flags = AI_PASSIVE;


    //инит адреса
    if (getaddrinfo(NULL, "666", &hints, &addrResult) != 0) {
        //"GetAddrInfo failed";
        freeaddrinfo(addrResult);
        WSACleanup();
        return -2;
    }

    ListenSocket = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        // "ListenSocket creation failed";
        freeaddrinfo(addrResult);
        WSACleanup();
        return -3;
    }


    if (bind(ListenSocket, addrResult->ai_addr, (int)addrResult->ai_addrlen) == SOCKET_ERROR) {
        //"Bind socket failed";
        closesocket(ListenSocket);
        ListenSocket  = INVALID_SOCKET;
        freeaddrinfo(addrResult);
        WSACleanup();
        return -4;
    }
}

int Server::Listen() {

    int Result;

    //Start Listen
    Result = listen(ListenSocket, SOMAXCONN);
    if (Result == SOCKET_ERROR) {
        cout << "Listening socket failed" << endl;
        closesocket(ListenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return -5;
    }

    //Set Client connecttion to ClientSocket from Server side
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        cout << "Accepting socket failed" << endl;
        closesocket(ListenSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    //Close Listen Socket
    closesocket(ListenSocket);


    do {
        ZeroMemory(recvBuffer, 512);
        Result = recv(ClientSocket, recvBuffer, 512, 0);
        if (Result > 0) {
            cout << "Recieved data " << recvBuffer << endl;
            cin >> SendBuffer;
            Result = send(ClientSocket, SendBuffer, (int)strlen(SendBuffer), 0);
//            if (Result == SOCKET_ERROR) {
//                cout << "Failed to send data back" << endl;
//                closesocket(ClientSocket);
//                freeaddrinfo(addrResult);
//                WSACleanup();
//                return 1;
//            }
        } else if (Result == 0) {
            cout << "Connection closing...";
        } else if (Result < 0) {
            cout << "recv failed with error";
            closesocket(ClientSocket);
            freeaddrinfo(addrResult);
            WSACleanup();
            return 1;
        }
    } while (Result > 0);

    Result = shutdown(ClientSocket, SD_SEND);
    if (Result == SOCKET_ERROR) {
        cout << "shutdown client socket failed" << endl;
        closesocket(ClientSocket);
        freeaddrinfo(addrResult);
        WSACleanup();
        return 1;
    }

    closesocket(ClientSocket);
    freeaddrinfo(addrResult);
    WSACleanup();
    return 0;

}