#include <random>
#include <vector>

//Function object
class RandGen_2 
{
public:
RandGen_2(const int min, const int max):
        engine(std::random_device{}()), distrib(min, max), min_value(min), max_value(max) {}
int operator()();
// void printNumbers() const;
void clearNumbers();

private:
int min_value;
int max_value;
std::vector<int> numbers;
std::mt19937 engine; // mersenne twister random number engine
std::uniform_int_distribution<> distrib; // uniform distribution that accepts min and max values
};
