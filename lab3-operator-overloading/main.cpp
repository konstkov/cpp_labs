//
// Created by Konstantin Kovalev on 24.1.2026.
//

#include <iostream>
#include "GroceryItem.h"

using namespace std;

//The class must use std::string for storing the name of the item, an int for the weight of the item in
//grams, a double for price of the item in euros, and an int for the discount percentage

// { "Name":"Diced chicken", "Weight":350, "Price":5.30, "Discount": 0 }
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
                                jsonInput(items);
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
        // terminate the program
        return 0;
}