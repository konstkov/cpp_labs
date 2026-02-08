//
// Created by Konstantin Kovalev on 27.1.2026.
//

#include  <iostream>
#include <string>
#include "Passenger.h"
#include "Flight.h"

Passenger::Passenger(const std::string &first, const std::string &last, const int bags)//, std::weak_ptr<Flight>flight) // and a vector of smart pointers to Flight(s) the passenger is on.
: first_name{first}, last_name{last}, bags_count{bags}//, flights{std::move(flight)}
{}

std::strong_ordering Passenger::operator<=>(const Passenger & other) const
{
        auto p = this->first_name <=> other.first_name; // first name will take the precedence during sorting

        if (p == 0) p = this->last_name <=> other.last_name; // if first names are identical sort by last names
        return p;
}

bool Passenger::findPassenger(std::string &first, std::string &last)
{
        if (this->first_name==first && this->last_name==last) return true;
        else
        {
                std::cout << "Passenger not found.\n" << std::endl;
                return false;
        }
}

void Passenger::printPassengerInfo(const std::shared_ptr<Passenger> &p)
{
        std::cout << "First_name: " << p->first_name << "\n"
        << "Last_name: " << p->last_name << "\n" << "Bags: "
        <<  p-> bags_count << "\n" << std::endl;
}

// create a member function for adding a flight for a passenger

void Passenger::addFlightForPassenger(const std::shared_ptr<Flight> &flight_to_book)
{
        this->flights.push_back(flight_to_book); // make weak pointer from vector of Flights(private data inside THIS class) point to a shared pointer of flights that is owned by main.cpp and index of which is specified by user, which automatically turns the shared pointer into a weak one
}

//non-member functions
int userPrompt(const std::string &keyword)
{
        std::string user_input;
        std::cout << "Please enter number of " << keyword << "s" <<  ":\n" << std::endl;
        getline(std::cin, user_input);
        auto total = std::stoi(user_input);//convert to int with stoi
        std::cout << "Enter information for each " << keyword << ":" << std::endl;
        return total;
}

void enterPassengerInfo(std::vector<std::shared_ptr<Passenger>> &passengers)
{
        std::string first_name;
        std::string last_name;
        std::string user_input;

        std::cout << "Enter the passenger's first name:\n" << std::endl;
        getline(std::cin, first_name);
        std::cout << "Enter the passenger's last name:\n" << std::endl;
        getline(std::cin, last_name);
        std::cout << "Enter the number of bags passenger has:\n" << std::endl;
        getline(std::cin, user_input);
        auto bags_count = std::stoi(user_input);
        auto passenger = std::make_shared<Passenger>(first_name, last_name, bags_count);
        passengers.push_back(passenger); // append it to a vector
        // After each passenger entry the user is presented a list of flights and is asked which
        //flights the passenger should be booked to.
}

