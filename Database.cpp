#include "Database.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

/*======================================================================================================================
 =====================================================================================================================*/
void Database::RegUser(string Login, string Password) {

}

int Database::FindUser(string Login, string Password) {

}

void Database::DeleteData(vector<ReservedData> db, int DataIndex) {
    db.erase(db.begin() + DataIndex);
    std::copy(db.begin(), db.end(),ostream_iterator<ReservedData>(std::cout, " "));
}

void Database::DeleteData(ReservedData ReservedData) {

}

void Database::DeleteUser(int UserIndex) {

}

void Database::DeleteUser(User User) {

}

void Database::AddData(vector<ReservedData> (&db)) {
    ReservedData reserved_data;
    cout << "Введите ID" << endl; cin >> reserved_data.ID;
    cout << "Введите точку отправки" << endl; cin >> reserved_data.DeparturePoint;
    cout << "Введите точки назначения" << endl; cin >> reserved_data.DestinationPoint;
    cout << "Введите тип вагона" << endl; cin >> reserved_data.SeatType;
    cout << "Введите ваше место" << endl; cin >> reserved_data.PlaceNumber;
    cout << "Введите дату" << endl; cin >> reserved_data.Date;
    cout << "Введите цену" << endl; cin >> reserved_data.Price;
    db.push_back(reserved_data);

}

void Database::AddUser(User User) {

}

void Database::ReadData(vector<ReservedData> (&db), string fileName) { // считывать по одному // закидываем элементы в массив

    fstream reading(fileName, fstream::in);
    ReservedData reserved_data;
    reading >> reserved_data.ID >> reserved_data.DeparturePoint >> reserved_data.DestinationPoint
        >> reserved_data.SeatType >> reserved_data.PlaceNumber >> reserved_data.Date >> reserved_data.Price;
    db.push_back(reserved_data);

    reading.close();
}