#include <iostream>
#include <string>
using namespace std;

void printTo(ostream& out) {
    out << "\t*RESUMEN DE SU RESERVACION*\n";

    out << "\n- Lugar que escogio para RECOGER el carro:\n";
    out << "this->getPickupLocation()" << endl;
    out << "\n- Tiempo que escogio para RECOGER el carro:\n";
    out << "this->getPickupTime()" << endl;

    out << "\n- Lugar que escogio para DEVOLVER el carro:\n";
    out << "this->getReturnLocation()" << endl;
    out << "\n- Tiempo que escogio para DEVOLVER el carro:\n";
    out << "this->getReturnTime()" << endl;

    out << "\n- Carro seleccionado:\n";
    out << "this->getCar()" << endl;

    out << "\n- Tiempo total de la reservacion:\n";
    out << "10 dias, 2 horas y 5 minutos";

    out << "\n\n\t***Total a pagar***\n";
    out << "\t   $12123.00 MXN\n";
}

int main() {

    printTo(cout);

    return 0;
}
