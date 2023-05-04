#ifndef INFO_SYSTEM_DEDICATED_SERVER_UTILITY_H
#define INFO_SYSTEM_DEDICATED_SERVER_UTILITY_H

#include <chrono>
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <string>
#include <vector>
#include <cstdio>
#include <thread>
#include <functional>
#include <fstream>
#include <iomanip>
#include <bits/stdc++.h>

#define DELETE_COMMAND 10

using namespace std;


string IDCreator(int UserNumber);
void substr(char* dest, char* source, int from, int length);


#endif //INFO_SYSTEM_DEDICATED_SERVER_UTILITY_H
