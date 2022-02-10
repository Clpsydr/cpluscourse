/*
1. Algorithm that checks if the input is valid as integer value. Warns if otherwise, but doesnt stop the input.
2. Endll method for iostream which skips two lines and flushes buffer
3. Black Jack class Player() inheriting from a GenericPlayer().
4. Black Jack class House() inheriting from a GenericPlayer()
*/

#include <iostream>
#include <fstream>
#include <cstdint>
#include <sstream>

using namespace std;
bool intcheck(string input)
{
    if (input.length() < 1)
        return 0;

    if ((input[0] != '-') && !isdigit(input[0]))              // checking for negative integers, by excluding all symbols other than minus
        return 0;

    for (int i = 1 ; i < input.length(); i++)               // non digit checks for the rest
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

class YandexParse                   // crude searching mechanism that relies on finding really specific values on yandex title page
{
    private:
        string c_target;          //setting the target of searching
        string c_display;       // representation of the target
        string c_filter;         // additional components that needed to filter out html fragments and leave only values
        string c_datefilter;
    public:
        YandexParse(string t, string tview, string f1, string f2) : c_target(t), c_display(tview), c_filter1(f1), c_filter2(f2)
        {
        }

        ~YandexParse()
        {
        }

        void Check(string filepath)       
        {
            ifstream parsefile(filepath);

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

                stringanchor = searchline.find(c_target,0);
                if (stringanchor != string::npos)
                {
                    cout << c_display << GetText(searchline, stringanchor, c_filter+"\">", "<") << endl;
                    cout <<  GetText(searchline, stringanchor, c_datefilter+"\">", "<" ) << endl;
                }

            }
        }
};

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
YandexParse YforDollars(">USD<", " US dollars ", "\"inline-stocks__value_inner", "inline-stocks__item__baloon_inner");
YandexParse YforEuros(">EUR<", " Euros ", "\"inline-stocks__value_inner", "inline-stocks__item__baloon_inner");
YforDollars.Check("yandex.html");
YforEuros.Check("yandex.html");

    return 0;
}