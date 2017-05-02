#include <iostream>
#include <string>
using namespace std;

class Car {
private:
    string sType;
    string sTransmission;
    string sModel;
    int iPrice;
public:
    //Constructors
    Car();
    Car(string data);

    // Getter
    int getPrice();

    // Copy Constructor
    Car(const Car &other);

    // Overload operator
    Car &operator=(const Car &rhs);
    friend ostream &operator<<(ostream &out, const Car &c1);
};

Car::Car()
{
    sType = "";
    sTransmission = "";
    sModel = "";
    iPrice = 0;
}

Car::Car(string data)
{
    int iDataLength = data.length(); // Number of chars in data

    // Extract the car's Vehicle
    int iCommaIndex = data.find(',');
    this->sType = data.substr(0, iCommaIndex);

    // Extract the car's sTransmission sType
    int iLineIndex = data.find('-');
    this->sTransmission = data.substr(iCommaIndex + 2, iLineIndex - iCommaIndex - 3);

    // Extract the car's sModel
    int iPriceIndex = data.find('=');
    this->sModel = data.substr(iLineIndex + 2, iPriceIndex - iLineIndex - 3);

    // Extract the car's rental price per day
    this->iPrice = stoi(data.substr(iPriceIndex + 2, iDataLength - iPriceIndex));
}

int Car::getPrice()
{
    return this->iPrice;
}

Car::Car(const Car &other)
{
    sType = other.sType;
    sTransmission = other.sTransmission;
    sModel = other.sModel;
    iPrice = other.iPrice;
}

Car &Car::operator=(const Car &rhs)
{
    if (this != &rhs) {
        sType = rhs.sType;
        sTransmission = rhs.sTransmission;
        sModel = rhs.sModel;
        iPrice = rhs.iPrice;
    }
    return *this;
}

ostream &operator<<(ostream &out, const Car &c1)
{
    out << c1.sType << ", " << c1.sTransmission << " - " << c1.sModel << " - $" << c1.iPrice << ".00 / dia";
    return out;
}
