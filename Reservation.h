#ifndef RESERVATION_H
#define RESERVATION_H

#include "Location.h"
#include "Car.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;

class Reservation {
private:
    static vector<Location> vecLoc;
    static vector<Car> vecCars;

    Location pickupLocation;
    struct tm pickupTime;

    Location returnLocation;
    struct tm returnTime;

    Car car;
public:
    // CONSTRUCTOR
    Reservation();

    // LOCATIONS
    static void extractLocationInformationFromFile(string sFileName);
    static void printAvailableLocations();
    static Location getLocation(int iIndex);

    void setPickupLocation(Location loc);
    void setReturnLocation(Location loc);
    Location getPickupLocation();
    Location getReturnLocation();

    // CARS
    static void extractCarInformationFromFile(string sFileName);
    static void printAvailableCars();
    static Car getGlobalCar(int iIndex);

    void setCar(Car car);
    Car getCar();

    // DATE AND TIME
    string getPickupTime();
    string getReturnTime();
    struct tm getPickupStructTm();
    struct tm getReturnStructTm();
    void setPickupTime(int iYear, int iMonth, int iDay, int iHour, int iMin);
    void setReturnTime(int iYear, int iMonth, int iDay, int iHour, int iMin);
    void printTotalRentalTime();

    // PRICE
    int getTotalPrice();

    // SUMMARY
    void printSummary(ostream &out, int iDecision);
};

vector<Location> Reservation::vecLoc;
vector<Car> Reservation::vecCars;

/***
"Reservation.h" implementation
***/

/***
CONSTRUCTOR
***/

Reservation::Reservation()
{
    struct tm tempPickTime = {0};
    struct tm tempRetTime = {0};

    this->pickupTime = tempPickTime;
    this->returnTime = tempRetTime;
}


/***
LOCATIONS
***/

// Extract the locations information from file
void Reservation::extractLocationInformationFromFile(string sFileName)
{
    string sLine;
    string sCountry, sCity, sPlace;
    ifstream pickLocFile;

    string sPathOfFile = "txt_files/" + sFileName;

    pickLocFile.open(sPathOfFile);

    while(!pickLocFile.eof()) {
        getline(pickLocFile, sLine);

        if (!sLine.empty()) {
            if (sLine[0] == '*') {
                sCountry = sLine.substr(4, 3); // ONLY WORKS IF NAME OF COUNTRY HAS 3 LETTERS
            } else if (sLine[0] == '-') {
                sCity = sLine.substr(1, sLine.length());
            } else {
                sPlace = sLine;
                Location loc (sCountry, sCity, sPlace);
                vecLoc.push_back(loc);
            }
        }
    }

    pickLocFile.close();
}

void Reservation::printAvailableLocations()
{
    int iVecSize = vecLoc.size();

    for (int i = 0; i < iVecSize; i++) {
        cout << i << "\t" << vecLoc[i] << endl;
    }
}

Location Reservation::getLocation(int iIndex)
{
    return vecLoc[iIndex];
}

void Reservation::setPickupLocation(Location loc)
{
    this->pickupLocation = loc;
}

void Reservation::setReturnLocation(Location loc)
{
    this->returnLocation = loc;
}

Location Reservation::getPickupLocation()
{
    return this->pickupLocation;
}

Location Reservation::getReturnLocation()
{
    return this->returnLocation;
}

/***
CARS
***/

// Extract the cars information from file
void Reservation::extractCarInformationFromFile(string sFileName)
{
    string sLine;
    ifstream vehicleFile;

    string sPathOfFile = "txt_files/" + sFileName;

    vehicleFile.open(sPathOfFile);

    while (!vehicleFile.eof()) {
        getline(vehicleFile, sLine);

        if (sLine != "") {
            Car newCar (sLine);
            vecCars.push_back(newCar);
        }
    }

    vehicleFile.close();
}

void Reservation::printAvailableCars()
{
    int iVecSize = vecCars.size();

    for (int i = 0; i < iVecSize; i++) {
        cout << i << "\t" << vecCars[i] << endl;
    }
}

