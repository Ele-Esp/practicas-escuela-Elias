#include "Passenger.h"
#include <iostream>
using namespace std;

Passenger::Passenger(string name_val, string phone_val)
    : name {name_val}, phone {phone_val} {
        //cout<< "Se llamó al constructor de Passenger con nombre" <<name_val << " y teléfono "<< phone_val;
}

string Passenger::getName() {
    return name;
}

void Passenger::setName(string name_val) {
    name = name_val;
}

string Passenger::getPhone() {
    return phone;
}

void Passenger::setPhone(string phone_val) {
    phone = phone_val;
    cout<< phone_val<<endl;
}