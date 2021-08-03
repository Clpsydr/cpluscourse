#include <cstdio>
#include <iostream>
#include <math.h>

template <typename T, typename N>
T Div(T a, N b)
{
    if (a == 0)
        throw "Division by zero, can't divide!!!";
    std::cout << "Result of division ";
    return a/b;
}

class Ex
{
    private:
        float x;
    public:
        Ex(float newx) : x(newx)
        {
        }

        ~Ex()
        {}

        float Get() const
        {
            return x;
        }
};

class MovementErr
{
    public:
        MovementErr(int a, int b, int pa, int pb) : dirx(a), diry(b), posx(pa), posy(pb)
        {
        }

        std::string GetErr() const
        {
            return "ERROR : unexpected movement error \n";
        }
    protected:
        int dirx;
        int diry;
        int posx;
        int posy;
};

class IllegalCommand : public MovementErr
{
    private:
    public:
        IllegalCommand(int a, int b, int pa, int pb) : MovementErr(a,b,pa,pb)
        {

        }

        ~IllegalCommand()
        {}

        std::string GetErr() const
        {
            return "ERROR : incorrect input - moving by " + std::to_string(dirx) + ", " + std::to_string(diry) +
                " from " + std::to_string(posx) + " " + std::to_string(posy) + "\n";
        }
};

class OffTheField : public MovementErr
{
    private:
    public:
        OffTheField(int a, int b, int pa, int pb) : MovementErr(a,b,pa,pb)
        {}

        ~OffTheField()
        {}

        std::string GetErr() const
        {
            return  "ERROR : attempt to move to " + std::to_string(dirx) + ", " + std::to_string(diry) + " with a move (" +
                std::to_string(posx) + " " + std::to_string(posy) + ")\n";
        }
};

class Bar
{
    private:
        float y;
    public:
        Bar()
        {
            y = 0;
        }

        void set(float a)
        {
            if ((y + a) > 100)
                throw Ex(a*y);
            else
            {
                y = a;
                std::cout << "value assigned to " << y << std::endl; 
            }
        }
};

class Robot
{
    private:
        int x_pos;
        int y_pos;
    public:
        Robot()
        {
            x_pos = 5;
            y_pos = 5;
        }

        const std::string getcoords()
        {
            return std::to_string(x_pos) + " " + std::to_string(y_pos) ;
        }


        void Move(int dirx, int diry)
        {
            if (dirx > 1 || diry > 1 || dirx < -1 || diry < -1)
                throw IllegalCommand(dirx, diry, x_pos, y_pos);
            if (x_pos + dirx > 10 || x_pos + dirx < 1 || y_pos + diry > 10 || y_pos + diry < 1)
                throw OffTheField(x_pos+dirx, y_pos+diry, dirx, diry);
            x_pos += dirx;
            y_pos += diry;
        }

        bool atDestination(int destx, int desty)
        {
            return (destx == x_pos && desty == y_pos);
        }
};

int main()
{
////////////////////////////////
    std::cout << "1. Division task." << std::endl;
    int avar;
    float bvar;
    try 
    {
        std::cout << "Enter first number: ";
        std::cin >> avar;
        std::cout << "Enter second number: ";
        std::cin >> bvar;
        std::cout << Div(avar,bvar);
    }
    catch(const char* DivisionByZero)
    {
        std::cerr << DivisionByZero;
    }

////////////////////////////////

    std::cout << std::endl << "2. Exception class" << std::endl;
    int i_input = 1;
    Bar exceptioning;
    while(i_input !=0)
    {
        try
        {
            std::cout << "Enter any integer, 0 to quit: ";
            std::cin >> i_input;
            exceptioning.set(i_input);
        }
        catch(Ex Err)
        {
            std::cerr << "thats an excessive value, multiplication - " << Err.Get() << std::endl;
        }
    }

////////////////////////////////
    std::cout << std::endl << "3. Robot movement" << std::endl;
    std::cout << "to exit, move to 2,2 coordinates" << std::endl;
    Robot rob1;
    int goalx = 2;
    int goaly = 2;
    int x_input, y_input;
    while (true)
    {
        try
        {
            std::cout << "Robot is at " << rob1.getcoords() << std::endl;
            std::cout << "Enter new direction (in \"x y\" format, with coordinates ranging from -1 to 1) ";
            std::cin >> x_input;
            std::cin >> y_input;
            rob1.Move(x_input, y_input);
            if (rob1.atDestination(goalx,goaly))
            {
                std::cout << "Found exit";
                exit(1);
            }
        }
        catch(OffTheField &RobotNurse)          // could be nice if I didn't have to set an order of errors to catch
        {
            std::cout << RobotNurse.GetErr();
        }
        catch(IllegalCommand &RobotNurse) 
        {
            std::cout << RobotNurse.GetErr();
        }
        catch(MovementErr &RobotNurse)
        {
            std::cout << RobotNurse.GetErr();
        }
    }
    return 0;
}