#include "Utility.h"

string IDCreator(int UserNumber) {
    string USERID = "ID";
    string DynamicPart = to_string(UserNumber);

    if (DynamicPart.length() == 1) {
        USERID += "00" + DynamicPart;

    } else if (DynamicPart.length() == 2) {
        USERID += "0" + DynamicPart;

    } else if (DynamicPart.length() == 3) {
        USERID += DynamicPart;
    }

    return USERID;
}

void substr(char* dest, char* source, int from, int length) {
    strncpy(dest, source+from, length);
    dest[length] = 0;
}