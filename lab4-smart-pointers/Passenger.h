//
// Created by Konstantin Kovalev on 27.1.2026.
//

#ifndef C___COURSE_PASSENGER_H
#define C___COURSE_PASSENGER_H

class Flight;

class Passenger
{
public:
        explicit Passenger(const std::string &, const std::string &, int);//, std::weak_ptr<Flight>flight) ; // and a vector of smart pointers to Flight(s) the passenger is on.
        // The Passenger class must implement operators that compare passengers by last name and then by first name.
        std::strong_ordering operator<=>(const Passenger & other) const;
        bool findPassenger(std::string &first, std::string &last);
        void printPassengerInfo(const std::shared_ptr<Passenger> &p);
        void addFlightForPassenger(const std::shared_ptr<Flight> &flight_to_book);

private:
        const std::string first_name;
        const std::string last_name;
        const int bags_count;
        std::vector<std::weak_ptr<Flight>> flights; // Passenger doesn't own Flight; breaking cyclic references
};
// non-member functions
int userPrompt(const std::string &);
void enterPassengerInfo(std::vector<std::shared_ptr<Passenger>> &passengers);


#endif //C___COURSE_PASSENGER_H