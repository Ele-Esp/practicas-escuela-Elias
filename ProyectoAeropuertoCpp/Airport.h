#pragma once
#ifndef _AIRPORT_H_
#define _AIRPORT_H_
#include <string>
#include "Airline.h"
#include <vector>
#include <iostream>
#include <iterator>
#include "Flight.h"

class Airport {
    private:
        int id;
        std::string city;
        std::string country;
        double totalTransactions;
        double totalDailyIncomes;
        void initAirlines();    
        std::string date;
public:
    std::vector<Airline> airlines;
    Airport(int inid = 0, std::string indate = "01/01/1989", std::string incity = "NA", std::string incountry = "NA");
    int getId();
    void setId(int id);
    std::string getDate();
    void setDate(std::string date);
    std::string getCity();
    void setCity(std::string city);
    std::string getCountry();
    void setCountry(std::string country);
    void startOperations(std::string id);
    void printAllFlights();
    double closeOperations();
    void printInfo();
    void printFlightsSchedule();
    
};
    

#endif