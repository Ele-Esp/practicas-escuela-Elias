#include "Flight.h"
#include <sstream>
#include <iostream>
#include <string>
#include "Passenger.h"

using namespace std;

Flight::Flight(
    string date_val, 
    string hour_val,
    double price_val,
    string model_val,
    string fromTo_val,
    double distance_val,
    string crew_val
) 
    : date{date_val}, 
    hour {hour_val}, 
    price{price_val}, 
    airplaneModel{model_val}, 
    fromTo {fromTo_val}, 
    distance{distance_val} {
    
    string crewMember;
    stringstream input_stringstream(crew_val);
    while (getline(input_stringstream, crewMember, ',')) {
        crew.push_back(crewMember);
    }
    initPassengers();
    initPremiumPassengers();
    calculateFuel();
    Passenger p("PersonaPrueba","555555");
    passengers[0][0]=p;
}

void Flight::info(){
    cout << "Fecha: "<< date << endl;
    cout << "Hora de salida: "<<hour<< endl;
    cout << "Precio del boleto: "<<price<< endl;
    cout << "Modelo del avión: : "<<airplaneModel << endl;
    cout << "Desde/Hacia: "<<fromTo<< endl;
    cout << "Distancia: "<<distance<< endl;
    calculateFuel();
    cout << "Combustible requerido: "<<fuel<< endl;
    printPassengers();
}

void Flight::printPassengers() {
    for(int i=0; i<20; i++) {
        for(int j=0;j<4; j++) {
            if (passengers[i][j].getName()!="default") {
            cout<< passengers[i][j].getName() << " está en el asiento "<< i+1 <<" "<< j+1<<  " con teléfono "<< passengers[i][j].getPhone()<<endl;   
            }
        }

    }
    for(int i=0; i<10; i++) {
        for(int j=0;j<4; j++) {
            if (premiumPassengers[i][j].getName()!="default") {
            cout<< premiumPassengers[i][j].getName() << " está en el asiento premium "<< i+1 <<" "<< j+1 << " con teléfono "<< premiumPassengers[i][j].getPhone()<<endl;   
            }
        }

    }
}
string Flight::getDate() {
    return date;
}

void Flight::setDate(string d) {
    date = d;
}

string Flight::getHour() {
    return hour;
}
void Flight::setHour(string h) {
    hour = h;
}

double Flight::getPrice() {
    return price;
}

void Flight::setPrice(double p) {
    price = p;
}

string Flight::getAirplaneModel() {
    return airplaneModel;
}

void Flight::setAirplaneModel(string am) {
    airplaneModel = am;
}

string Flight::getFromTo() {
    return fromTo;
}

void Flight::setFromTo(string ft) {
    fromTo = ft;
}

double Flight::getDistance() {
    return distance;
}

void Flight::setDistance(double d) {
    distance = d;
}

string Flight::getCrew() {
    string a;
    for (size_t i = 0; i < crew.size(); i++)
        a += crew.at(i) + ",";
    string c = a.substr(0, a.size() - 1);
    return c;
}

void Flight::setCrew(string c) {
    crew.clear();
    string crewMember;
    stringstream input_stringstream(c);
    while (getline(input_stringstream, crewMember, ',')) {
        crew.push_back(crewMember);
    }
}

double Flight::getFuel() {
    return fuel;
}

void Flight::setFuel(double f) {
    fuel = f;
}

void Flight::initPassengers() {
    for (int i = 0; i < 20; i++) {
        for(int j=0; j<4; j++) {
            //cout << i << " " <<j<<"\n";
            Passenger nuevo;
            passengers[i][j]=nuevo;
        }

    }
}
void Flight::initPremiumPassengers() {
    for (int i = 0; i < 10; i++) {
        for(int j=0; j<4; j++) {
            //cout << i << " " <<j<<"\n";
            Passenger nuevo;
            premiumPassengers[i][j]=nuevo;
        }

    }
}
void Flight::calculateFuel() {
    //1200l por cada 100km
    double fuelLitros = (distance * 1200) / 100;
    fuel = fuelLitros / 4.546;
    //cout << "El combustible requerido para viajar " << fromTo << " es de " << fuel << " galones." << endl;
}

void Flight::reservaAsiento() {
    int fila{}, asiento{};
    cout << "Cual fila quieres reservar (1-20): " << endl;
    cin >> fila;
    if (fila < 1 || fila > 20) {
        cout << "La fila " << fila << " no esta disponible." << endl;
        return;
    }
    cout << "Cual asiento quieres reservar (1-4): " << endl;
    cin >> asiento;
    if (asiento < 1 || asiento > 4) {
        cout << "El asiento " << asiento << " no esta disponible." << endl;
        return;
    }
    string nombre="default", telefono="default";

    if (passengers[fila-1][asiento-1].getName()== "default") {
        cout << "Asiento disponible" << endl;
        cout << "Cual es su nombre: " << endl;
        cin >> nombre;
        //cout<< nombre;
        cout <<nombre << ", Cual es su telefono: " << endl;
        cin >> telefono;
        //cout<< telefono;
        passengers[fila-1][asiento-1].setName(nombre);
        passengers[fila-1][asiento-1].setPhone(telefono);
        
    } else {
        cout << "El asiento ya está reservado" << endl;
    }
}
void Flight::reservaAsientoPremium() {
    int fila{}, asiento{};
    cout << "Cual fila premium quieres reservar (1-10): " << endl;
    cin >> fila;
    if (fila < 1 || fila > 10) {
        cout << "La fila " << fila << " no esta disponible." << endl;
        return;
    }
    cout << "Cual asiento quieres reservar (1-4): " << endl;
    cin >> asiento;
    if (asiento < 1 || asiento > 4) {
        cout << "El asiento " << asiento << " no esta disponible." << endl;
        return;
    }
    string nombre, telefono;
    if (premiumPassengers[fila-1][asiento-1].getName()=="default") {
        cout << "Asiento disponible" << endl;
        cout << "Cual es su nombre: " << endl;
        cin >> nombre;
        cout << nombre<< " Cual es su telefono: " << endl;
        cin >> telefono;
        premiumPassengers[fila-1][asiento-1].setName(nombre);
        premiumPassengers[fila-1][asiento-1].setPhone(telefono);
    } else {
        cout << "El asiento ya está reservado" << endl;
    }
}

int Flight::getNumberOfPassengers() {
    int result{};
    for (int i=0;i<20;i++) {
        for(int j=0; j<4; j++) {
            if(passengers[i][j].getName()!="default") {
                result++;
            }
        }
    }
    
    return result;
}

int Flight::getNumberOfPremiumPassengers() {
    int result{};
    for (int i=0;i<10;i++) {
        for(int j=0; j<4; j++) {
            if(premiumPassengers[i][j].getName()!="default") {
                result++;
            }
        }
    }
   
    return result;
}