#include "Airline.h"
#include <string>
#include <iostream>
#include <iterator>
#include "Airport.h"
#include <iterator>
using namespace std;


//Solamente tenemos 5 aeronaves por aerolinea
const int NUM_FLIGHTS = 5;

Airline::Airline(string date, string boardingCity_val, string name_val, string shortName_val) 
                : boardingCity{boardingCity_val}, name{name_val}, shortName{shortName_val} 
                {
                //initFlights();
                Flight f(date,"13:30",10000.0,"BOEING144","CDMXtoNY",1000.0,"Salamandra, Ajolote, Juan");
                flights.push_back(f);
                }

vector<Flight> Airline::getFlights() {
    return flights;
}
string Airline::getBoardingCity() {
    return boardingCity;
    };
    string Airline::getShortName() {
        return shortName;
    };
    void Airline::setShortName(string shortName_val) {
        shortName=shortName_val;
    };
    double Airline::getIncomes() {
        currentIncome();
        return incomes;
    };
    void Airline::setIncomes(double incomes_val){
        incomes=incomes_val;
    }

void Airline::printFlights() {
    cout << shortName << ":" << endl;
    for(auto current: flights) {
        if(current.getFromTo()!="") {
            current.info();
        }
    }
}
void Airline::updateAirline() {
    cout << "Cual es el codigo de la aerolinea: " << endl;
    cin >> shortName;
    cout << "Cual es el nombre de la aerolinea: " << endl;
    cin >> name;
}

// void Airline::initFlights() { //no se debería ejecutar
//     for (size_t i = 0; i < NUM_FLIGHTS; i++) {
//         Flight nuevo(date,"00:00",0.0,"AAAA", "",0.0,"f");
//         flights.push_back(nuevo);
//     }
// }

void Airline::scheduleFlight() {
    int counter=0;
    for(int i=0; i<flights.size(); i++) {
        if (flights.size()<=NUM_FLIGHTS) {
            string fecha{}, hour{}, model{}, fromTo{}, crew{};
            double price{}, distance{};
            cout << "Cual es la fecha del vuelo (dd/mm/yyyy): " << endl;
            cin >> fecha;
            cout << "Cual es la hora del vuelo (hh:mm): " << endl;
            cin >> hour;
            cout << "Cual es el modelo de la aeronave: " << endl;
            cin >> model;
            cout << "De dónde a dónde del vuelo: " << endl;
            cin >> fromTo;
            cout << "Cual es el precio del vuelo: " << endl;
            cin >> price;
            cout << "Cual es la distancia del vuelo: " << endl;
            cin >> distance;
            cout << "Cuales son los nombres de la tripulacion (separados por comas): " << endl;
            cin >> crew;

            Flight nuevoVuelo{fecha, hour, price, model, fromTo, distance, crew};
            flights.push_back(nuevoVuelo);
            break;
        }
        if (i==flights.size()-1) {
            cout << "No hay aeronaves disponibles." << endl;
        return;
    }
    }


    //currentIncome();
}

void Airline::currentIncome() {
    double finalIncome{};
    for(auto vuelo : flights) {
        if (vuelo.getAirplaneModel() != "") {
            finalIncome += (vuelo.getPrice() * static_cast<double>(vuelo.getNumberOfPassengers()) + vuelo.getPrice()*static_cast<double>(vuelo.getNumberOfPremiumPassengers()));
        }
    }
    incomes = finalIncome;
    //cout << "El income en este momento es de $" << incomes << endl; 



}
double Airline::closeOperataion() {
        cout << name <<" cierra el día con: ";
        currentIncome();
        cout << incomes<< endl;
        return incomes;
}
