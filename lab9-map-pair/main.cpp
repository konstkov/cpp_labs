#include <iostream>
#include <string>
#include <map>

void printMap(const std::map<std::string, std::pair<int, int>>&m);

// Write a program that defines a map<string, pair<int, int>> and uses the map to store course name,
//number of credits and grades.
int main()
{
    std::map<std::string, std::pair<int, int>>gradeMap;
    std::string user_input;

    while (true)
    {    
        std::cout << "Please enter a name of the course or 'stop' or 'print'\n" << std::endl;
        getline(std::cin, user_input);
        if (user_input == "stop")
        {
            break;
        }
        else if (user_input=="print")
        {
            printMap(gradeMap); // call print function
        }
        else 
        {
            std::pair<int, int> credits_grades;

            std::cout << "Please enter a number of credits: \n" << std::endl;
            std::string integer;
            getline(std::cin, integer);

            credits_grades.first = stoi(integer);; // credits

            std::cout << "Please enter a grade :\n" << std::endl;
            getline(std::cin, integer);
            credits_grades.second = stoi(integer); // read int from standard input (grades)
            
            gradeMap[user_input] = credits_grades; // use the course name (user_input) as the key to retrieve the index where to store the grades and credits
        }
    }
}  

void printMap(const std::map<std::string, std::pair<int, int>>&m)
{
    auto average = 0;
    for (const auto& [course_name, credits_grades] : m)
    {
        auto value = credits_grades.second;
        auto weight = credits_grades.first / credits_grades.second; // for calculating weighted average
        auto sum_weights = 0;
        sum_weights += weight;
        auto sum_value_weight = 0;
        sum_value_weight += value * weight;
        average = sum_value_weight / sum_weights;

        std::cout << "Course name: " << course_name << "; Credits: " << credits_grades.first <<
        "; Grade: " << credits_grades.second << std::endl;
    }
    std::cout << "Average GPA: " << average << std::endl;
}



