/*
1. Class with two floats and two methods, one sets float values, another displays f1 in power of f2
2. Class RGBA with uin8_t values for each color attribute. Default constructor assigning values. Method that displays their values.
3. Class with a stack functionality. Contains private 10size Array of integeres, private value that returns size, also methods reset(), push(), pop(), print().
*/

#include <iostream>
#include <cstdint>
#include <math.h>

using namespace std;

// No manual input in runtime
// variables replace for quick changes in t1 and t3
#define NUMONE 1.25
#define NUMTWO 3.12
#define STACKLENGTH 10

class Power                             // Power class
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

class RGBA                              // Color property class
{
    private:
        uint8_t m_red =    0;
        uint8_t m_green =  0;
        uint8_t m_blue =   0;
        uint8_t m_alpha =  255;

    public:
        RGBA() // default constructor without arguments
        {
            cout << " - blank color allocated" << endl;
        }       

        RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
        m_red(r), m_green(g), m_blue(b), m_alpha(a)
        {
            cout << " - specific color allocated" << endl;
        }

        void Print()
        {
            cout << "color is (" << unsigned(m_red) << " " << unsigned(m_green) << " " << unsigned(m_blue) << " " << unsigned(m_alpha) << ")" << endl;
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
RGBA newcolor2;
newcolor2.Print();

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