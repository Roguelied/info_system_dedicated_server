#include "Utility.h"
#include "Server.h"

/*
 *      Available commands to send:
 *          DEL <IndexIntValue>
 *          FND Login%Password%
 *          REG Login%Password%
 *
 *
 *  План капкан:
 *      Check for admin while found somebody
 *      Input Validation
 *          User Already in Database
 *          Data Already in Database - 2 ways check - reserved for user or not
 *          User 10 length login and pass
 *      Functions for:
 *          Database add sing
 *          Databse check sign for reserved
 *              Check what is reserved
 *          Get all reserved
 *              Find reserved by user
 *          Parse all signs
 *
 *          Database reserve by user
 *
 *
 *
 *
 */

int main() {
    Database::ParseUserData();
    Database::ParseResData();
    Server::Initialize();
    int RecvCommand = Server::Listen();
    int a;
    cin >> a;
    return 0;
}
