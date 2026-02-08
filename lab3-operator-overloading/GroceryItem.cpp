//
// Created by Konstantin Kovalev on 24.1.2026.
//

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <compare>
#include <algorithm>
#include <cctype>
#include "GroceryItem.h"

#define G_TO_KG 1000

std::ostream & operator<<(std::ostream &output, const GroceryItem &item) // overloaded stream insertion operator
{ // { "Name":"Diced chicken", "Weight":350, "Price":5.30, "Discount": 0 }
        output << '{' << " \"Name\": " << '"' << item.item_name << '"' << ','
                      <<  " \"Weight\": "  << item.item_weight  << ','
                      <<  " \"Price\": " << item.item_price  << ','
                      << " \"Discount\": " << item.item_discount << '}';
        return output; // enables cout << etc.
}

std::string & trimSpace(std::string &user_input)
{
        auto first_space = std::find_if(user_input.begin(), user_input.end(),[](unsigned char c){return !std::isspace(c);});
        auto last_space = std::find_if(user_input.rbegin(), user_input.rend(),[](unsigned char c){return !std::isspace(c);}).base();
        auto first = first_space - user_input.begin();

        auto trimmed_str = user_input.substr(first, last_space - first_space);

        return user_input; // return the string with trimmed white space
}

std::string removeAllWhitespace(std::string s)
{
        s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char c){ return std::isspace(c); }), s.end());
        return s;
}

std::istream & operator>>(std::istream &input, GroceryItem &item) // overloaded stream extraction operator
{ // { "Name":"Diced chicken", "Weight":350, "Price":5.30, "Discount": 0 }
        std::string user_input;
        getline(input, user_input, ':');
        std::string name("{ \"Name\"");
        if (removeAllWhitespace(user_input) != removeAllWhitespace(name ))
        {
                input.setstate(std::ios_base::failbit);
                return input;
        }
        getline(input, item.item_name, ',');
        getline(input, user_input, ':');
        std::string weight(" \"Weight\"");
        if (removeAllWhitespace(user_input) != removeAllWhitespace(weight ))
        {
                input.setstate(std::ios_base::failbit);
                return input;
        }
        getline(input, user_input, ',');
        item.item_weight = stoi(user_input); // convert string to int

        getline(input, user_input, ':');
        std::string price(" \"Price\"");
        if (removeAllWhitespace(user_input) != removeAllWhitespace(price ))
        {
                input.setstate(std::ios_base::failbit);
                return input;
        }
        getline(input, user_input, ',');
        item.item_price = stod(user_input);


        getline(input, user_input, ':');
        std::string discount(" \"Discount\"");
        if (removeAllWhitespace(user_input) != removeAllWhitespace(discount ))
        {
                input.setstate(std::ios_base::failbit);
                return input;
        }
        getline(input, user_input, '}');
        item.item_discount = stoi(user_input);
        return input; // enables cin >> a >> b >> c
}

//default constructor
GroceryItem::GroceryItem()
{
item_name="";
item_weight=0;
item_price=0.0;
item_discount=0;
}

// parameterized constructor
GroceryItem::GroceryItem(std::string & name, int weight, double price, int discount)
{
        item_name=name;
        item_weight=weight;
        item_price=price;
        item_discount=discount;
}
#if 1

// defining '<=>' operator form comparing prices/kg between different items
// change to strong_ordering if possible
std::partial_ordering GroceryItem::operator<=>(const GroceryItem &next_item) const
{
        auto curr_weight = (static_cast<double>(this->getWeight()) / G_TO_KG); // convert from grams to kilos
        auto next_weight = (static_cast<double>(next_item.getWeight()) / G_TO_KG); // convert from grams to kilos
        auto curr_price_per_kg = applyDiscount(this->getPrice() , this->getDiscount()) / curr_weight;
        auto next_price_per_kg = applyDiscount(next_item.getPrice() , next_item.getDiscount()) / next_weight;
        auto v= curr_price_per_kg <=> next_price_per_kg;
        return v;

} // defining '==' operator form comparing prices/kg between different items
bool GroceryItem::operator==(const GroceryItem &next_item) const
{
        auto curr_weight = (static_cast<double>(this->getWeight()) / G_TO_KG); // convert from grams to kilos
        auto next_weight = (static_cast<double>(next_item.getWeight()) / G_TO_KG); // convert from grams to kilos
        auto curr_price_per_kg = applyDiscount(this->getPrice() , this->getDiscount()) / curr_weight;
        auto next_price_per_kg = applyDiscount(next_item.getPrice() , next_item.getDiscount()) / next_weight;
        auto v= curr_price_per_kg == next_price_per_kg;
        return v;
}

//set name
void GroceryItem::setName(const std:: string &name)
{
item_name=name;
}
//return name
std::string GroceryItem::getName() const
{
return item_name;
}
//set weight
void GroceryItem::setWeight(int weight)
{
item_weight=weight;
}
//return weight
int GroceryItem::getWeight() const
{
return item_weight;
}
#endif
// set the discount
void GroceryItem::setDiscount(int discount)
{
item_discount=discount;
}
// return the discount amount
int GroceryItem::getDiscount() const
{
return item_discount;
}
// set price
void GroceryItem::setPrice(double price)
{
item_price=price;
}
//return price
double GroceryItem::getPrice() const
{
return item_price;
}

