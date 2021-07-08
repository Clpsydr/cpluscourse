#include <iostream>
#include <cstdint>
#include <cmath>

using namespace std;

// TASK 1 classes

class Figure
{
    public:
        virtual float const Area() = 0;

        virtual ~Figure()
        {
            cout << "clean up of a base figure class..." << endl;
        }
};

class Parallelogram : public Figure
{
    private:
        float base;
        float height;
    public:
        Parallelogram(float b, float h) : base(b), height(h)
        {
            cout << "New parallelogram with base of " << b << " and height of " << h << endl;
        }

        float const getBase() 
        {
            return base;
        }

        float const getHeight() 
        {
            return height;
        }

        float const Area() override 
        {
            return base*height;
        }

        ~Parallelogram()
        {
        }
};

class Circle : public Figure
{
    private:
        float radius;
    public:
        Circle(float r) : radius(r)
        {
            cout << "New circle with radius of " << r << endl;
        }

        float const getRadius() 
        {
            return radius;
        }

        float const Area() 
        {
            return M_PI * pow(radius, 2);
        }

        ~Circle()
        {
        }
};

class Rectangle : public Parallelogram
{
    private:
    public:
        Rectangle(float base, float height) : Parallelogram(base,height)
        {
            cout << "New rectangle with base of " << base << " and height of " << height << endl;
        }

        ~Rectangle()
        {
        }
};

class Square : public Parallelogram
{
    private:
    public:
        Square(float a) : Parallelogram(a,a)
        {
            cout << "New square with a side of " << a << endl;
        }

        ~Square()
        {
        }
};

class Rhombus : public Parallelogram
{
    private:
    public:
        Rhombus(float b, float h) : Parallelogram(b,h)
        {
            cout << "New rhomubs with a base of " << b << " and height of " << h << endl;
        }

        ~Rhombus()
        {
        }
};

void const Printarea(Figure &f)                         // yay virtual functions with no overloading
{   
    cout << "Area of the figure - " << f.Area() << endl << endl;
}

// TASK 2 classes

class Car
{
    private:
        string company;
        string model;
    public:
        Car(string c, string m) : company(c), model(m)
        {
            cout << "car prototype created" << endl;
        }

        virtual ~Car()
        {
            cout << "car cleanup" << endl;
        }
};

class PassengerCar : virtual public Car
{
    private:
    public:
        PassengerCar(string c, string m) : Car(c,m)
        {
            cout << "Passenger car " << c << " " << m << " created" << endl;
        }

        ~PassengerCar()
        {
        }
};

class Bus : virtual public Car
{
    private:
    public:
        Bus(string c, string m) : Car(c,m)
        {
            cout << "Bus " << c << " " << m << " created" << endl;
        }

        ~Bus()
        {
        }
};

class Minivan : public PassengerCar, public Bus
{
    private:
    public:
        Minivan(string c, string m) : Car(c,m), PassengerCar(c,m), Bus(c,m)
        {
            cout << "Minivan " << c << " " << m << " created" << endl;
        }

        ~Minivan()
        {
        }
};

// TASK 3 classes

class Fraction
{
    private:
        int numerator;
        int denominator;
    public:                            
        Fraction(int n, int d) : 
        numerator( (d == 0) ? d : n), denominator( (d == 0) ? 1 : abs(d))               // attempt to regulate zero and negative values in denominator
        {
        }

        int getn() const
        {
            return numerator;
        }

        int getd() const
        {
            return denominator;
        }

        string const show()
        {
            return to_string(numerator) + "/" + to_string(denominator);
        }
};

Fraction operator*(const Fraction &f1, int multiplier)
{
    return Fraction(f1.getn() * multiplier, f1.getd());
}

Fraction operator+(const Fraction &f1, const Fraction &f2)
{
    return Fraction(f1.getn()*f2.getd()+f2.getn()*f1.getd(), f1.getd()*f2.getd());
}

Fraction operator-(const Fraction &f1, const Fraction &f2)
{
    return Fraction(f1.getn()*f2.getd()-f2.getn()*f1.getd(), f1.getd()*f2.getd());
}

