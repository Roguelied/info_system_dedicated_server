#include "Database.h"

#include <utility>
#include "Utility.h"

/*=============================================USER====================================================================
 =====================================================================================================================*/
int Database::AmountOfAllUsers;
int Database::AmountOfAllReserved;
vector <User> Database::ParsedUserData;
vector <ReservedData> Database::ParsedReservedData;


void Database::ParseUserData() {
    string Buffer;
    fstream File("../USERS.txt", fstream::in);

    getline(File, Buffer);
    AmountOfAllUsers = atoi(Buffer.c_str());

    while (getline(File, Buffer)) {
        stringstream StringStream(Buffer);
        User User;

        StringStream >> User.Index;
        StringStream >> User.Login;
        StringStream >> User.Password;
        StringStream >> User.USERID;
        StringStream >> User.AdminFlag;

        ParsedUserData.push_back(User);
    }
    File.close();
    //at this moment u have all parsed data from file USERS.txt in Database::ParsedUserData
}



void Database::UserDataToFile() {
    fstream USERDATA("../USERS.txt", fstream::out);
    USERDATA << AmountOfAllUsers << '\n';
    for (auto &User : ParsedUserData) {
        USERDATA << User.Index << "    " << User.Login << "    " << User.Password << "    " << User.USERID << "    " \
        << User.AdminFlag << '\n';
    }
    USERDATA.close();
}


void Database::RegUser(string Login, string Password) {
    User NewUser;
    NewUser.Index = AmountOfAllUsers+1;
    NewUser.Login = std::move(Login);
    NewUser.Password = std::move(Password);
    NewUser.USERID = IDCreator(AmountOfAllUsers+1);
    NewUser.AdminFlag = 0;


    ParsedUserData.push_back(NewUser);
    AmountOfAllUsers++;
    UserDataToFile();
}


string Database::FindUser(string Login, string Password) {
    string Buffer;
    for (auto &User : ParsedUserData) {
        if (User.Login == Login and User.Password == Password) {

            Buffer += to_string(User.Index); Buffer += "    ";
            Buffer += User.Login; Buffer += "    ";
            Buffer += User.Password; Buffer += "    ";
            Buffer += User.USERID; Buffer += "    ";
            Buffer += to_string(User.AdminFlag);
            return Buffer;
        }
        else if (User.Login == Login and User.Password != Password) {
            return "WRONGPASS";
        }
    }

    return "NOTFOUND";
}

int Database::DeleteUser(int UserIndex) {
    int Index = 0, IsDeleteSuccessful = 0;
    for (auto &User : ParsedUserData) {
        if (User.Index == UserIndex) {
            ParsedUserData.erase(ParsedUserData.begin() + Index);
            IsDeleteSuccessful = 1;
            break;
        }
        Index++;
    }
    Index = 0;
    if (IsDeleteSuccessful) {
        AmountOfAllUsers--;
        for (auto &User : ParsedUserData) {
            User.Index = Index;
            Index++;
        }
        UserDataToFile();
        return 1;
    }
    return 0;
}

/*=============================================RESERVED DATA===========================================================
 =====================================================================================================================*/


int Database::DeleteData(int DataIndex) {
    int Index = 0, IsDeleteSuccessful = 0;
    for (auto &Data : ParsedReservedData) {
        if (Data.Index == DataIndex) {
            ParsedReservedData.erase(ParsedReservedData.begin() + Index);
            IsDeleteSuccessful = 1;
            break;
        }
        Index++;
    }
    Index = 0;
    if (IsDeleteSuccessful) {
        AmountOfAllReserved--;
        for (auto &Data : ParsedReservedData) {
            Data.Index = Index;
            Index++;
        }
        ReservedDataToFile();
        return 1;
    }
    return 0;
}

void Database::ReservedDataToFile() {
    fstream RESDATA("../DATA.txt", fstream::out);
    RESDATA << AmountOfAllReserved << '\n';
    for (auto &ReservedData : ParsedReservedData) {
        RESDATA << ReservedData.Index << "    " << ReservedData.Type << "    " << ReservedData.Date << "    " <<
                ReservedData.Place << "    " << ReservedData.User << '\n';
    }
    RESDATA.close();
}

void Database::ParseResData() {
    string Buffer;
    fstream File("../DATA.txt", fstream::in);

    getline(File, Buffer);
    AmountOfAllReserved = atoi(Buffer.c_str());

    while (getline(File, Buffer)) {
        stringstream StringStream(Buffer);
        ReservedData Data;

        StringStream >> Data.Index;
        StringStream >> Data.Type;
        StringStream >> Data.Date;
        StringStream >> Data.Place;
        StringStream >> Data.User;

        ParsedReservedData.push_back(Data);
    }
    File.close();
}

string Database::FindReservedData(string Type, string Date, string Place) {
    string Buffer;
    for (auto &Data : ParsedReservedData) {
        if (Data.Type == Type and Data.Date == Date and Data.Place == Place) {

            Buffer += to_string(Data.Index); Buffer += "    ";
            Buffer += Data.Type; Buffer += "    ";
            Buffer += Data.Date; Buffer += "    ";
            Buffer += Data.Place; Buffer += "    ";
            Buffer += Data.User;
            return Buffer;
        }
    }
    //strcpy(OutputStr, "NOTFOUND");
    return "NOTFOUND";
}

void Database::AddNewReservation(string Type, string Date, string Place, string User) {
    ReservedData NewData;

    NewData.Index = AmountOfAllReserved+1;
    NewData.Type = std::move(Type);
    NewData.Date =  std::move(Date);
    NewData.Place =  std::move(Place);
    NewData.User =  std::move(User);


    ParsedReservedData.push_back(NewData);
    AmountOfAllReserved++;
    ReservedDataToFile();
}

string Database::Reserve(string Login, int ReserveIndex) {
    if (ReserveIndex > AmountOfAllReserved) {
        cout << AmountOfAllReserved + 1 << "   " << ReserveIndex + 1 << "  ";
        return "NOTFOUND";
    }

    if (FindUser(Login, "KOCTbILb") != "NOTFOUND") {
        if (ParsedReservedData[ReserveIndex].User == Login) {
            return "ALREADY RESERVED";
        }
        if (ParsedReservedData[ReserveIndex].User != "NONE" and ParsedReservedData[ReserveIndex].User != Login) {
            return "RESERVED BY ANOTHER USER";
        }
        ParsedReservedData[ReserveIndex].User = Login;
        ReservedDataToFile();
        return Login + " SUCCESSFULLY RESERVED " + to_string(ReserveIndex) + " SLOT";
    }
    cout << 321;
    return "NOTFOUND";
}
