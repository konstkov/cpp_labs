//
// Created by Konstantin Kovalev on 27.1.2026.
//

#include <iostream>
#include <string>
#include <memory>
#include "Flight.h"
#include "Passenger.h"


// parameterized constructor
Flight::Flight(const std::string &number, const std::string &name, const int capacity)
        : flight_number{number}, operator_name{name}, flight_capacity{capacity} {
}
// overloaded output operator for printing the flight information
std::ostream & operator<<(std::ostream &output, const Flight &f)
{
        output << "Flight_number: " << f.flight_number << "\nOperator name: "
        << f.operator_name << "\nFlight capacity: " << f.flight_capacity << std::endl;//<< "Passengers: "
                return output; // enables cout << a << b << c
}

// overloaded operator <=>
std::strong_ordering Flight::operator<=>(const Flight & other) const
{
        auto f = this->flight_capacity <=> other.flight_capacity; // compare by number of available seats
        return f;
}

// member function for printing passenger list

void Flight::printFlightInfo(const std::vector<std::shared_ptr<Flight>> &flights, std::vector<std::shared_ptr<Passenger>> &passengers)
{
        std::cout << "Flight details:\n" << std::endl;
        for (auto & v : flights)
        {
                std::cout << *v << std::endl; // loop through the vector and print flight info
                std::cout << "List of passengers on this flight: \n" << std::endl;
                v->printPassengerList(passengers); // prints passenger list (which calls another function to print details of each passenger)
        }
}

void Flight::printPassengerList( std::vector<std::shared_ptr<Passenger>> &passengers) const
{
        for (int i=0; i < this->passengers.size(); ++i)
        {
                auto sh = this->passengers[i].lock();
                passengers[i]->printPassengerInfo(sh);
        }
}
//member function for adding a passenger to the flight.
bool Flight::addPassenger(std::shared_ptr<Passenger> &p,const std::shared_ptr<Flight> &flight_to_book) // Function returns true if a seat was available
{
        if  (passengers.size() < flight_capacity) // passengers is a vector of WEAK pointers of PASSENGER class that is private data member of THIS (FLight) class
        {
                passengers.push_back(p); // appending a SHARED_PTR to a vector of WEAK_PTR which automatically creates a WEAK_PTR
                p->addFlightForPassenger(flight_to_book);
                std::cout << "Seat is available. Booking successful!\n" << std::endl;
                return true;
        }
        else
        {
                std::string user_input;
                std::cout << "Sorry, the flight is fully booked.\n" << std::endl;
                std::cout << "Would you like to remove some passenger? [y/n].\n" << std::endl;
                getline(std::cin, user_input);
                if (user_input == "y") removePassenger();
                else if (user_input == "n") return true; // continue main program if user doesn't wish to remove a passenger
                return false;
        }
}

// member function for removing passenger by name.

bool Flight::removePassenger() // Function returns true if passenger was found and removed.
{
        std::string first_name;
        std::string last_name;
        std::cout << "Please enter the name of passenger you wish to remove.\n" << std::endl;
        std::cout << "First name:\n" << std::endl;
        getline(std::cin,first_name);
        std::cout << "Last name:\n" << std::endl;
        getline(std::cin,last_name);

        for (auto it = passengers.begin(); it !=passengers.end(); ++it) // iterates through the vector
        {
                auto p = it->lock();
                if (p->findPassenger(first_name, last_name))
                {
                        passengers.erase(it); // erases the weak pointer of matched passenger
                        std::cout << "Passenger successfully removed!\n" << std::endl;
                        ++flight_capacity; // increment flight capacity by 1
                        return true;
                }
        }
        return false;
}
// non-member functions

void enterFlightInfo( std::vector<std::shared_ptr<Flight>> &flights)
{
        std::string user_input;
        std::string flight_number;
        std::string operator_name;

                std::cout << "Enter the flight number:\n" << std::endl;
                getline(std::cin, flight_number);
                std::cout << "Enter the operator name:\n" << std::endl;
                getline(std::cin, operator_name);
                std::cout << "Enter the number of passengers that the plane can carry:\n" << std::endl;
                getline(std::cin, user_input);
                auto flight_capacity = std::stoi(user_input);
                // allocate memory and init one share pointer of Flight object
                auto flight = std::make_shared<Flight>(flight_number, operator_name,flight_capacity);
                flights.push_back(flight); // append it to a vector
}

int chooseFlight(const std::vector<std::shared_ptr<Flight>> &flights )
{
        std::string user_input;
        std::cout << "Please choose the flight by index:\n";
        for (int f = 0; f < flights.size(); ++f)
        {
                std::cout << *flights[f]; // dereferencing a pointer in order to print the values to which it points
                std::cout << "Index: " << f << std::endl;
        }
        getline(std::cin, user_input);
        int index = stoi(user_input);
        return index;
}

bool compareFlights(const std::shared_ptr<Flight> &a, const std::shared_ptr<Flight> &b) // comparator function for sorting the flights
{
return *a < *b;
}