Fraction operator-(const Fraction &f1)
{
    return Fraction(-f1.getn(), f1.getd());
}

Fraction operator*(const Fraction &f1, const Fraction &f2)
{
    return Fraction(f1.getn()*f2.getn(), f1.getd()*f2.getd());
}

Fraction operator/(const Fraction &f1, const Fraction &f2)
{
    return Fraction(f1.getn()*f2.getd(), f1.getd()*f2.getn());
}

bool operator==(const Fraction &f1, const Fraction &f2)     // to compare, we transform both fractions to common denominator and then compare resulting numerators
{
    return f1.getn() * f2.getd() == f2.getn() * f1.getd();
}

bool operator!=(const Fraction &f1, const Fraction &f2)
{
    return f1.getn() * f2.getd() == f2.getn() * f1.getd() ? false : true;
}

bool operator>(const Fraction &f1, const Fraction &f2)
{
    return ((f1.getn()*f2.getd()) > (f2.getn()* f1.getd())) ? true : false;
}

bool operator>=(const Fraction &f1, const Fraction &f2)
{
    return ((f1.getn()*f2.getd()) >= (f2.getn()* f1.getd())) ? true : false;
}

bool operator<=(const Fraction &f1, const Fraction &f2)
{
    return (f1 > f2) ? false : true;
}

bool operator<(const Fraction &f1, const Fraction &f2)
{
    return (f1 >= f2) ? false : true;
}

string strbool(bool b)
{
    return b ? "true" : "false";
}

// TASK 4 classes
enum cardsuit {hearts, spades, diamonds, clubs};
enum cardrank {ace=1, two=2, three=3, four=4, five=5, six=6, seven=7, eight=8, nine=9, ten=10, jack=10, king=10, queen=10};

class Card
{
    private:
        cardrank rank;
        cardsuit suit;
        bool istapped;
    public:
        void Flip() 
        {
            istapped = !istapped;
        }

        int Getvalue() const
        {
            return rank;
        }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
//========================================================================================================================
// making all figures as examples, and showing their area
cout << " *Task 1 output* " << endl << endl;
Parallelogram para1(15.2, 10);
Printarea(para1);
Circle circle1(5.02);
Printarea(circle1);
Square sqar1(9.123);
Printarea(sqar1);
Rectangle rect1(16,0.93);
Printarea(rect1);
Rhombus rho1(27, 43);
Printarea(rho1);

//========================================================================================================================
cout << " *Task 2 output* " << endl << endl;
PassengerCar car1("Nissan", "Sentra");
cout << endl;
Bus car2("Wrightbus", "Gemini");
cout << endl;
Minivan car3("Chrysler", "Pacifica");
cout << endl;

//========================================================================================================================
cout << " *Task 3 output* " << endl << endl;

Fraction fr1(5, 7);
Fraction fr1b(30,42);
Fraction fr2(1, 8);
Fraction fr2b(-10,15);
Fraction fr2c(-10,-15);
Fraction fr3(1,25);
Fraction fr4(6,13);
Fraction fr5(1,0);
cout << fr1.show() << " + " << fr2.show() << " = " << (fr1+fr2).show() << endl;
cout << fr2.show() << " - " << fr3.show() << " = " << (fr2-fr3).show() << endl;
cout << fr4.show() << " / " << fr2.show() << " = " << (fr4/fr2).show() << endl;
cout << fr2.show() << " < " << fr3.show() << " - " << strbool(fr2<fr3) << endl;
cout << fr4.show() << " >= " << fr1.show() << " - " << strbool(fr4>=fr1) << endl;
cout << fr1.show() << " == " << fr1b.show() << " - " << strbool(fr1==fr1b) << endl;
cout << "negative " << fr2.show() << " = " << (-fr2).show() << endl;
cout << "negative " << fr2b.show() << " = " << (-fr2b).show() << endl;
cout << "negative " << fr2c.show() << " = " << (-fr2c).show() << endl;
cout << "dividing by zero? " << fr5.show() << endl;

cout << endl << endl;

//========================================================================================================================
    return 0;
}