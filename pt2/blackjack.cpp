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
    friend ostream& operator<< (ostream &out, const Card &crd);

    private:
        cardrank rank;
        bool istapped;
    public:
        Card(cardrank nrank, cardsuit nsuit) : rank(nrank), suit(nsuit), istapped(false)
        {
        }

        ~Card()
        {
        }

        bool IsFlipped() const
        {
            return istapped;
        }

        void Flip() 
        {
            istapped = !istapped;
        }

        int Getvalue() const
        {
            return rank;
        }

    protected:
        cardsuit suit;
       
};

ostream& operator<< (ostream &out, const Card &crd)                         /// output overloading for cards ///
{
    const int suits[] = {3, 6, 4, 5};
    const string ranks[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    if (crd.IsFlipped())
        out << ranks[crd.Getvalue()] << char(suits[crd.suit]) << " ";
    else
        out << "XX ";
    
    return out;
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

        vector<Card*> getDeck() const
        {
            return deck;
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
    friend ostream& operator<< (ostream &out, const GenericPlayer &Pl);

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

ostream& operator<< (ostream &out, const GenericPlayer &Pl)                 /// output overloading for player ///
{
    string cardstack;
    vector<Card*> pldeck = Pl.getDeck();
    
    
    out << Pl.getName();    
    
    vector<Card*> :: const_iterator card;
    if (!pldeck.empty())
    {
        for (card = pldeck.begin(); card != pldeck.end(); ++card)
        {
            out << *(*card) << " ";
        }
    }

    out << "points: " << Pl.getValue() << endl;
    return out;
};

class Player : public GenericPlayer
{
    private:
    public:
        Player(string n) : GenericPlayer(n)
        {
        }

        ~Player()
        {
        }

        virtual bool isHitting() const                  // is it okay to consider "no" as answer for any other key than yY?
        {
            char query;
            while(query == 'y' || query == 'n' || query == 'Y' || query == 'N')
            {
            cout << "Take another card?(y/n) " << endl;
            cin >> query;
            }
            
            return (query == 'y' || query == 'Y');
        }

        void Win() const
        {
            cout << getName() << " has won." << endl;
        }

        void Lose() const
        {
            cout << getName() << " has lost." << endl;
        }

        void Push() const
        {
            cout << getName() << " is in draw." << endl;
        }

};

class House : public GenericPlayer
{
    private:
    public:
        virtual bool isHitting() const
        {
            return (getValue() < 17);
        }

        void FlipFirstCard()
        {
            if (!getDeck().empty())
            {
                Card a = *getDeck().at(0);
                a.Flip();
            }
        }
};

}