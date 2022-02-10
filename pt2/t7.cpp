/*
1. Date() class, with overloaded output, has 2 smartpointers Today and Date swapping their data. They should check for nullptr.
2. Date() comparison algorithm that returns later date. Function that exchanges data in two smart pointers passed as parameters.
*/
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <memory>

using namespace std;

enum months {january, february, march, april, may, june, july, august, september, october, november, december};


class Date
{
    friend ostream& operator<< (ostream &out, Date &date);
    const string monthtxt[12] {"january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"};

    private:
        unsigned short int day;
        months month;
        unsigned int year;
    public:
        Date(unsigned short int d, months m, unsigned int y) : day(d), month(m), year(y)
        {

            cout << "date created" << endl;
            //there should be some crazy check for maximum amount of days in certain year
        }

        Date()
        {
            cout << "empty date created" << endl;
        }

        ~Date()
        {
            cout << "date removed" << endl;
        }

        unsigned short int getDay() const
        {
            return day;
        }

        string getMonth() const
        {
            return monthtxt[month];
        }

        months getDMonth() const
        {
            return month;
        }

        unsigned int getYear() const
        {
            return year;
        }

        int GetTotalDays() const
        {
            return year * 365 + (month+1) * day;
        }

        void setDate(unsigned short int nd, months nm, unsigned int ny)
        {
            day = nd;
            month = nm;
            year = ny;
        }
};

template<typename T>
void cautiousPrint(unique_ptr<T>& ptr)
{
    if (ptr)
        cout << "pointer is not empty: " << *ptr;
    else
        cout << "pointer is empty" << endl;
}

void pointerSwap(unique_ptr<Date>& a_ptr, unique_ptr<Date>& b_ptr)                      // data exchange between pointers
{
    if (a_ptr && b_ptr)
    {
        unique_ptr<Date> temp = make_unique<Date>();

        temp->setDate(b_ptr->getDay(), b_ptr->getDMonth(), b_ptr->getYear());
        b_ptr->setDate(a_ptr->getDay(), a_ptr->getDMonth(), a_ptr->getYear());
        a_ptr->setDate(temp->getDay(), temp->getDMonth(), temp->getYear());
        temp = move(nullptr);
    }
    else 
        cout << "one or more pointers are null" << endl;
}

ostream& operator<< (ostream &out, Date &date)                         
{
    out << date.getDay() << " " << date.getMonth() << ", " << date.getYear() << endl;
    return out;
}

Date& CompareTimes(Date &a_date, Date &b_date)
{
    if (a_date.GetTotalDays() > b_date.GetTotalDays())
        return a_date;
    else if (a_date.GetTotalDays() < b_date.GetTotalDays())
        return b_date;
    else
    {
        cout << "dates are equal" << endl;
        return b_date;
    }
        
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
//========================================================================================================================
unique_ptr<Date> today = make_unique<Date>(21, july, 2021);
unique_ptr<Date> date = make_unique<Date>();
cautiousPrint(today);
cautiousPrint(date);

cout << endl << "moving pointers" << endl;
date = move(today);

cautiousPrint(today);
cautiousPrint(date);
//========================================================================================================================
unique_ptr<Date> date1 = make_unique<Date>(31,january, 1989);
unique_ptr<Date> date2 = make_unique<Date>(18, january,1989);
cautiousPrint(date1);
cautiousPrint(date2);

cout << endl << "figuring out a later date...  " << CompareTimes(*date1, *date2);

cautiousPrint(date1);
cautiousPrint(date2);

cout << endl << "also swapping Date1 and Date, attempting to access today as well" << endl;
pointerSwap(date1, today);
pointerSwap(date1, date);

cautiousPrint(date1);
cautiousPrint(date);

    return 0;
}