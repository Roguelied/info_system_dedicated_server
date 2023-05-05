#include "Database.h"
#include "Utility.h"

/*======================================================================================================================
 =====================================================================================================================*/
int Database::AmountOfAllUsers;
int Database::AmountOfAllRes;
vector <User> Database::ParsedUserData;
vector <ReservedData> Database::ParsedResData;


void Database::ParseUserData() {
    string Buffer;
    fstream File("../USERS.txt", fstream::in);

    getline(File, Buffer);
    AmountOfAllUsers = Buffer[0] - 48;

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

int Database::FindUser(string Login, string Password) {
    for (auto &User : ParsedUserData) {
        if (User.Login == Login and User.Password == Password) return 1;
        else if (User.Login == Login and User.Password != Password) return -1;
    }
    return 0;
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

int Database::DeleteData(int ResIndex) {
    int Index = 0, IsDeleteSuccessful = 0;
    for (auto &ReservedData : ParsedResData) {
        if (ReservedData.Index == ResIndex) {
            ParsedResData.erase(ParsedResData.begin() + Index);
            IsDeleteSuccessful = 1;
            break;
        }
        Index++;
    }
    Index = 0;
    if (IsDeleteSuccessful) {
        AmountOfAllRes--;
        for (auto &ReservedData : ParsedResData) {
            ReservedData.Index = Index;
            Index++;
        }
        ResDataToFile();
        return 1;
    }
    return 0;

}

void Database::ResDataToFile() {
    fstream RESDATA("../DATA.txt", fstream::out);
    RESDATA << AmountOfAllRes << '\n';
    for (auto &ReservedData : ParsedResData) {
        RESDATA << ReservedData.ID << "    " << ReservedData.DeparturePoint << "    " << ReservedData.DestinationPoint << "    " <<
        ReservedData.SeatType << "    " << ReservedData.PlaceNumber << "    " << ReservedData.Date << "    " << ReservedData.Price << '\n';
    }
    RESDATA.close();
}


void Database::ParseResData() {
    string Buffer;
    fstream File("../DATA.txt", fstream::in);

    getline(File, Buffer);
    AmountOfAllRes = Buffer[0] - 48;

    while (getline(File, Buffer)) {
        stringstream StringStream(Buffer);
        ReservedData ReservedData;

        StringStream >> ReservedData.Price;
        StringStream >> ReservedData.Date;
        StringStream >> ReservedData.PlaceNumber;
        StringStream >> ReservedData.SeatType;
        StringStream >> ReservedData.DestinationPoint;
        StringStream >> ReservedData.DeparturePoint;
        StringStream >> ReservedData.ID;

        ParsedResData.push_back(ReservedData);
    }
    File.close();
    //at this moment u have all parsed data from file USERS.txt in Database::ParsedUserData
}

