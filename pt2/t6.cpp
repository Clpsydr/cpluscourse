#include <iostream>
#include <fstream>
#include <cstdint>
#include <sstream>
//#include "blackjack.cpp"

using namespace std;
//using namespace BlackJack;

bool intcheck(string input)
{
    if (input.length() < 1)
        return 0;

    for (int i =0 ; i < input.length(); i++)
    {
        if (!isdigit(input[i]))
            return 0;
    }
    return 1;
}

ostream& endll (ostream& os)
{
    os.put('\n');
    os.put('\n');
    os.flush();
    return os;
}

string GetText(string source, int searchstart, string begin, string end)                // subfunction to extract values from one position to another in the string
                                                                                        // returns only text after searched "begin" of a size from begin to end
{
    int beginlength = begin.size();         // size of a searched line, used to negate length of searched text for display 
                                            // since we need only text after the searched one
    int startingpoint = source.find(begin,searchstart);         

    return source.substr(startingpoint+beginlength, source.find(end,startingpoint) - startingpoint - beginlength);
}

void YandexParse(string filename)                                                       // looking up in a certain file for currencies
{
    ifstream parsefile(filename);

    if (!parsefile)
    {
        cerr << "File not found, make sure its in the same folder";
        exit(1);
    }
    while(parsefile)
    {
        int stringanchor;
        string searchline;
        getline(parsefile, searchline);

        stringanchor = searchline.find(">USD<",0);
        if (stringanchor != string::npos)
        {
            cout << "US dollars: " << GetText(searchline, stringanchor, "\"inline-stocks__value_inner\">", "<") << " rubles" << endl;
            cout <<  GetText(searchline, stringanchor, "inline-stocks__item__baloon_inner\">", "<" ) << endl;
        }

        stringanchor = searchline.find(">EUR<",0);                 
        if (stringanchor != string::npos)
        {
            cout << "Euro: " << GetText(searchline, stringanchor,"\"inline-stocks__value_inner\">", "<") << " rubles" << endl;
            cout <<  GetText(searchline, stringanchor,"inline-stocks__item__baloon_inner\">", "<" ) << endl;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
//========================================================================================================================
string somenumber;                                                                                      // integer verification
int result;
cout << "Enter an integer value: ";
while (true)
{
    getline(cin, somenumber);
    if (!intcheck(somenumber))
        cout << "invalid number, please try again: ";
    else 
        break;
}
stringstream conv;
conv << somenumber;
conv >> result;
cout << "recorded a " << result;

//========================================================================================================================
cout << endll << "also, this is a double endl" << endll << "look, an extra line skipped!" << endll;             //endll usage

//========================================================================================================================
cout << "Additionally parsing files for currency rates" << endl;
YandexParse("yandex.html");
    return 0;
}