/*
1. Template class for pair of a certain value.
2. Template class for pair of different values.
3. StringValuePair() with a string and any other value.
*/
#include <iostream>
#include <cstdint>
#include <ctime>
#include <vector>
#include "blackjack.cpp"

using namespace std;
using namespace BlackJack;

template <typename T>
class Pair1
{
    private:
        T firstval;
        T secondval;
    public:
        Pair1(T fv, T tv) : firstval(fv), secondval(tv)
        {
        }

        ~Pair1()
        {
        }

        T first() const 
        {
            return firstval;
        }

        T second() const 
        {
            return secondval;
        }
};

template <typename T, typename N>
class Pair
{
    private:
        T firstval;
        N secondval;
    public:
        Pair(T fv, N tv) : firstval(fv), secondval(tv)
        {
        }

        ~Pair()
        {
        }

        T first() const
        {
            return firstval;
        }

        N second() const
        {
            return secondval;
        }
};

template<typename T>
class StringValuePair : public Pair<string, T>
{
    private:
        string firstval;
        T secondval;
    public:
        StringValuePair(string fv, T tv) : Pair<string, int> (fv, tv)
        {
        }

        ~StringValuePair()
        {
        }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
//========================================================================================================================
cout << "Task 1: " << endl;
Pair1<int> p1(6,9);
cout << "Pair: " << p1.first() << " " << p1.second() << endl;

const Pair1<double> p2(3.4, 7.8);
cout << "Pair: " << p2.first() << " " << p2.second() << endl;
//========================================================================================================================
cout << endl << "Task 2: " << endl;
Pair<int, double> pvar1(6, 7.8);
cout << "Pair: " << pvar1.first() << " " << pvar1.second() << endl;

Pair<double, int> pvar2(3.4, 5);
cout << "Pair: " << pvar2.first() << " " << pvar2.second() << endl;

//========================================================================================================================
cout << endl << "Task 3: " << endl;
StringValuePair<int> svp("Amazing", 7);
cout << "Pair: "  << svp.first() << ' ' << svp.second() << endl;

    return 0;
}