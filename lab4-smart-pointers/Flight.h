//
// Created by Konstantin Kovalev on 27.1.2026.
//

#ifndef C___COURSE_FLIGHT_H
#define C___COURSE_FLIGHT_H

class Passenger;

class Flight
{
        friend std::ostream & operator<<(std::ostream &output, const Flight &f);

public: // parameterized constructor
        explicit Flight(const std::string &, const std::string &, int);//, std::vector<std::shared_ptr<Flight>>); // and a vector of smart pointers

        std::strong_ordering operator<=>(const Flight & other) const;

        void printPassengerList( std::vector<std::shared_ptr<Passenger>> &passengers) const;// Name of passenger, number of bags, flight(s) that the passenger is on
        bool addPassenger(std::shared_ptr<Passenger> &p,const std::shared_ptr<Flight> &flight_to_book); //member function for adding a passenger to the flight.
        bool removePassenger(); // member function for removing passenger by name.
        void printFlightInfo(const std::vector<std::shared_ptr<Flight>> &flights, std::vector<std::shared_ptr<Passenger>> &passengers);

private:
        std::string flight_number;
        std::string operator_name;
        int flight_capacity;
        std::vector<std::weak_ptr<Passenger>> passengers; // and a vector of smart pointers (which passengers are booked on the flight)
};

//non-member functions
void enterFlightInfo( std::vector<std::shared_ptr<Flight>> &flights );

int chooseFlight(const std::vector<std::shared_ptr<Flight>> &flights );

bool compareFlights(const std::shared_ptr<Flight> &a, const std::shared_ptr<Flight> &b);

#endif //C___COURSE_FLIGHT_H