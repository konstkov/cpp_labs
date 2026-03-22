#include <iomanip>
#include <iostream>
#include <type_traits>

/*Implement a function template that prints any integral value as hexadecimal number. The
number of digits printed must be twice the size of the value. For example, two digits for a
byte, four digits for a 16-bit integer, eight digits for a 32-bit integer etc. All non-ingeter values
are printed as: “[noint]”*/

template <typename T>
void printHex(T const &val, std::ostream &out = std::cout)
{
        // out << "The size of value in bytes: " << sizeof(val) << '\n'; // for debugging
        int digit_num = sizeof(val) * 2;
        if constexpr (!std::is_integral<T>::value)
        {
                out << "[noint]";
        }
        else
        {
                out << "0X" << std::setw(digit_num) << std::setfill('0') << std::hex << val << '\n';
        }
}

/*Implement a test program that uses the template with different integer and non-integer
types.*/

int main()
{
        printHex<int>(203);
        printHex<bool>(true);
        printHex<std::string>("Kimmo");

        return 0;
}

