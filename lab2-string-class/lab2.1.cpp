//
// Created by Konstantin Kovalev on 21.1.2026.
//

#include <iostream>
#include <fstream>

#define BRACKETS 2 // count (2) of '<' and '>' characters

using namespace std;

void outputLine(const vector <string> &xml, const string &tagName);

vector <string> find_all_elements(const string &xml, string
tag_name);

int main()
{
        string fileName;
        string xmlStr;
        string userInput;

        cout << "Please enter the file name or 'stop' to quit: \n";
        getline(cin, fileName);

        ifstream file(fileName, ios::in);

        if (!file)
        {
                cerr << "Error opening the file" << endl;
                exit (EXIT_FAILURE);
        }

        while (userInput !="stop")
        {
                        cout << "Please enter the tag name: \n";
                        getline(cin ,userInput);
                if (userInput !="stop")
                {
                        while (file >> xmlStr) find_all_elements(xmlStr, userInput);
                        file.clear();
                        file.seekg(0); // return to the beginning
#if 1
                        if (find_all_elements(xmlStr, userInput).empty())
                        {
                                cout << "Not found\n" << endl; // if vector is empty print not found
                        }
#endif
                }
        }
        return 0;
}

vector <string> find_all_elements(const string &xml, string tag_name)
{
        string formattedStr;
        vector <string> strVector;
        if (xml.find(tag_name)!=string::npos)
        {
                auto tagLen=tag_name.size();
                auto len=xml.find_last_of('<') - tag_name.size();
                formattedStr=xml.substr(tagLen + BRACKETS, len - BRACKETS);
                strVector.push_back(formattedStr);
        }
        outputLine(strVector, tag_name);
        return strVector;
}

void outputLine(const vector <string> &xml, const string &tagName)
{
        for (auto & v : xml)
        {
                cout << tagName << " : " << xml[0] << endl;
        }
}
