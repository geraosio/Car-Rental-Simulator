#include <iostream>
#include <string>
using namespace std;

class Location {
private:
    string sCountry;
    string sCity;
    string sPlace;
public:
    // Constructor
    Location();
    Location(string sCountry, string sCity, string sPlace);

    // Copy Constructor
    Location(const Location &other);

    // Overload operator
    Location &operator=(const Location &rhs);
    friend ostream &operator<<(ostream &output, const Location &loc);
};

Location::Location()
{
    this->sCountry = "";
    this->sCity = "";
    this->sPlace = "";
}

Location::Location(string sCountry, string sCity, string sPlace)
{
    this->sCountry = sCountry;
    this->sCity = sCity;
    this->sPlace = sPlace;
}

Location::Location(const Location &other)
{
    sCountry = other.sCountry;
    sCity = other.sCity;
    sPlace = other.sPlace;
}

Location &Location::operator=(const Location &rhs)
{
    if (this != &rhs) {
        sCountry = rhs.sCountry;
        sCity = rhs.sCity;
        sPlace = rhs.sPlace;
    }

    return *this;
}

ostream &operator<<(ostream &out, const Location &loc)
{
    out << loc.sPlace << " (" << loc.sCity << ", " << loc.sCountry << ")";
    return out;
}
