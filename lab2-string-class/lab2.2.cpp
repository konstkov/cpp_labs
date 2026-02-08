//
// Created by Konstantin Kovalev on 21.1.2026.
//

#include <iostream>
#include <numeric>

using namespace std;

class RunningAverage
{
public:
        explicit RunningAverage(int len)
                : maxLen(len)
        {
                // empty body
        }
        void add_value(int value)
        {
        if (numbers.size()==maxLen) numbers.pop_front();
                numbers.push_back(value);
        }
        double get_average()
        {
        auto average=accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size();
                return average;
        }
private:
        deque <int > numbers;
        int maxLen;
};

int main()
{
        int value=1;
        RunningAverage runningAverage(5);
        while (value !=0)
        {
                cout << "Please enter any number or '0' to stop:\n" << endl;
                cin >> value;
                if (value !=0)
                {
                        runningAverage.add_value(value);
                        cout << "The current running average is: \n" << runningAverage.get_average() << endl;
                }
        }
        return 0;
}