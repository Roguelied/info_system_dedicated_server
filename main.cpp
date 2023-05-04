#include "Utility.h"
#include "Server.h"


int main() {
    Server::Initialize();
    Database::ParseUserData();

    int RecvCommand = Server::Listen();



//    for (auto i : Database::ParsedUserData) {
//        cout << i.Index << i.Login << i.Password << i.USERID << i.AdminFlag <<'\n';
//
//    }

    int a;
    cin >> a;

    return 0;
}