// non-member functions

void printItem(const std::vector <GroceryItem> &items)
{
        for (int v = 0; v < items.size(); ++v )
        {
                std::cout << items[v]; //loop through the vector and use overloaded operator to print the item info
                std::cout << " Index: " << v << std::endl; // print the index as well
        }

}

auto netWorth(const std::vector <GroceryItem> &items)
{ // calculate net worth
        auto net_worth = 0.0;
        for (auto & v : items) // loop through grocery items
        {
                net_worth += (applyDiscount(v.getPrice(), v.getDiscount())) * (static_cast<float>(v.getWeight()) / G_TO_KG); // calculate the net worth
        }
        return net_worth;
}

void changeDiscount(std::string &user_input, std::vector <GroceryItem> &items)
{
        auto index = stoi(user_input); // convert the input to int
        std::cout << "Enter discount percentage for the chosen item:\n" << std::endl;
        getline(std::cin, user_input);

        auto discount_percentage = stoi(user_input); // convert the input to int
        std::cout << "discount percentage(debugging):\n" << discount_percentage << std::endl;
        items[index].setDiscount(discount_percentage); // set discount for given item in a vector
        //auto discount_amount = items[index].getPrice() * (static_cast<double>(items[index].getDiscount()) / 100); // apply discount for specific item
        //auto price_after_discount = items[index].getPrice() - discount_amount; // calculate the price after discount
        //items[index].setPrice(price_after_discount);
}


double applyDiscount(const double &price, const int &discount)
{
        auto discount_amount = price * (static_cast<double>(discount) / 100); // apply discount for specific item
        auto price_after_discount = price - discount_amount; // calculate the price after discount
        return price_after_discount;
}

void nameInput(std::string &user_input, std::vector <GroceryItem> &items) // when user enters name of the item
{
        GroceryItem groceryItem; // create a grocery item object
        // set the item name passed by user
        groceryItem.setName(user_input);

        //prompt user for item weight
        std::cout << "Enter item weight:\n" << std::endl;
        getline(std::cin, user_input);
        auto weight=stoi(user_input); // typecast the string to int
        groceryItem.setWeight(weight);

        //prompt user for item price
        std::cout << "Enter item price:\n" << std::endl;
        getline(std::cin, user_input);
        auto price=stod(user_input); // typecast the string to double
        groceryItem.setPrice(price);

        //prompt user for item discount
        std::cout << "Enter item discount:\n" << std::endl;
        getline(std::cin, user_input);
        auto discount_percentage = stoi(user_input); // convert the input to int
        groceryItem.setDiscount(discount_percentage); // set discount for given item in a vector

        items.push_back(groceryItem); // add an object of the class "GroceryItem" to the vector
}

void jsonInput(std::vector <GroceryItem> &items) // when user enters 'json'
{
        GroceryItem groceryItem; // create a grocery item object
        do
        {
                std::cout << "Please enter the string in json format:\n" << std::endl;
                        std::cin >> groceryItem; // loop through the vector and append values to different values
                if (std::cin.rdstate() == std::ios_base::failbit) // check the current state of input stream
                {
                        std::cout << "Error! Please enter json string in correct format.\n"
                        << std::endl;

                        std::cin.clear();
                }
        }
        while (std::cin.rdstate() == std::ios_base::failbit); // keep looping until the parsing succeeds

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush cin
        items.push_back(groceryItem); // add a populated grocery item object to the vector
}

void changeItem(std::vector <GroceryItem> &items) // when user enters 'stop' for the first time
{
        std::string user_input;
        while (user_input !="stop")
        { // check whether user input is stop AGAIN
                sort(items.begin(), items.end()); // sort the vector (make it a separate function)
                printItem(items); // print all the items
                std::cout << "Net worth: " << netWorth(items) << std::endl; // print the net worth in the end

                std::cout << "Choose an item to change by typing the item "
                        "index or 'stop' to end the program:\n" << std::endl;
                getline(std::cin, user_input);
                if (user_input !="stop")
                {
                        changeDiscount(user_input, items);
                }
        }
}
#if 0
unsigned long jsonParser(std::string &user_input, const std::string &str_entry, std::istream &input)
{
        // reading name value
        auto json_entry = (R"(", )") + str_entry +  (R"(:)");
        auto static prev_pos = 0;
        auto static curr_pos = user_input.find(str_entry, prev_pos); // find occurrence of "Weight:" entry, save the pos
        if (curr_pos == std::string::npos)
        { // set fail-bit in case validation fails
                input.setstate(std::ios_base::failbit);
        }
        // then read the substring ( value of name entry) in between
        auto name_len = curr_pos - prev_pos;
        return name_len;
}
#endif