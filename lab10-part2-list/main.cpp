//
// Created by Konstantin Kovalev on 24.1.2026.
//

#include <iostream>
#include <fstream>
#include <filesystem>

#include "GroceryItem.h"

using namespace std;

//The class must use std::string for storing the name of the item, an int for the weight of the item in
//grams, a double for price of the item in euros, and an int for the discount percentage

// { "Name":"Diced chicken", "Weight":350, "Price":5.30, "Discount": 0 }

void openFile(std::vector <GroceryItem> &items)
{
        string file_string;
        string fileName;

        std::cout << "Please enter the name of the file to read items from: \n" << std::endl;

        // getline(cin, fileName);

        getline(std::cin >> std::ws, fileName);

        ifstream file(fileName, ios::in);

        // file.open(fileName);

        if (!file.is_open())
        {
                throw std::runtime_error("Error, cannot open the file");
        }

        jsonInput(file, items);
}

int main()
{
        string user_input; // create a string for storing user input¨
        vector <GroceryItem> items; // define a vector of object of the class "GroceryItem"

        while (user_input!="stop") // if input is not stop continue creating items
        {
                cout << "Enter item information, starting with the name or “stop” \n"
                        "to end entering items or “json” to enter item information in JSON format:\n" << endl;
                getline(cin, user_input);
                if (user_input!="stop") // if user doesn't enter stop
                {
                        if (user_input=="json") // if user enters 'json'
                        {
                                try
                                {
                                        openFile(items);
                                } catch (std::runtime_error &e)
                                {
                                        std::cout << "Caught exception: " << e.what() << std::endl;
                                        return 1;
                                };

                                // jsonInput(cin,items);
                        }
                        //otherwise, create item object and add it to vector

                        else if (user_input!="json")
                        {
                                nameInput(user_input, items);
                        }
                }
        }
        // if user did enter stop

        changeItem(items);

        std::string discount_percentage;
        std::cout << "Type 'list' to show only items with specific discount: " << std::endl;
        getline(std::cin, user_input);
        if (user_input == "list")
        {
                std::cout << "Enter the discount percentage: " << std::endl;

                getline(std::cin, discount_percentage);
                auto discount = stoi(discount_percentage);

                std::cout << "Items with discount greater or equal to the one specified: \n" << std::endl;
                for (auto &s : items)
                {
                        if (s.getDiscount()>=discount)
                        {
                                std::cout << s << std::endl; //loop through the vector and use overloaded operator to print the item info
                        }
                }
        }
        // terminate the program
        return 0;
}
