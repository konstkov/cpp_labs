//
// Created by Konstantin Kovalev on 17.1.2026.
//

#include <iostream>
#include <string>

using namespace std;

bool replaceChar(string &userInput, const string &currentChar,const string &desiredChar);

int main()
{
        const string stop( "stop" );
        string userInput ( "abc" );
        string currentChar ( "a" );
        string desiredChar ( "b" );

        while (userInput != stop)
        {
                cout << "\n Please enter any string or 'stop' to quit:\n";
                getline(cin, userInput);

                if (userInput != stop)
                {
                        cout << "\n Please enter: \n 1. Character to be replaced\n";
                        getline(cin, currentChar);
                        cout << "\n 2. Character to replace with\n";
                        getline(cin, desiredChar);

                         if (replaceChar(userInput, currentChar, desiredChar)) // replace the characters
                         {
                                cout << "\n Modified string: " << userInput << "\n" << endl;
                         }
                }
        }

        return 0;
}

bool replaceChar(string &userInput,const string &currentChar, const string &desiredChar)
{
        bool replaced = false;
        size_t position = userInput.find( currentChar ); // find first occurrence of the character to be replaced
        while ( position != string::npos )
        {
                replaced = true; // meaning that at least one char to be replaced was found
                userInput.replace(position, 1, desiredChar);
                position = userInput.find(currentChar, position + 1);
        }
        return replaced;
}

