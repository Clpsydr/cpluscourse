#include <iostream>

#define SwapINT(a, b) temp = a; a = b; b = temp;
#define SwapINT2(a, b) swap(a,b);

namespace ArrayWorks
{
    void ArrayMake(double* arr, int size, int limit)
    {
        for (int i = 0; i < size; i++)
        {
            arr[i] = rand()%limit + static_cast<float>(rand()%10000)/10000;
        }
    }

    void ArrayDisplay(double arr[], int size)
    {
        std::cout << "\n";
        for (int i = 0; i < size; i++)
        {
            std::cout << arr[i] << " ";
        }
    }
    
    void ArrayDisplay(int arr[], int size)
    {
        std::cout << "\n";
        for (int i = 0; i < size; i++)
        {
            std::cout << arr[i] << " ";
        }
    }

    int Divide(int arr[], int start, int end)           //complementary sorting operation
    {
        int temp, marker = start;

        for (int index = start; index <= end; index++)
        {
            if(arr[index] < arr[end])
            {
                
                SwapINT(arr[marker], arr[index]);
                marker++;
            }
        }

        SwapINT(arr[marker], arr[end]);
        return marker;
    }

    void ArraySort(int arr[], int start, int end)       // attempt at fastsorting
    {
        if (start >= end) return;

        int basepoint = Divide(arr, start, end);
        ArraySort(arr, start, basepoint-1);
        ArraySort(arr, basepoint+1, end);
    }
}