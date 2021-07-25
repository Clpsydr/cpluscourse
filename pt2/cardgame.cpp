#include <cstdio>
#include <iostream>
#include <vector>
#include <sstream>
#include "blackjack.h"

using namespace BlackJack;

bool intcheck(std::string input)
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

int main()
{
    int PlayerCount = 0;
    std::vector<std::string> PNames;
    std::string t_namequery;
    std::string t_name;                                  // provisional string player input
    char t_query;                                        // provisional y/n player input

    std::cout << "Enter amount of players (max 7) - ";

    while (true)
    {
        std::getline(std::cin,t_namequery);
        if (intcheck(t_namequery))
        {
            std::stringstream conv;
            conv << t_namequery;
            conv >> PlayerCount;
            if (PlayerCount > 1 && PlayerCount < 7)
                break;
            else
                std::cout << "Incorrect number of players, try another number" << std::endl;
        }
        else
            std::cout << "Incorrect input, please try again." << std::endl;
    }

    for(int i=0; i<PlayerCount; i++)
    {
        std::cout << std::endl << "Enter name of player " << i+1 << " - ";
        std::cin >> t_name;
        PNames.push_back(t_name);
    }
    
    Game NewGame(PNames);
    while(t_query != 'n' && t_query != 'N')
    {
        NewGame.Play();
        std::cout << "restart the game? (input any key to restart, N to stop) - ";
        std::cin >> t_query;
    }

    return 0;
}