/*****
TEST: <ctime>

PURPOSE: Manage dates and times of the reservations in "Reservation.h"

TODO:
-x- How to input date and time from int
-x- Formats to output date and time
-x- Calculate the car reservation's total time
*****/
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

int main()
{
    // current date/time based on current system
    time_t now = time(0);
    tm *dt = localtime(&now);

    // current date & time converted to arr of chars.
    char cArrTemp [17];
    strftime(cArrTemp, 17, "%Y-%m-%d %H:%M", dt);
    cout << "Current Time: \t" << cArrTemp << endl;

    // input new date and time
    struct tm pickTime = {0};
    pickTime.tm_year = 2017 - 1900;
    pickTime.tm_mon = 4 - 1;
    pickTime.tm_mday = 20;
    pickTime.tm_hour = 14;
    pickTime.tm_min = 30;
    pickTime.tm_sec = 20;

    struct tm returnTime = {0};
    returnTime.tm_year = 2017 - 1900;
    returnTime.tm_mon = 4 - 1;
    returnTime.tm_mday = 25;
    returnTime.tm_hour = 16;
    returnTime.tm_min = 26;
    returnTime.tm_sec = 43;

    // Covert struct tm to string with format "%Y-%m-%d %H:%M"
    char tempCharArr [20];
    strftime(tempCharArr, 20, "%Y-%m-%d %H:%M", &pickTime);
    cout << "Pickup Time: \t" << tempCharArr << endl;

    // Covert struct tm to string with format "%Y-%m-%d %H:%M"
    char tempCharArr2 [20];
    strftime(tempCharArr2, 20, "%Y-%m-%d %H:%M", &returnTime);
    cout << "Return Time: \t" << tempCharArr2 << endl;

    // Testing assignment between struct tm's
    struct tm assignTime = pickTime;
    char tempCharArr3 [20];
    strftime(tempCharArr3, 20, "%Y-%m-%d %H:%M", &assignTime);
    cout << "Assign Time: \t" << tempCharArr3 << endl;

    // Total rental time (return - pickup)
    double sec = difftime(mktime(&returnTime), mktime(&pickTime));

    // Seconds to struct tm
    // use gmtime for difference of time
    time_t seconds(sec);
    struct tm *timeElap = gmtime(&seconds);

    cout << sec << " seconds =\n";
    cout << "\t\t\t" << timeElap->tm_yday << " days\n";
    cout << "\t\t\t" << timeElap->tm_hour << " hours\n";
    cout << "\t\t\t" << timeElap->tm_min << " mins\n";
    cout << "\t\t\t" << timeElap->tm_sec << " secs\n";

    return 0;
}
