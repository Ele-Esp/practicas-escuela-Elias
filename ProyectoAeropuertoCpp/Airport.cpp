#include "Airport.h"
#include "Airline.h"
#include <string>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

const int NUM_AIRLINES=3;
Airport::Airport(int inid, string indate, string incity, string incountry)
                :id{inid}, date{indate}, city{incity}, country{incountry}
            {
            //initAirlines();
            Airline n(date,city,"VivaAerobus","VA");
            airlines.push_back(n);
            //startOperations(indate);
            }


// void Airport::initAirlines() {
//     for (size_t i = 0; i < NUM_AIRLINES; i++) {
//         Airline nuevo(date,city,"","");
//         airlines.push_back(nuevo);
//     }
// }

void Airport::printInfo() {
    cout << date << endl;
    cout << city << endl;
    cout << country << endl;
}
void Airport::printAllFlights() {
    //airlines.sort();
    for (auto i:airlines) {
        if(i.getShortName()!="") {           
            cout<<"Imprimiendo para " << i.getShortName()<<endl; 
            i.printFlights();
        }
        
    }
}



void Airport::startOperations(string inDate) {
    cout<<"Identificador del aeropuerto (int)" << endl;
    cin>>id;
    cout << "Ciudad de operación" << endl;
    cin>>city;
    cout << "País" << endl;
    cin>>country;
    date=inDate;
}


double Airport::closeOperations() {   
    int tot;
    double ingr;
    for(int i=0; i<airlines.size(); i++) {
        ingr+=airlines[i].getIncomes();
        airlines[i].setIncomes(0);
        vector<Flight> vuelos = airlines[i].getFlights();
        for(int j=0; j<vuelos.size(); j++) {
            if(vuelos[j].getDate()==date) {
                tot++;
            }
        }
    }
    cout << "Total de vuelos en el día: "<< tot <<endl;
    cout << "Total de ingresos del día " << ingr << endl;
    return ingr;
    // int totalSum;
    // vector<Airline>::iterator a= airlines.begin();
    // for(int i=0; i<airlines.size();i++) {
    //     totalSum= (*a).getIncomes();
    //     (*a).setIncomes(0);
    //     a=next(a);
    // }
    // cout<<"El ingreso total del aeropuerto es " <<totalSum;
    // return totalSum;
}