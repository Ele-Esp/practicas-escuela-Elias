#pragma once
#ifndef _AIRLINE_H_
#define _AIRLINE_H_
#include <string>
#include <vector>
#include "Flight.h"
#include <iterator>


class Airline {
    private:
        std::string boardingCity;
        std::string name;
        std::string shortName;
        double incomes;
        void initFlights();
        std::string date;
    public:
        Airline(std::string date, std::string boardingCity_val = "", std::string name_val = "", std::string shortName_val = "");
        std::vector<Flight> flights;
        void updateAirline();
        void scheduleFlight();
        void currentIncome();
        std::string getBoardingCity();
        std::string getShortName();
        void setShortName(std::string shortName);
        double getIncomes();
        void setIncomes(double incomes);
        double closeOperataion();
        void printFlights();
        std::vector<Flight> getFlights();

};

#endif