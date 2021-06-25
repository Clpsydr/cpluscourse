#include <iostream>
#include <cstdint>
#include <math.h>

using namespace std;

// var replace for quick changes in t1 and t3
#define NUMONE 1.25
#define NUMTWO 3.12
#define STACKLENGTH 10

class Power                             // exponent class
{
    private:
        float base;
        float power;

    public:
        void Set(float a, float b)
        {
            base = a;
            power = b;
        }

        float Calculate()
        {
            return pow(base,power);
        }
};

class RGBA                              // color class
{
    private:
        uint8_t m_red =    0;
        uint8_t m_green =  0;
        uint8_t m_blue =   0;
        uint8_t m_alpha =  255;

    public:
        RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
        m_red(r), m_green(g), m_blue(b), m_alpha(a)
        {
        }

        void Print()
        {
            printf("color is (%d %d %d %d) \n", m_red, m_green, m_blue, m_alpha);           //looks like cout displays uint8 as char, had to switch to printf here
        }
};

class Stack                                 // stack class
{
    private:
        int values[STACKLENGTH];
        int length;

    public:
        void Reset()
        {
            length = 0;
            for (int i = 0; i<STACKLENGTH; i++)
            {
                values[i] = 0;
            }
        }

        void Push(int a)
        {
            if (length+1 < STACKLENGTH)
            {
                values[length] = a;
                length++;
            }
            else 
                cout << "Stack is full! \n";
        }

        void Pop()
        {
            if (length > 0)
            {
                values[length] = 0;
                length--;
            }
            else
                cout << "Stack is empty \n";
        }

        void Print()
        {
            cout << "Array values: ( ";
            for (int i = 0; i<length; i++)
            {
                cout << values[i] << " ";
            }
            cout << ")" << endl;
        }
};

////////////////////////////////// 

int main()
{
//========================================================================================================================
Power newnumber;
newnumber.Set(NUMONE, NUMTWO);
cout << "T2.1.1  Power calculation" << endl;
cout << "for " << NUMONE << " in power of " << NUMTWO << ", result is " << newnumber.Calculate() << endl;

//========================================================================================================================
cout << "\nT2.1.2  Color class" << endl;
RGBA newcolor(125,125,0,255);
newcolor.Print();

//========================================================================================================================
cout << "\nT2.1.3  Stack class operations" << endl;
Stack newstack;
newstack.Reset();
newstack.Print();
    newstack.Push(3);
    newstack.Push(7);
    newstack.Push(5);
newstack.Print();
    newstack.Pop();
newstack.Print();
    newstack.Pop();
    newstack.Pop();
newstack.Print();
//========================================================================================================================
    return 0;
}