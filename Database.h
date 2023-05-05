#ifndef INFO_SYSTEM_DEDICATED_SERVER_DATABASE_H
#define INFO_SYSTEM_DEDICATED_SERVER_DATABASE_H
#include "Utility.h"

// Изменяйте так, как вам нужно
struct User {
    int Index;
    string Login;
    string Password;
    string USERID;
    int AdminFlag;
} typedef User;


// Изменяйте так, как вам нужно
struct ReservedData {
    int Index;
    string Type;
    string Date;
    string Place;
    string User;
} typedef ReservedData;


class Database {
private:


public:
    static int AmountOfAllUsers;
    static int AmountOfAllReserved;
    static vector <User> ParsedUserData;
    static vector <ReservedData> ParsedReservedData;
    void AddUserFromString(string Buffer);


    static void ParseUserData();

    static void UserDataToFile();


    //аня
    // функция ДОПИСЫВАЕТ в USERS.txt логин, пароль и имя, генерирует айди и прописывает админфлаг 0
    static void RegUser(string Login, string Password);
    // функция ИЩЕТ внутри USERS.txt переданные логин и пароли, и если находит вовзращает 1, иначе 0
    static string FindUser(string Login, string Password);
    // вася ваза вазон зонд завал зов ебем азов
    // Перегрузки удаления информации из базы - удаление по индексу и удаление по Структуре
    static int DeleteUser(int UserIndex);

    static void ParseResData();
    static void ReservedDataToFile();
    static int DeleteData(int DataIndex);
    static string FindReservedData(string Type, string Date, string Place);
    static void AddNewReservation(string Type, string Date, string Place, string User);


    static string Reserve(string Login, int ReserveIndex);
};


#endif //INFO_SYSTEM_DEDICATED_SERVER_DATABASE_H
