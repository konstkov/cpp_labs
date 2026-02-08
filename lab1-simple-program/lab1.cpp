#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
using namespace std;

void outputVector( const vector< double > &numbers );

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
        int len=0;
        cout << "Please enter amount of numbers you would like to enter:\n" << endl;
        cin >> len;
        vector< double > numbers(len);
        for (int i = 0; i < len; i++)
        {
                cout << "Please enter a number:\n" << endl;
                cin >> numbers[i]; // assigning entered values to the vector
        }
        outputVector(numbers);

        return 0;
}

void outputVector( const vector< double > &numbers )
{
        cout << "\n After the input vector contains:" << endl;
        for ( const double number : numbers)
                cout << fixed << setprecision(4) << number << " ";
        cout << "\n Sum of all values:" << endl;
        auto sum = reduce(numbers.begin(), numbers.end());
        cout << fixed << setprecision(4) << sum << endl; // print sum
} // end function outputVector






