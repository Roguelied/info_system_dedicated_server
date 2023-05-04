#include "Server.h"

int Server::DeleteIndex;
ADDRINFO* Server::addrResult = NULL;
SOCKET Server::ClientSocket = INVALID_SOCKET;
SOCKET Server::ListenSocket = INVALID_SOCKET;
char Server::SendBuffer[512];
char Server::recvBuffer[512];
WSADATA Server::wsaData;
ADDRINFO Server::hints;


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

    //Set Client connection to ClientSocket from Server side
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
            cout << "Recieved:" << recvBuffer << endl;
            char Message[64];

            //DELETE CASE----------------------------------------------------------------------------------------------
            if (recvBuffer[0] == 'D' and recvBuffer[1] == 'E' and recvBuffer[2] == 'L'){
                if (isdigit(recvBuffer[4]) and isdigit(recvBuffer[5])) {
                    char str[2];
                    str[0] = recvBuffer[4];
                    str[1] = recvBuffer[5];
                    DeleteIndex = atoi(str);
                } else {
                    DeleteIndex = recvBuffer[4] - 48;
                }
                cout << DeleteIndex << ' ';
                Result = Database::DeleteUser(DeleteIndex);
                if (Result == 1) {
                    cout << "Successfully delete user\n";
                    strcpy(Message, "Successfully delete user\n");
                } else if (Result == 0) {
                    cout << "User not found\n";
                    strcpy(Message, "User not found\n");
                }
            }
            //---------------------------------------------------------------------------------------------------------
            //FIND CASE------------------------------------------------------------------------------------------------
            if (recvBuffer[0] == 'F' and recvBuffer[1] == 'N' and recvBuffer[2] == 'D'){
                char sliced_buf[20];
                substr(sliced_buf, recvBuffer, 4, 20);
                string Credentials(sliced_buf);
                cout << Credentials;
                string Login;
                string Password;
                int i = 0;
                while (Credentials[i] != '%') {
                    Login.push_back(Credentials[i]);
                    i++;
                }
                cout << '\n' << Login << '\n';
                i+=1;
                int c = i;
                i = 0;
                while (Credentials[c+i] != '%') {
                    Password.push_back(Credentials[c+i]);
                    i++;
                }
                cout << Password << '\n';

                Result = Database::FindUser(Login, Password);
                if (Result == 1) {
                    strcpy(Message, "Successfully find user, login accepted\n");
                    cout << Message;
                } else if (Result == -1) {
                    strcpy(Message, "Wrong Password\n");
                    cout << Message;
                } else if (Result ==  0) {
                    strcpy(Message, "User not found\n");
                    cout << Message;
                }
            }
            //---------------------------------------------------------------------------------------------------------
            //REGISTRATION CASE----------------------------------------------------------------------------------------
            if (recvBuffer[0] == 'R' and recvBuffer[1] == 'E' and recvBuffer[2] == 'G'){
                char sliced_buf[20];
                string Login;
                string Password;
                substr(sliced_buf, recvBuffer, 4, 20);
                string Credentials(sliced_buf);
                cout << Credentials;
                int i = 0;
                while (Credentials[i] != '%') {
                    Login.push_back(Credentials[i]); i++;
                }
                cout << '\n' << Login << '\n';
                i+=1; int c = i; i = 0;
                while (Credentials[c+i] != '%') {
                    Password.push_back(Credentials[c+i]); i++;
                }
                cout << Password << '\n';

                Result = Database::FindUser(Login, Password);
                if  (Result == -1 or Result == 1) {
                    strcpy(Message, "This username is already taken                 \n");
                    cout << Message;
                } else if (Result ==  0) {
                    Database::RegUser(Login, Password);
                    strcpy(Message, "Registration successful, now you can sign in\n");
                    cout << Message;
                }
            }
            //---------------------------------------------------------------------------------------------------------

            strcpy(SendBuffer, Message); memset(Message, 0, sizeof(char)*strlen(Message));
            Result = send(ClientSocket, SendBuffer, (int)strlen(SendBuffer), 0);


            if (Result == SOCKET_ERROR) {
                cout << "Failed to send data back" << endl;
                closesocket(ClientSocket);
                freeaddrinfo(addrResult);
                WSACleanup();
                return 1;
            }
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