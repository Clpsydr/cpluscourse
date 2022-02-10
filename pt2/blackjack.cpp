#include <iostream>
#include <cstdint>
#include <algorithm>
#include <ctime>
#include <vector>
#include "blackjack.h"

#define MAXHAND 7
#define MAXDECK 52
#define HEARTS "\u2660"
#define SPADES "\u2665"
#define DIAMONDS "\u2666" 
#define CLUBS "\u2663"

namespace BlackJack
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Card::Card(cardrank nrank, cardsuit nsuit) : rank(nrank), suit(nsuit), istapped(true)
    {
    }

Card::~Card()
    {
    }

bool Card::IsFlipped() const
    {
        return istapped;
    }

void Card::Flip() 
    {
        istapped = !istapped;
    }

int Card::GetValue() const
    {
        if (rank < 10)
            return rank+1;
        else 
            return 10;
    }

int Card::GetRank() const
    {
        return rank;
    }

int Card::GetSuit() const
    {
        return suit;
    }

std::ostream& operator<< (std::ostream &out, const BlackJack::Card &crd)                         /// output overloading for cards ///
{
    const std::string suits[] = {HEARTS, SPADES, DIAMONDS, CLUBS};
    const std::string ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    if (crd.IsFlipped())
        //out << ranks[crd.Getvalue()] << crd.GetSuit() << " ";
        out << ranks[crd.GetRank()] << suits[crd.GetSuit()] << " ";
    else
        out << "XX ";
    
    return out;
};

std::ostream& operator<< (std::ostream &out, BlackJack::GenericPlayer &Pl)                 /// output overloading for player ///
{
    std::string cardstack;
    std::vector<BlackJack::Card*> pldeck = *Pl.getDeck();

    out << "----------------" << std::endl;
    out << Pl.getName() << ": " << std::endl;    
    out << "Hand:-- ";
    
    std::vector<BlackJack::Card*> :: const_iterator card;
    if (!pldeck.empty())
    {
        for (card = pldeck.begin(); card != pldeck.end(); ++card)
        {
            out << *(*card) << " ";
        }
    }

    out << "points: " << Pl.getValue() << std::endl;
    return out;
};

////////////////////

Hand::Hand()
    {
        deck.reserve(MAXHAND);
    }

Hand::~Hand()
    {
    }

void Hand::Add(Card *newcard)
    {
        deck.push_back(newcard);
    }

void Hand::Clear()
    {
        std::vector<Card*>::iterator iter;
        for (iter = deck.begin(); iter !=deck.end(); ++iter)
        {
            delete *iter;
            *iter = 0;
        }
        deck.clear();
    }

int Hand::Count() const
    {
        return deck.size();
    }

std::vector<Card*>* Hand::getDeck()
    {
        return &deck;
    }

int Hand::getValue() const                    // So, I assume that we only need 11 point Ace for cases where extra points would let us win (ie closer to 21)
    {
        bool hasAce = false;                        // doesnt matter how many aces we have, since even 2 aces is 22 points.
        int tempvalue = 0 ;
        for (int i = 0; i < deck.size(); i++)
        {
            if (deck[i]->GetValue() == 1)
                hasAce = true;
            tempvalue += deck[i]->GetValue();
        }
        if ((hasAce) && tempvalue < 12)             // only adding for safe situations
            tempvalue += 10;                        

        return tempvalue;
    }


///////////////////////////////////////   

GenericPlayer::GenericPlayer(const std::string& n) : name(n)
    {
    }

GenericPlayer::~GenericPlayer()
    {
    }

bool GenericPlayer::IsBusted() const
    {
        return (getValue() > 21);
    }

void GenericPlayer::Bust() const
    {
        std::cout << name << " has lost with " << getValue() << " points! " << std::endl;
    }

std::string GenericPlayer::getName() const
    {
        return name;
    }


///////////////////////////////////////////////////////    

Deck::Deck()
    {
        deck.reserve(MAXDECK);
        Populate();
    }

Deck::~Deck()
    {
    }

void Deck::Populate()
    {
        Clear();
        for (int suit = BlackJack::cardsuit::hearts; suit <= BlackJack::cardsuit::clubs; ++suit)
        {
            for (int rank = BlackJack::cardrank::ace; rank <= BlackJack::cardrank::king; ++rank)
            {
                Add(new Card(static_cast<BlackJack::cardrank>(rank), static_cast<BlackJack::cardsuit>(suit)));
            }
        }
    }

