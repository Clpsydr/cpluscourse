#include <iostream>
#include <cstdint>
#include <ctime>
#include <cassert>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

#define SAMPLESIZE 15
#define RANDSPAN 150
#define RANDSPAN2 10

class ArrayInt
{
    private:
        int m_length;
        int *m_data;

        void Qsort(int* dataset, int start, int end)
        {
            if (start < end)
            {
                int anchor = Divide(dataset, start, end);
                
                Qsort(dataset, start, anchor-1);
                Qsort(dataset, anchor+1, end);
            }
        }

        int Divide(int* data, int start, int end)
        {
            int temp = 0;
            int anchor = data[end];
            int i = start - 1;

            for(int j = start; j <= end - 1; j++)
            {
                if(data[j] < anchor)
                {
                    i++;
                    temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
            }
            temp = data[i+1];
            data[i+1] = data[end];
            data[end] = temp;
            return i+1;
        }
    public:
        ArrayInt() : m_length(0), m_data(nullptr)
        {
        }

        ArrayInt(int length) : m_length(length)
        {
            assert(length >- 0);

            if (length > 0)
                m_data = new int[length];
            else
                m_data = nullptr;
        }

        ~ArrayInt()
        {
            delete[] m_data;
        }

        void Erase()
        {
            delete[] m_data;
            m_data = nullptr;
            m_length = 0;
        }

        int getLength() const
        {
            return m_length;
        }

        int& operator[] (int index)
        {
            assert(index >= 0 && index < m_length);
            return m_data[index];
        }

        void resize(int newlength)
        {
            if (newlength == m_length)
                return;
            
            if (newlength < 0)
            {
                Erase();
                return;
            }

            int *data = new int[newlength];
            if (m_length > 0)
            {
                int eletarget = newlength > m_length ? m_length : newlength;
                for (int i = 0; i < eletarget; i++)
                {
                    data[i] = m_data[i];
                }
            }

            delete[] m_data;
            m_data = data;
            m_length = newlength;
        }

        void insertBefore(int value, int index)
        {
            assert (index > 0 && index < m_length);

            int *data = new int[m_length + 1];
            for (int i = 0; i < index; i++)
                data[i] = m_data[i];
            data[index] = value;
            for (int i = index; i < m_length; i++)
                data[i + 1] = m_data[i];

            delete[] m_data;
            m_data = data;
            ++m_length;
        }

        void pushBack(int value)
        {
            insertBefore(value, m_length);
           
        }

        void popBack()
        {
            resize(m_length-1);
        }

        void popFront()
        {
            assert(m_length > 0);

            int *data = new int[m_length-1];
            if (m_length > 0)
            {
                for (int i = 0; i < m_length-1; i++)
                {
                    data[i] = m_data[i+1];
                }
            }

            delete[] m_data;
            m_data = data;
            m_length--;
        }

        void Sort()
        {
            assert(m_length > 1);

            Qsort(m_data, 0, m_length-1);
        }

        void Display()
        {
            cout << "current index status: " << endl;
            for (int i = 0; i < m_length; i++)
            {
                cout << " " << m_data[i];
                if (i < m_length-1)
                    cout  << ",";
            }
            cout << endl;
        }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VecDisplay(vector<int> &samplevec)
{
    cout << "Vector is: ";
    for (int i = 0; i < samplevec.size(); i++)
        cout << samplevec[i] << " ";

    cout << endl;
}

int DetectDupes(vector<int> &samplevec)                        // I used builtin library sorting instead of writing a function again
                                                                // But AFAIK it works like quicksort + heapsort, which makes it unstable but fairly efficient
                                                                // with overall worst case of O(N*log(N))
{
    int diffcases = 0;
    int example;

    vector<int> dupevector = samplevec;

    sort(dupevector.begin(), dupevector.end(), less<int>());
    for (int i = 0; i < dupevector.size(); i++)
    {
        if(example != dupevector[i])
        {
            diffcases++;
            example = dupevector[i];
        }
    }

    return diffcases;
}


//BLACK JACK CLASSES        
//sorry for now I just copied previous task classes instead of making external library for them
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
        vector<Card> deck;
    public:
        Hand()
        {
        }

        ~Hand()
        {
        }

        void Add(Card &newcard)
        {
            deck.push_back(newcard);
        }

        void Clear()
        {
            deck.clear();
        }

        int Count()
        {
           return deck.size();
        }

        int getValue() const                    // So, I assume that we only need 11 point Ace for cases where extra points would let us win (ie closer to 21)
        {
            bool hasAce = false;                        // doesnt matter how many aces we have, since even 2 aces is 22 points.
            int tempvalue = 0 ;
            for (int i = 0; i < deck.size(); i++)
            {
                if (deck[i].Getvalue() == 1)
                    hasAce = true;
                tempvalue += deck[i].Getvalue();
            }
            if ((hasAce) && tempvalue < 12)             // only adding for safe situations
                tempvalue += 10;                        

            return tempvalue;
        }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
srand(static_cast<unsigned int>(time(0)));
//========================================================================================================================

cout << "Task 4.1, custom container operations: " << endl;
ArrayInt newarray(SAMPLESIZE);
for (int i = 0; i < newarray.getLength(); i++)
    newarray[i] = rand()%RANDSPAN;
newarray.Display();

newarray.popBack();
newarray.Display();
newarray.resize(20);
newarray.Display();
newarray.popFront();
newarray.Display();
newarray.Sort();
newarray.Display();
//========================================================================================================================

cout << endl << "Task 4.2, dupes in vector container: " << endl;
vector<int>Record;
for (int i = 0; i < SAMPLESIZE; i++)
    Record.push_back(rand()%RANDSPAN2);
VecDisplay(Record);
cout << "total different elements " << DetectDupes(Record) << endl;

//========================================================================================================================

cout << endl << "Task 4.3, checking deck functionality: " << endl;
Hand playershand;
Card crd(ace, spades);                  // Im not sure how to directly add them into hand, without declaring spearately like this
Card crd2(three, clubs);
Card crd3(queen, hearts);
Card crd4(jack, clubs);
playershand.Add(crd);
cout << "current hand ( " << playershand.Count() << " cards) worth " << playershand.getValue() << endl;
playershand.Add(crd2);
cout << "current hand ( " << playershand.Count() << " cards) worth " << playershand.getValue() << endl;
playershand.Add(crd3);
cout << "current hand ( " << playershand.Count() << " cards) worth " << playershand.getValue() << endl;

cout << "removing the hand" << endl;
playershand.Clear();
playershand.Add(crd);
playershand.Add(crd4);
cout << "current hand ( " << playershand.Count() << " cards) worth " << playershand.getValue() << endl;

    return 0;
}