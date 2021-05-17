#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector> //forgive me, master, I have to go all out just this time

using namespace std;

const int SIZE = 5;
const int SIZELARGER = 15;

const int THIRDTASKSIZE = 8;

////////////////////////////////////////////// sort of array assignment, with floatpoint imitation
void arraygen(double* arr, int size)
{
    for (int i = 0; i<size; i++)
        arr[i] = rand()%500 + static_cast<float>(rand()%10000)/10000;
}

////////////////////////////////////////////// smaller scale array generation with controlled size
void arraygen(int* arr, int size, int limits)
{
    for (int i = 0; i<size; i++)
        arr[i] = rand()%limits;
}

////////////////////////////////////////////// display an array in question
void arrayload(double* arr, int size)
{
    cout << "\n following array is loaded: ";
    for (int i = 0; i<size; i++)
        cout << *(arr+i) << " " ;
}

////////////////////////////////////////////// display bool arrays, overloaded (I guess?)
void arrayload(bool* arr, int size)
{
    cout << "\n following array is loaded: ";
    for (int i = 0; i<size; i++)
        cout << *(arr+i) << " " ;
}

////////////////////////////////////////////// display int arrays
void arrayload(int* arr, int size)
{
    cout << "\n following array is loaded: ";
    for (int i = 0; i<size; i++)
        cout << *(arr+i) << " " ;
}

////////////////////////////////////////////// flip function for task 5-2
void arrayswap(bool* arr, int size)
{
    for (int i = 0; i<size; i++)
        arr[i] = !arr[i];
}

////////////////////////////////////////////// generation function for task 5-3
void arrayintfill(int* arr)
{
    for (int i = 0; i<THIRDTASKSIZE; i++)
        arr[i] = 1 + 3*i;
}

////////////////////////////////////////////// shifting function for task 5-4
void arrayshift(int* arr, int size, int shift)
{
    int arr2[size];  //temporal array
    for (int i=0;i<size;i++) //this happens because I don't know how to merely duplicate the array
        arr2[i] = arr[i];

    int actualshift = shift % size;  //skipping shifts that would just return the array into its initial state
    cout << "\n shifting for " << actualshift << " positions \n";

    //conditions vary depending on whether shift is left or right directional
    if (shift > 0)
    {
        for (int i = 0; i<size; i++)
        {
            if ((i + actualshift) >= size)
                arr[(i + actualshift) - size] = arr2[i];
            else
                arr[i + actualshift] = arr2[i];
        }
    }
    else
    {
        for (int i = 0; i<size; i++)
        {
            if ((i + actualshift) < 0)
                arr[size + (i + actualshift)] = arr2[i];
            else
                arr[i + actualshift] = arr2[i];
        }
    }
}

////////////////////////////////////////////// subfunction that returns sum of a part of the array (for 5-5)
int sum(int* arr, int start, int finish)
{
    int sum = 0;
    for (int i = start; i <= finish; i++)
        sum += arr[i];

    return sum;
}

////////////////////////////////////////////// main function for task 5-5 checking function
void arraycomparison(int* arr, int size)
{
    vector<int> journal;  //dynamic array to store division encounters because its easier

    for (int i = 0; i<size; i++)
        if (sum(arr, 0, i) == sum(arr, i+1, size-1))
            journal.push_back(i);

    if (journal.size() == 0)
    {
        arrayload(arr, size);
        cout << "\n no matches found. ";
    }
    else
        for (int i = 0; i<journal.size(); i++)
        {
            cout << "\n Encounter " << i+1 << ": ";
            for (int j = 0; j<size; j++)
            {
                cout << arr[j] << " ";
                if (journal[i] == j)
                    cout << " || ";
            }
        }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
srand(static_cast<unsigned int>(time(0)));

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   #5.1
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
        double firstarray[SIZE] = {0};
        double secondarray[SIZELARGER] = {0};


        cout << "Task 5-1. Testing function for array display. ";
        arraygen(firstarray, SIZE);
        arrayload(firstarray, SIZE);

        cout << "\n Remaking second array ... ";
        arraygen(secondarray, SIZELARGER);
        arrayload(secondarray, SIZELARGER);
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   #5.2
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
        bool bitarray[SIZE] = {0,1,0,1,1};

        cout << "\n\n Task 5-2. Inverting bit array";
        arrayload(bitarray, SIZE);
        arrayswap(bitarray, SIZE);
        cout << "\n inverted version: ";
        arrayload(bitarray, SIZE);
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   #5.3
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
        int intarray[THIRDTASKSIZE] = {0};

        cout << "\n\n Task 5-3. Filling array with int values";
        arrayintfill(intarray);
        arrayload(intarray, THIRDTASKSIZE);


    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   #5.4
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
        int intarrayplus[SIZELARGER] = {};
        for (int i=0; i<SIZELARGER; i++)
            intarrayplus[i] = i+1;

        int shiftvalue;

        cout << "\n\n Task 5-4. Enter how many positions to shift (positive to right, negative - to left): ";
        cin >> shiftvalue;

        arrayload(intarrayplus, SIZELARGER);
        arrayshift(intarrayplus, SIZELARGER, shiftvalue);
        arrayload(intarrayplus, SIZELARGER);
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   #5.5
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
            int dividearray[SIZE] = {9,3,1,6,7};
            int dividearray2[SIZE] = {18,4,-6,2,18};
            int dividearray3[SIZE] = {0,0,0,0,0};
            int dividearray4[SIZE] = {5,2,12,1,0};
            
            cout << "\n\n Task 5-5. Analyzing the arrays... ";
            cout << "\n Looking for wings with equal sum in the first array:  ";
            arraycomparison(dividearray, SIZE);
            
            cout << "\n\n Retrying a different array: ";
            arraycomparison(dividearray2, SIZE);

            cout << "\n\n Retrying again";
            arraycomparison(dividearray3, SIZE);

            cout << "\n\n Retrying again!";
            arraycomparison(dividearray4, SIZE);
    }

    return 0;
}