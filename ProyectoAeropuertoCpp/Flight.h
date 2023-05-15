#pragma once
#ifndef _FLIGHT_H_
#define _FLIGHT_H_
#include <string>
#include <vector>
#include "Passenger.h"

class Flight {
    private:
        std::string date;
        std::string hour;
        double price;
        std::string airplaneModel;
        std::string fromTo;
        double distance;
        std::vector<std::string> crew;
        double fuel;
        Passenger passengers[20][4]; //Considerar que tengo vuelos de 30 filas, 4 asientos por fila
        Passenger premiumPassengers[10][4];
        void calculateFuel();
        void initPassengers();
        void initPremiumPassengers();
    public:
        Flight(
            std::string date_val = "01/01/9999", 
            std::string hour_val = "00:00",
            double price_val = 0.0,
            std::string model_val = "d",
            std::string fromTo_val = "e",
            double distance_val = 0.0,
            std::string crew_val = "f"
        );

        std::string getDate();
        void setDate(std::string d);
        std::string getHour();
        void setHour(std::string h);
        double getPrice();
        void setPrice(double p);
        std::string getAirplaneModel();
        void setAirplaneModel(std::string am);
        std::string getFromTo();
        void setFromTo(std::string ft);
        double getDistance();
        void setDistance(double d);
        std::string getCrew();
        void setCrew(std::string c);
        double getFuel();
        void setFuel(double f);
        void reservaAsiento();
        void reservaAsientoPremium();
        int getNumberOfPassengers();
        int getNumberOfPremiumPassengers();
        void info();
        void printPassengers();
    
};

#endif