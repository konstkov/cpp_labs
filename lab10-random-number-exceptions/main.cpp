#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "RandGen_2.h"

void test_generator(RandGen_2 &ur, int count)
{
        auto count_gen_numbers = 0;
        std::cout << "Generated random numbers: \n" << std::endl;
        while (count--)
        {
                try
                {
                        std::cout << ur() << std::endl; // generate a random number and print it
                        ++count_gen_numbers;
                } catch (std::runtime_error &e)
                {
                        std::cout << "Error: " << e.what() << "Could only generate: "
                        << count_gen_numbers << " numbers" << std::endl;
                        break;
                }
        }
        std::cout << "End of generator. \n" << std::endl;
}

int main()
{
RandGen_2 randGen(5, 17);

test_generator(randGen, 3);
//randGen.printNumbers();

test_generator(randGen, 6);
//randGen.printNumbers();

test_generator(randGen, 13); // this will cause exception
//randGen.printNumbers();

RandGen_2 randGen2(1, 35);

test_generator(randGen2, 7);
//randGen2.printNumbers();

test_generator(randGen2, 7);
//randGen2.printNumbers();

test_generator(randGen2, 7);
//randGen2.printNumbers();

test_generator(randGen2, 70); // this will cause exception
//randGen2.printNumbers();

}





