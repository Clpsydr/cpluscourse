#include <iostream>
#include <cstdlib>

const int fieldwidth = 3;
const int fieldheight = 3;

using namespace std;

int main()
{
/// create and init shortint int long long char bool float double  ///
    {
        short int smallvar = 128;
        int okvar = 32000;
        long long bigvar = -322912982918274282;
        char onesymbol = 'A';
        bool flag = true;
        float pointvar = 3.141568;
        double iforgotpinumbers = 3.1415688887;
        cout << "Task1 \n";
        cout << "integers: " << smallvar << " " << okvar << " " << bigvar << endl;
        cout << "symbol: " << onesymbol << " boolean: " << flag  << endl;
        cout << "float: " << pointvar << " longerfloat: " << iforgotpinumbers  << endl;
    }

///  enum for tictac toe, array init  ///
    {
        enum tictactoe {_, X, O};                       

        tictactoe gamefield[fieldwidth][fieldheight] = { _ };   //initializing the board
        
        cout << "\n\nTask2. current field is:";
        for (int i = 0; i < fieldwidth; i++)            //displaying the board, feels hacky
        {
            cout << "\n";
            for (int j = 0; j < fieldheight; j++)
                switch (gamefield[i][j])
                {
                    case 0:
                    {
                        cout << "_ ";
                        break;
                    };
                    case 1:
                    {
                        cout << "X ";
                        break;
                    };
                    case 2:
                    {
                        cout << "O ";
                        break;
                    }
                    default:
                        cout << "? ";
                }
        }


/// * task  ///
// data structure for tic tac toe game
    
        enum gamestates {INPROCESS, END};
        enum colors {RED, BLUE, GREEN, YELLOW};

        //structure for player data
        struct player
        {
            char name[10];
            bool cpu;           //whether players turn operated by computer or keyboard input

            colors color;          //arbitrary color for board symbols and name?
            tictactoe symbol;   //not sure if needed, possibly automatically assigned based on starting turn 
        };

        //structure for the game session
        struct tictacgame 
        {
            tictactoe field;            //current field
            gamestates gamestate;       //for algorythm to continue the game or not?
            int playerturn = 0;         //for controlling order of player turns - that shall define which symbol players use

            player players[2];          //set of players
        };
    }

/// ** task
// union in struct, query user 
    {
        short int choice;

        union tempswap
        {
            int temperature;
            float precisetemp;
            char temptype;
        };

        struct mutablevar
        {
            tempswap temp;
            unsigned short isInt : 1;
            unsigned short isFloat : 1;
            unsigned short isChar : 1;
        };
        
        mutablevar weirdvar;
        
        weirdvar.isInt = 0;
        weirdvar.isFloat = 0;
        weirdvar.isChar = 0;
        
        cout << "\n\nTask** Please input a number for either float(1), char(2) or integer(3) temperature value: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
            {
                cout << "\n enter a floating point temperature: ";
                cin >> weirdvar.temp.precisetemp;
                weirdvar.isFloat = 1;
                weirdvar.isChar = 0;
                weirdvar.isInt = 0;
                break;
            }
            case 2:
            {
                cout << "\n enter a temperature type as one symbol: ";
                cin >> weirdvar.temp.temptype;
                weirdvar.isFloat = 0;
                weirdvar.isChar = 1;
                weirdvar.isInt = 0;
                break;
            }
            case 3:
            {
                cout << "\n enter an integer temperature: ";
                cin >> weirdvar.temp.temperature;
                weirdvar.isFloat = 0;
                weirdvar.isChar = 0;
                weirdvar.isInt = 1;
                break;
            }
            default:
                cout << "\n we didn't write anything in...";
        }

        //union output (without its own function for structure yet)
        if (weirdvar.isChar)
            cout << "\n Union so far holds a character, its " << weirdvar.temp.temptype;    
        else if (weirdvar.isFloat)
            cout << "\n Union so far holds floating point temperature, its " << weirdvar.temp.precisetemp;    
        else if (weirdvar.isInt)
            cout << "\n Union so far has an integer temperature, its " << weirdvar.temp.temperature;
        else
            cout << "\n theres nothing sensible written in the union yet!";
    }
    return 0;
}