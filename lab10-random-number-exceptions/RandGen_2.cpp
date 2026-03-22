#include "RandGen_2.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>

int RandGen_2::operator()()
{
        if (numbers.size() >= max_value - min_value + 1)
        {
                throw std::runtime_error("Cannot generate the specified number of unique numbers within given range. \n");
        }
        int number = 0;
        do
        {
                number = distrib(engine);
        }while(find(numbers.begin(), numbers.end(), number) != numbers.end());
        numbers.push_back(number);
        return number;
}
/*
void RandGen_2::printNumbers() const
{
        std::cout << "Generated random numbers: \n" << std::endl;
        for (const auto &n : numbers)
        {
                std::cout << n<< std::endl;
        }
        std::cout << "End of generator. \n" << std::endl;
}
*/
void RandGen_2::clearNumbers()
{
        numbers.clear(); // clear the vector
}
