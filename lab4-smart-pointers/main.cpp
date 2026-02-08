 //
// Created by Konstantin Kovalev on 27.1.2026.
//

#include <iostream>
#include "Passenger.h"
#include "Flight.h"

int main()
{// these vectors are passed by reference, so values are preserved after executing enter info functions
        std::vector<std::shared_ptr<Flight>> flights;
        std::vector<std::shared_ptr<Passenger>> passengers;

        static auto count = userPrompt("flight");
        while (count--) enterFlightInfo(flights); // enter flight data into object(pointed to by shared_ptr) and add to a vector
        count = userPrompt("passenger");
        while (count--) // count also represents the index of passenger
        {
                enterPassengerInfo(passengers);// count represents the number of passengers provided by user in userPrompt function
                const auto & flight_to_book = flights[chooseFlight(flights)]; // chooseFlight() returns index of the desired flight
                while (!flight_to_book -> addPassenger(passengers.back(), flight_to_book)); // if function add Passenger returns false ( meaning that the flight is fully booked) loop until it returns true ( there is an available seat)
        }

        std::sort(flights.begin(), flights.end(), compareFlights); // call comparator function that compares dereferenced values of pointers
        flights[0]->printFlightInfo(flights, passengers);

        return 0;
}