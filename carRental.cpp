/***
Car Rental

URL: http://www.rentadeautosenmonterrey.com
***/
#include "Reservation.h"

#include <iostream>
#include <string>
#include <ctime>    // struct tm
#include <cstdlib>  // system()
#include <fstream>  // ofstream
using namespace std;

void startupGreeting()
{
    cout << "\t*****************************\n";
    cout << "\t****      BIENVENIDO     ****\n";
    cout << "\t****           A         ****\n";
    cout << "\t****  AMERICA CAR RENTAL ****\n";
    cout << "\t*****************************\n";
    cout << "\n";
}

// Prints error message if the input number is out of the range of numbers
void printErrorMessageIfOutOfRange(int iNum, int iLowerBound, int iUpperBound)
{
    if (iNum < iLowerBound || iNum > iUpperBound) {
        cout << "**********\n";
        cout << "ERROR: Selecciono un numero que no esta en la lista.\n";
        cout << "**********\n";
    }
}

// Validate that the pickup date is after the current date.
bool isValidReservationDate(struct tm *stmTime, int iYear, int iMonth, int iDay, int iHour, int iMinute)
{
    // Manage inputted date with struct tm
    struct tm tmInputDate = {0};
    int tempY = iYear, tempM = iMonth;
    tmInputDate.tm_year = tempY - 1900;
    tmInputDate.tm_mon = tempM - 1;
    tmInputDate.tm_mday = iDay;
    tmInputDate.tm_hour = iHour;
    tmInputDate.tm_min = iMinute;

    double dSec = difftime(mktime(&tmInputDate), mktime(stmTime));

    if (dSec > 0) {
        return true;
    }

    return false;
}

int main()
{
    Reservation::extractCarInformationFromFile("cars.txt");
    Reservation::extractLocationInformationFromFile("locations.txt");

    startupGreeting();

    // Retrieve the systems's date and time.
    time_t now = time(0);
    tm *tmNow = localtime(&now);

    Reservation res1;
    int iPickLocIndex, iReturnLocIndex;
    int iYear, iMonth, iDay, iHour, iMinute;
    int iCarIndex;
    int iModifyIndex;

    /***
    CHOOSE PICKUP INFORMATION
    ***/

    // Selection of Pickup Location
    do {
        cout << "Teclee el numero, de la lista de abajo, del lugar donde desee RECOGER el carro\n";
        Reservation::printAvailableLocations();
        cin >> iPickLocIndex;

        system("clear"); // clear screen

        printErrorMessageIfOutOfRange(iPickLocIndex, 0, 19);
    } while(iPickLocIndex < 0 || iPickLocIndex > 19);
    res1.setPickupLocation(Reservation::getLocation(iPickLocIndex));

    // Selection of Pickup Time
    do {
        cout << "Teclee la fecha cuando desee RECOGER el carro con el siguiente formato: AAAA MM DD.\nPor ejemplo para Mayo 23 2017, teclear 2017 05 23.\n";
        cin >> iYear >> iMonth >> iDay;
        cout << endl;

        cout << "Teclee la hora a la que desee RECOGER el carro con el siguiente formato: HH MM.\nPor ejemplo para las 9:10 pm, teclear 21 10.\n";
        cin >> iHour >> iMinute;

        system("clear"); // clear screen

        if (!isValidReservationDate(tmNow, iYear, iMonth, iDay, iHour, iMinute)) {
            cout << "**********\n";
            cout << "ERROR: Selecciono una fecha y/o hora que ya paso.\n";
            cout << "**********\n";
        }
    } while(!isValidReservationDate(tmNow, iYear, iMonth, iDay, iHour, iMinute));
    res1.setPickupTime(iYear, iMonth, iDay, iHour, iMinute);


    /***
    CHOOSE RETURN INFORMATION
    ***/

    // Selection of Return Location
    do {
        cout << "Teclee el numero, de la lista de abajo, del lugar donde desee DEVOLVER el carro.\n";
        Reservation::printAvailableLocations();
        cin >> iReturnLocIndex;

        system("clear"); // clear screen

        printErrorMessageIfOutOfRange(iReturnLocIndex, 0, 19);
    } while(iReturnLocIndex < 0 || iReturnLocIndex > 19);
    res1.setReturnLocation(Reservation::getLocation(iReturnLocIndex));

    struct tm tmTemp = res1.getPickupStructTm();
    struct tm *tmPickTime = &tmTemp;

    // Selection of Return Time
    do {
        cout << "Teclee la fecha cuando desee DEVOLVER el carro con el siguiente formato: AAAA MM DD.\nPor ejemplo para Mayo 23 2017, teclear 2017 05 23.\n";
        cin >> iYear >> iMonth >> iDay;
        cout << endl;

        cout << "Teclee la hora a la que desee DEVOLVER el carro con el siguiente formato: HH MM.\nPor ejemplo para las 9:10 pm, teclear 21 10.\n";
        cin >> iHour >> iMinute;

        system("clear"); // clear screen

        if (!isValidReservationDate(tmPickTime, iYear, iMonth, iDay, iHour, iMinute)) {
            cout << "**********\n";
            cout << "ERROR: Selecciono una fecha anterior a la fecha que escogio para RECOGER el carro.\n";
            cout << "**********\n";
        }
    } while(!isValidReservationDate(tmPickTime, iYear, iMonth, iDay, iHour, iMinute));
    res1.setReturnTime(iYear, iMonth, iDay, iHour, iMinute);

    /***
    SELECT CAR
    ***/

    do {
        cout << "Teclee el numero, de la lista de abajo, del carro que desea escoger.\n";
        Reservation::printAvailableCars();
        cin >> iCarIndex;

        system("clear"); // clear screen

        printErrorMessageIfOutOfRange(iCarIndex, 0, 9);
    } while(iCarIndex < 0 || iCarIndex > 9);
    res1.setCar(Reservation::getGlobalCar(iCarIndex));

    /***
    SUMMARY OF RESERVATION
    ***/

    res1.printSummary(cout, 1);

    int iSummaryDec;

    do {
        cout << "Desea guardar la informacion de su reservacion?\n";
        cout << "Teclee 0 si desea guardar la informacion.\n";
        cout << "Teclee 1 si NO desea guardar la informacion.\n";
        cin >> iSummaryDec;

        system("clear"); // clear screen

        printErrorMessageIfOutOfRange(iSummaryDec, 0, 1);
    } while(iSummaryDec != 0 && iSummaryDec != 1);

    if (iSummaryDec == 0) {
        ofstream outFile;
        outFile.open("ReservationSummary.txt");
        cout << "Guardando en archivo...\n";

        res1.printSummary(outFile, 0);

        outFile.close();

        cout << "Se ha guardado su informacion exitosamente.\n";
    }

    return 0;
}
