#ifndef __BLACKJACK_H__
#define __BLACKJACK_H__

namespace BlackJack
{

enum cardsuit {hearts, spades, diamonds, clubs};
enum cardrank {ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king};

class Card
{
    friend std::ostream& operator<< (std::ostream &out, const Card &crd);

    private:
        cardrank rank;
        cardsuit suit;
        bool istapped;
    public:
        Card(cardrank nrank, cardsuit nsuit);
        ~Card();
        bool IsFlipped() const;
        void Flip();
        int GetValue() const;
        int GetRank() const;
        int GetSuit() const;
};

std::ostream& operator<< (std::ostream &out, const Card &crd);

class Hand
{
    public:
        Hand();
        virtual ~Hand();
        void Add(Card *newcard);
        void Clear();
        int Count() const;
        int getValue() const;
        std::vector<Card*> *getDeck();
    protected:
        std::vector<Card*> deck;
};

class GenericPlayer : public Hand
{
    friend std::ostream& operator<< (std::ostream &out, const GenericPlayer &Pl);

    private:
        std::string name;
    
    public: 
        GenericPlayer(const std::string& n);

        virtual ~GenericPlayer();
        virtual bool IsHitting() const = 0;
        bool IsBusted() const;
        void Bust() const;
        std::string getName() const;
};

std::ostream& operator<< (std::ostream &out, const GenericPlayer &Pl);                 /// output overloading for player ///

class Deck : public Hand
{
    private:
    public:
        Deck();
        ~Deck();
        void Populate();
        void Shuffle();
        void Deal(Hand& aHand);
        void AdditionalCards(GenericPlayer& GPlayer);
};

class Player : public GenericPlayer
{
    private:
    public:
        Player(std::string n);
        virtual ~Player();
        virtual bool IsHitting() const;                   // is it okay to consider "no" as answer for any other key than yY?
        void Win() const;
        void Lose() const;
        void Push() const;
};

class House : public GenericPlayer
{
    private:
    public:
        House(const std::string name = "House");
        virtual ~House();
        virtual bool IsHitting() const;
        void FlipFirstCard();
};


class Game
{
    private:
        Deck deck;
        House dealer;
        std::vector<Player> Players;

    public:
        Game(const std::vector<std::string>& Pnames) ;
        ~Game();
        void Play();
};

}

#endif