#include <iostream>
#include <cstdlib>
#include <ctime>
#include "sevenlib.h"
#include <fstream>

#define WithinBounds(a, b) ((a>=0)&&(a<b)) ? " >> true <<" : " >> false <<"         
#define SORTEDARRAYSIZE 10

using namespace std;    
using namespace ArrayWorks;     // calling namespace from the library

#pragma pack(push, 1)       //compressed structure
    struct Employee
    {
        string name;
        string department;
        int position;
        long int ID;
        size_t salary;
    };
#pragma pack(pop)

const int ARRSIZE = 9;

int main()
{
    srand(static_cast<unsigned int>(time(0)));
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   #7.1 (7.5)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    double newarray[ARRSIZE] = {};
    cout << "7.1. Displaying random array, but through a function in its own namespace!";
    ArrayMake(newarray, ARRSIZE, 600);
    ArrayDisplay(newarray, ARRSIZE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   #7.2
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    int a, b;
    cout << "\n 7.2. Lets enter the first positive number  ";
    cin >> a;

    cout << "\n Enter containing number too   ";
    cin >> b;
    
    cout << (WithinBounds(a,b));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   #7.3
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    int newarray[SORTEDARRAYSIZE];

    cout << "\n 7.3. Sorting an array";
    for (int i = 0; i < SORTEDARRAYSIZE; i++)
    {
        cout << "element [" << i+1 << "] ";
        cin >> newarray[i];
    }
    ArrayDisplay(newarray, SORTEDARRAYSIZE);
    
    cout << "\n now sorting...";
    
    ArraySort(newarray, 0, SORTEDARRAYSIZE-1);

    cout << "\n sorting finished...";

    ArrayDisplay(newarray, SORTEDARRAYSIZE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   #7.4
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
    Employee* somedude = new (nothrow) Employee;
    if (somedude == nullptr)
        cout << "memory allocation failed";
    else
    {
        somedude->ID = 291891;
        somedude->name = "Dmitry Shestakov";
        somedude->department = "IT";
        somedude->position = 5;
        somedude->salary = 250;
    }

    cout << "\n 7.4. compacted structure" ;
    cout << "\nID: " << somedude->ID << ", name: " << somedude->name << ", salary: " << somedude->salary << ", department: " << somedude->department;
    cout << "\n this compacted employee should take about " << sizeof(somedude) << " bytes \n";
    cout << "\n however this is just a pointer. The written structure would take " << (sizeof(somedude->ID) +sizeof(somedude->name) +sizeof(somedude->department) +sizeof(somedude->position) +sizeof(somedude->salary)) << " bytes";
    

    ofstream writestream("me.txt"); 
    writestream << "ID: " << somedude->ID << "\n";
    writestream << "name: " << somedude->name << "\n";
    writestream << "works in: " << somedude->department << "\n";
    writestream << "rank: " << somedude->position << "\n";
    writestream << "salary: " << somedude->salary << " dollers \n";

    writestream.close();

    cout << "\n file should be written now as me.txt"; 

    delete somedude;
}



    return 0;
}