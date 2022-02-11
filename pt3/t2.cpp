/*
1. template swap function that takes two pointers and swaps only their addresses.
2. SortPointers template function that accepts vector of pointers and sorts them by values 
3. count vowels in War and Peace book. Use 4 different methods, display the calculation time.
*/

#include <cstdio>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <chrono>
#include <string_view>
#include "timer.h"

template <typename T>
void Swap(T* pointera, T* pointerb) 
{
    T temp = std::move(*pointera);
    *pointera = std::move(*pointerb);
    *pointerb = std::move(temp);
}

template <typename T>
void SortPointers(std::vector<T*>& plist)
{
    sort(plist.begin(), plist.end(), 
        [](const T* p1, const T* p2) -> bool
        {
            return *p1 < *p2;
        }
    );
}

template <typename T>
std::ostream& operator<<(std::ostream &out, std::vector<T*> &sample)
{
    for (const T* element : sample)
    {
        out << *element <<  " " ;
    }
    out << std::endl;
    return out;
}

int Search_countiffind(std::string_view& text, std::string& searchsample)
{
    return std::count_if(text.begin(), text.end(), [searchsample](char element)
    {
        return (find(searchsample.begin(), searchsample.end(), element) != searchsample.end());
    });
}

int Search_countiffor(std::string_view& text, std::string& searchsample)
{
    return std::count_if(text.begin(), text.end(), [searchsample](char element)
    {
        for (const char& lettr : searchsample)
        {
            if (element == lettr)
                return 1;
        }
        return 0;
    });
}

int Search_forfind(std::string_view& text, std::string& searchsample)
{
    int counter = 0;
    for(const char& lettr : text)
    {
        if (find(searchsample.begin(), searchsample.end(), lettr) != searchsample.end())
            counter++;
    }
    return counter;
}

int Search_forfor(std::string_view& text, std::string& searchsample)
{
    int counter = 0;
    bool marker;
    for (const char& textlettr : text)
    {
        marker = false;
        for (const char& samplelettr : searchsample)
        {
            if (textlettr == samplelettr)
                marker = true;
        }
        if (marker) counter++;
    }
    return counter;    
}

//////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    int m, n, f, g;
    std::cout << "input four numbers (divided by space) - ";
    std::cin >> m >> n >> f >> g;

    std::cout << "first = " << m << ", second = " << n << std::endl;
    Swap(&m,&n);
    std::cout << "first = " << m << ", second = " << n << std::endl;

    /////////////////////////////////////////////
    
    std::vector<int*> ingress;
    ingress.push_back(&m);
    ingress.push_back(&n);
    ingress.push_back(&f);
    ingress.push_back(&g);

    SortPointers(ingress);
    std::cout << "Sorting... " << ingress;

    /////////////////////////////////////////////

    std::string parseline;
    std::string parsedtext;
    std::string sample = "aeiouAEIOU";

    if (argc > 1)           
    {
        std::ifstream source(argv[1]);
        if (!source.is_open())
        {
            std::cerr << "file name invalid, exiting";
            exit(1);
        }
        else 
        {
            while (getline(source, parseline))
            {
                parsedtext.append(parseline);
            }
        }
    }
    else
    {
        std::cerr << "No file specified, skipping file reading test";
        exit(1);
    }
        
    std::string_view txt = parsedtext;
    std::cout << "total lines " << txt.size();

    Timer tr("\n countif > find ");
    Search_countiffind(txt, sample);
    tr.print();

    Timer tr2("\n countif > for ");
    Search_countiffor(txt,sample);
    tr2.print();

    Timer tr3("\n for > find ");
    Search_forfind(txt, sample);
    tr3.print();

    Timer tr4("\n for > for ");
    Search_forfor(txt, sample);
    tr4.print();

    return 0;
}