void Deck::Shuffle()
    {
        std::srand (static_cast<unsigned int>(std::time(0)));
        random_shuffle(deck.begin(), deck.end());
    }

void Deck::Deal(Hand& aHand)
    {
        if (!deck.empty())
        {
            aHand.Add(deck.back());
            deck.pop_back();
        }
        else
        {
            std::cout << "No cards left in the deck.";
        }
    }

void Deck::AdditionalCards(GenericPlayer& GPlayer)
    {
        std::cout << GPlayer << std::endl;
        while(!(GPlayer.IsBusted()) && GPlayer.IsHitting())
        {
            Deal(GPlayer);
            std::cout << GPlayer << std::endl;

            if (GPlayer.IsBusted())
                GPlayer.Bust();        
        }
    }

//////////////////////////////////////////////////////////

Player::Player(std::string n) : GenericPlayer(n)
    {
    }

Player::~Player()
    {

    }

bool Player::IsHitting() const                   // is it okay to consider "no" as answer for any other key than yY?
    {
        char query;
        while(query != 'y' && query != 'n' && query != 'Y' && query != 'N')
        {
            std::cout << "Does " << getName() << " take another card?(y/n) " << std::endl;
            std::cin >> query;
        }
        return (query == 'y' || query == 'Y');
    }

void Player::Win() const
    {
        std::cout << getName() << " has won." << std::endl;
    }

void Player::Lose() const
    {
        std::cout << getName() << " has lost." << std::endl;
    }

void Player::Push() const
    {
        std::cout << getName() << " is in draw." << std::endl;
    }

///////////////////////////////////////////////////////////////

House::House(const std::string name) : GenericPlayer(name)
    {
    }

House::~House()
    {
    }

bool House::IsHitting() const 
    {
        return (getValue() < 17);
    }
    
void House::FlipFirstCard()
    {
        if (!deck.empty())
            deck[0]->Flip();
    }

///////////////////////////////////////////////////////////////

Game::Game(const std::vector<std::string>& Pnames) 
        {
            std::vector<std::string>::const_iterator iName;
            for (iName = Pnames.begin(); iName != Pnames.end(); ++iName)
                Players.push_back(Player(*iName));

            std::cout << "Making new deck...  ";
            deck.Populate();    

            std::cout << "Shuffling...  " << std::endl;
            deck.Shuffle();
        }

Game::~Game()
        {
        }

void Game::Play()
        {
            std::vector<Player>::iterator iPlayer;
            std::vector<Card*>::iterator iCard;


            std::cout << std::endl << HEARTS << SPADES << " GAME START " << DIAMONDS << CLUBS << std::endl << std::endl;

// initial 2 cards for everyone
            for (int i = 0; i < 2; i++)
            {
                for (iPlayer = Players.begin(); iPlayer != Players.end(); ++iPlayer)
                    deck.Deal(*iPlayer);
                deck.Deal(dealer);
            }

            dealer.FlipFirstCard();

// player display
            for (iPlayer = Players.begin(); iPlayer != Players.end(); ++iPlayer)
                std::cout << *iPlayer << std::endl; 
            std::cout << dealer;

// playing extra cards until bust or stop

            std::cout << std::endl << "- Adding card phase! - " << std::endl;
            for (iPlayer = Players.begin(); iPlayer != Players.end(); ++iPlayer)
            {
                deck.AdditionalCards(*iPlayer);
                std::cout << "next player >>>>>>>>>>>>>>>" << std::endl;
            }

            dealer.FlipFirstCard();
            std::cout << dealer << std::endl;

            deck.AdditionalCards(dealer);

// score roundup
            if(dealer.IsBusted())
            {
                for (iPlayer = Players.begin(); iPlayer != Players.end(); ++iPlayer)
                {
                    if (!iPlayer->IsBusted())
                        iPlayer->Win();
                }
            }
            else
            {
                for (iPlayer = Players.begin(); iPlayer != Players.end(); ++iPlayer)
                {
                    if (!iPlayer->IsBusted())
                    {
                        if (iPlayer->getValue() > dealer.getValue())
                            iPlayer->Win();
                        else if (iPlayer->getValue() < dealer.getValue())
                            iPlayer->Lose();
                        else
                            iPlayer->Push();
                    }
                }
            }

//postgame card cleanup
            for (iPlayer = Players.begin(); iPlayer != Players.end(); ++iPlayer)
                iPlayer->Clear();
            dealer.Clear();

        }

/////////////////////////////////////////
}