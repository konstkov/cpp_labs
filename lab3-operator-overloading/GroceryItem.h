//
// Created by Konstantin Kovalev on 24.1.2026.
//

#ifndef C__COURSE_GROCERYITEM_H
#define C__COURSE_GROCERYITEM_H


class GroceryItem
{
        friend std::ostream & operator<<(std::ostream & , const GroceryItem & );
        friend std::istream & operator>>(std::istream & , GroceryItem & );
public:
        GroceryItem(); // default constructor
        explicit GroceryItem (std::string & name, int weight, double price, int discount); // parameterized constructor

        std::partial_ordering operator<=>(const GroceryItem &) const;
        bool operator==(const GroceryItem &) const;

#if 1
        void setName(const std::string & ); // set name
        std::string getName() const; //return name

        void setWeight(int weight); // set weight
        int getWeight() const; // return weight
#endif
        void setDiscount(int discount); // set the discount
        int getDiscount() const; // return the discount amount

        void setPrice(double price); // set price
        double getPrice() const; //return price

private:
        std::string item_name;
        int item_weight;
        double item_price;
        int item_discount;
};

// non-member functions (for controlling the main program flow)

void printItem(const std::vector <GroceryItem> &items); // print item information
auto netWorth(const std::vector <GroceryItem> &items); // calculate net worth of all items
void changeDiscount(std::string &user_input, std::vector <GroceryItem> &items); // change discount percentage of different items
double applyDiscount(const double &price,const int &discount); // apply the discount to the price

void nameInput(std::string &user_input, std::vector <GroceryItem> &items); // when user enters name of the item
void jsonInput(std::vector <GroceryItem> &items); // when user enters 'json'
void changeItem(std::vector <GroceryItem> &items); // when user enters 'stop' for the first time

#endif //C__COURSE_GROCERYITEM_H