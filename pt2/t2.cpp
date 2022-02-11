/*
1. Class Person with name, age, gender and weight parameters.  Student is an inherited class with extra parameter. In main() several students are created and printed.
2. Classes Apple() and Banana() inhertied from Fruit(), that contains name and color atritbutes. Extra class that inhertis from Apple().
*/

#include <iostream>
#include <cstdint>
#include <math.h>
#include <sstream>

using namespace std;

#define CLASSSIZE 30                                                                // Classroom is limited in size
enum genders {unspecified, male, female};
static const char * Gendstrings[] = {"unspecified" , "male", "female"};             
    
class Person                                                                        // base human class
{
    private: 
        string name = "no name";
        int age = 0;
        genders gender = unspecified;
        float weight = 0;

    public:
        Person()
        {
            cout << " - blank person created" << endl;
        }

        Person(string newname, int newage, genders g, float newweight)
        {
            name = newname;
            age = newage;
            gender = g;
            weight = newweight;
            cout << " - specific person created" << endl;
        }

        string getName() const
        {
            return name;
        }

        genders getGender() const
        {
            return gender;
        }

        float getWeight() const
        {
            return weight;
        }

        float getAge() const
        {
            return age;
        }

        void setName(string a)
        {
            name = a;
        }

        void setAge(int a)
        {
            age = a;   
        }

        void setGender(genders a)
        {
            gender = a;
        }

        void setWeight(float a)
        {
            weight = a;
        }
};

class Student : public Person                                                           // student class
{
    private:
        static int count;
        int studyYear;

    public:
        Student()
        {
            count ++;
            checkstudents();
        }

        Student(string newname, int newage, genders g, float newweight, int newyear) :
            studyYear(newyear), Person(newname, newage, g, newweight)
        {
            count ++;
            checkstudents();
        }

        int static getCount() 
        {
            return count;
        }

        void const checkstudents()
        {
            cout << " total students : " << getCount() << endl;
        }

        int const getYear()
        {
            return studyYear;
        }

        void AdvanceYear(int n)
        {
            studyYear += n;
        }

        void setYear(int n)
        {
            studyYear = n;
        }
};

int Student::count = 0;                     // Static student counter

class Classroom                             // Class for keeping track of students 
{
    private:
        Student* students[CLASSSIZE];
        int population;                 // still have to use separate counter, to avoid being able to add students only after their immediate creation

    public:
        Classroom()
        {
            population = 0;
            cout << "new classroom has been made " << endl;
        }

        void addtoaClass(Student *newstudent)
        {
            students[population] = newstudent;
            population ++;
        }

        string searchStudent(string searchline)
        {
            if (population != 0)
            {
                for (int i = 0 ; i < population; i++)
                {
                    Student j = *students[i];
                    if (j.getName() == searchline)
                    {
                        stringstream stream;
                        stream << "student found, its " << j.getName() << ": " << Gendstrings[j.getGender()] << ", " << j.getAge() <<  " years, " << j.getWeight() << " kg.";
                        return stream.str();  
                    }
                }
                
                return "didnt find such a student";
            }
            else
                return "classroom is currently empty";
        }
};


class Fruit
{
    private:
        string name;
        string color;
    public:
        Fruit(string n, string c) : name(n), color(c)
        {
        }

        string const getColor()
        {
            return color;
        }

        string const getName()
        {
            return name;
        }

        void setColor(string col)
        {
            color = col;
        }

        void setName(string n)
        {
            name = n;
        }
};

class Apple : public Fruit
{
    private:
    public:
        Apple(string c) : Fruit("apple", c)
        {
        }

        Apple(string n, string c) : Fruit(n,c)
        {
        }

};

class Banana : public Fruit
{
    private:
    public:
        Banana() : Fruit("banana", "yellow")
        {
        }
};

class GrannySmith : public Apple
{
    private:
    public:
        GrannySmith() : Apple("Granny Smith", "green")
        {
        }
};

int main()
{
//========================================================================================================================
Classroom classroom;         // feels extremely redundant , but its easier for the sake of searching
string searchline;

Student newstudent1("Shestakov", 37, male, 70, 2009);
Student newstudent2("Ivanov", 25, male, 73, 2015);
Student newstudent3("Petrova", 26, female, 60, 2017);
Student newstudent4("Sidorov", 30, male, 80, 2012);

classroom.addtoaClass(&newstudent1);
classroom.addtoaClass(&newstudent2);
classroom.addtoaClass(&newstudent3);
classroom.addtoaClass(&newstudent4);

cout << "Searching for a student by name: ";
cin >> searchline;
cout << classroom.searchStudent(searchline) << endl;
cout << "Searching for a student by name: ";
cin >> searchline;
cout << classroom.searchStudent(searchline) << endl;

//========================================================================================================================
Apple a("red");
Banana b;
GrannySmith c;

cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    return 0;
}
