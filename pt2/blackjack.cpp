#include <iostream>
#include <cstdint>
#include <ctime>
#include <vector>

using namespace std;

namespace BlackJack
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum cardsuit {hearts, spades, diamonds, clubs};
enum cardrank {ace=1, two=2, three=3, four=4, five=5, six=6, seven=7, eight=8, nine=9, ten=10, jack=10, king=10, queen=10};

class Card
{
    private:
        cardrank rank;
        cardsuit suit;
        bool istapped;
    public:
        Card(cardrank nrank, cardsuit nsuit) : rank(nrank), suit(nsuit), istapped(false)
        {
        }

        ~Card()
        {
        }

        void Flip() 
        {
            istapped = !istapped;
        }

        int Getvalue() const
        {
            return rank;
        }
};

class Hand
{
    private:
        vector<Card*> deck;
    public:
        Hand()
        {
        }

        ~Hand()
        {
        }

        void Add(Card *newcard)
        {
            deck.push_back(newcard);
        }

        void Clear()
        {
            vector<Card*>::iterator iter;
            for (iter = deck.begin(); iter !=deck.end(); iter++)
            {
                delete *iter;
                *iter = 0;
            }

            deck.clear();
        }

        int Count() const
        {
           return deck.size();
        }

        int getValue() const                    // So, I assume that we only need 11 point Ace for cases where extra points would let us win (ie closer to 21)
        {
            bool hasAce = false;                        // doesnt matter how many aces we have, since even 2 aces is 22 points.
            int tempvalue = 0 ;
            for (int i = 0; i < deck.size(); i++)
            {
                if (deck[i]->Getvalue() == 1)
                    hasAce = true;
                tempvalue += deck[i]->Getvalue();
            }
            if ((hasAce) && tempvalue < 12)             // only adding for safe situations
                tempvalue += 10;                        

            return tempvalue;
        }
};

class GenericPlayer : public Hand
{
    private:
        string name;
    public: 
        GenericPlayer(string n) : Hand(), name(n)
        {
        }

        ~GenericPlayer()
        {
        }

        virtual bool IsHitting() const = 0;

        bool IsBusted() const
        {
            return (getValue() > 21);
        }

        void Bust() const
        {
            cout << name << " has lost with " << getValue() << " points";
        }

        string getName() const
        {
            return name;
        }
};

}