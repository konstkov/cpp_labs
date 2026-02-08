//
// Created by Konstantin Kovalev on 21.1.2026.
//

#include <iostream>
#include <fstream>

using namespace std;

void outputLine(const vector <string> &xml, const string &tagName);

vector <string> find_all_elements(const string &xml, string
tag_name);

int main()
{
        string fileName;
        string xmlStr;
        string userInput;
        string fileContents;

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
                         while (file >> xmlStr) // read file line by line and concatenate each line to final output str
                         {
                         fileContents+=xmlStr;
                         }
                         find_all_elements(fileContents, userInput);

                }
                file.clear();
                file.seekg(0); // return to the beginning
        }
        return 0;
}

vector <string> find_all_elements(const string &xml, string tag_name)
{
        // new str for opening and closing tags

        string opening_tag = "<" + tag_name + ">";
        string closing_tag = "</" + tag_name + ">";
        size_t closing_tag_pos = 0; // pos that keeps incremented and used for tracking
        auto op_tag_len=opening_tag.size(); // find opening tag's length (only once per user input)

        // other strings

        vector <string> str_vector;
        bool is_found=false;

        while (xml.find(opening_tag, closing_tag_pos)!=string::npos) // search for the specified tag name until we reach the end of str
        {
                is_found=true;
                auto op_first_char_pos = xml.find(opening_tag, closing_tag_pos); // pos of 1st char of the opening tag
                auto after_op_tag_pos = op_first_char_pos + op_tag_len; // pos of 1st char after the opening tag (+ '>')
                closing_tag_pos = xml.find(closing_tag, after_op_tag_pos);// pos of 1st char of the closing tag;
                auto str_len=closing_tag_pos - after_op_tag_pos; // len of str between tags; - 2 steps ('</' )

                // now extracting the string between tags

                string sub_str=xml.substr(after_op_tag_pos, str_len); // substr (str between xml tags)
                str_vector.push_back(sub_str); // append formatted str to the output(final result) vector
        }

        outputLine(str_vector, tag_name);
        if (!is_found) cout << "Not found!\n" << endl; // searched tag is not found

        return str_vector;
}

void outputLine(const vector <string> &xml, const string &tagName)
{
        for (auto const &i : xml)
        {
                cout << tagName << " : " << i << endl;
        }
}
