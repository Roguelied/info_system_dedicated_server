#include "Database.h"


/*======================================================================================================================
 =====================================================================================================================*/
void Database::RegUser(string Login, string Password) {

}

int Database::FindUser(string Login, string Password) {

}

void Database::DeleteData(int DataIndex) {

}

void Database::DeleteData(ReservedData ReservedData) {

}

void Database::DeleteUser(int UserIndex) {

}

void Database::DeleteUser(User User) {

}

void Database::AddData(ReservedData ReservedData) {

}

void Database::AddUser(User User) {

}

void Database::ReadData(Database* (&d), string fileName, int n) { // считывать по одному // закидываем элементы в массив
    fstream reading(fileName, fstream::in);
    ReservedData reservedData;
    reading >> reservedData.ID >> reservedData.DeparturePoint >> reservedData.DestinationPoint
        >> reservedData.SeatType >> reservedData.PlaceNumber >> reservedData.Date >> reservedData.Price;
    d[n] = reservedData;

    reading.close();
}