Car Reservation::getGlobalCar(int iIndex)
{
    return vecCars[iIndex];
}

void Reservation::setCar(Car car)
{
    this->car = car;
}

Car Reservation::getCar()
{
    return this->car;
}

/***
DATE AND TIME
***/

string Reservation::getPickupTime()
{
    char cTempPick [20];
    strftime(cTempPick, 20, "%Y-%m-%d %H:%M", &this->pickupTime);
    return cTempPick;
}

string Reservation::getReturnTime()
{
    char cTempRet [20];
    strftime(cTempRet, 20, "%Y-%m-%d %H:%M", &this->returnTime);
    return cTempRet;
}

struct tm Reservation::getPickupStructTm()
{
    return this->pickupTime;
}

struct tm Reservation::getReturnStructTm()
{
    return this->returnTime;
}

void Reservation::setPickupTime(int iYear, int iMonth, int iDay, int iHour, int iMin)
{
    // Make copy of year and month for further modification to input it in "struct tm"
    int tempY = iYear, tempM = iMonth;

    this->pickupTime.tm_year = tempY - 1900;
    this->pickupTime.tm_mon = tempM - 1;
    this->pickupTime.tm_mday = iDay;
    this->pickupTime.tm_hour = iHour;
    this->pickupTime.tm_min = iMin;
}

void Reservation::setReturnTime(int iYear, int iMonth, int iDay, int iHour, int iMin)
{
    // Make copy of year and month for further modification to input it in "struct tm"
    int tempY = iYear, tempM = iMonth;

    this->returnTime.tm_year = tempY - 1900;
    this->returnTime.tm_mon = tempM - 1;
    this->returnTime.tm_mday = iDay;
    this->returnTime.tm_hour = iHour;
    this->returnTime.tm_min = iMin;
}

void Reservation::printTotalRentalTime()
{
    double dSec = difftime(mktime(&this->returnTime), mktime(&this->pickupTime));

    time_t seconds(dSec);
    struct tm *timeElapsed = gmtime(&seconds);

    cout << timeElapsed->tm_yday << " dias, ";
    cout << timeElapsed->tm_hour << " horas y ";
    cout << timeElapsed->tm_min << " minutos";
}

/***
PRICE
***/

int Reservation::getTotalPrice()
{
    int iPricePerDay = this->car.getPrice();
    int iTotalPrice;

    // Calculate the difference of time.
    double dSec = difftime(mktime(&this->returnTime), mktime(&this->pickupTime));

    // Convert time to seconds and use struct tm to store and represent.
    time_t seconds(dSec);
    struct tm *timeElapsed = gmtime(&seconds);

    iTotalPrice = timeElapsed->tm_yday * iPricePerDay;

    // If it surpasses the hour of use add a day worth of use in the price.
    if (timeElapsed->tm_hour >= 1) {
        iTotalPrice += iPricePerDay;
    }

    return iTotalPrice;
}

/***
SUMMARY
***/

void Reservation::printSummary(ostream &out, int iDecision)
{
    out << "\t*RESUMEN DE SU RESERVACION*\n";

    out << "\n- Lugar que escogio para RECOGER el carro:\n";
    out << this->getPickupLocation() << endl;
    out << "\n- Tiempo que escogio para RECOGER el carro:\n";
    out << this->getPickupTime() << endl;

    out << "\n- Lugar que escogio para DEVOLVER el carro:\n";
    out << this->getReturnLocation() << endl;
    out << "\n- Tiempo que escogio para DEVOLVER el carro:\n";
    out << this->getReturnTime() << endl;

    out << "\n- Carro seleccionado:\n";
    out << this->getCar() << endl;

    out << "\n- Tiempo total de la renta:\n";
    if (iDecision == 1) {
        this->printTotalRentalTime();
    }

    out << "\n\n\t***Total a pagar***\n";
    out << "\t    $" << this->getTotalPrice() << ".00 MXN\n\n";
}

#endif
