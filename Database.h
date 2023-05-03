#ifndef INFO_SYSTEM_DEDICATED_SERVER_DATABASE_H
#define INFO_SYSTEM_DEDICATED_SERVER_DATABASE_H
#include "Utility.h"


// Изменяйте так, как вам нужно
struct User {
    string Login;
    string Password;
    string Surname, Name, Patronymic;
    string ID;
    int AdminFlag;
} typedef User;


// Изменяйте так, как вам нужно
struct ReservedData {
    string SeatType, PlaceNumber, ID, DeparturePoint, DestinationPoint;
    int Price;
    DATE Date;
} typedef ReservedData;


class Database {
private:
    User user;
    ReservedData reserved_data;

public:
    int n;
    vector<ReservedData> db;
    int size;
    //аня
    //функция ДОПИСЫВАЕТ в USERS.txt логин, пароль и имя, генерирует айди и прописывает админфлаг 0
    static void RegUser(string Login, string Password);

    //функция ИЩЕТ внутри USERS.txt переданные логин и пароли, и если находит вовзращает 1, иначе 0
    static int FindUser(string Login, string Password);


    //вася ваза вазон зонд завал зов ебем азов
    // Перегрузки удаления информации из базы - удаление по индексу и удаление по Структуре
    static void DeleteData(vector<ReservedData> db, int DataIndex);
    static void DeleteData(ReservedData ReservedData);
    static void DeleteUser(int UserIndex);
    static void DeleteUser(User User);

    //короче я заебался писать
    static void AddData(vector<ReservedData> (&db));
    static void AddUser(User User);
    static void ReadData(vector<ReservedData> (&db), string fileName);

    //еще должна быть сортировка по структуре, редактирование и быстрый поиск, ну ты помнишь да короче
};


#endif //INFO_SYSTEM_DEDICATED_SERVER_DATABASE_H
