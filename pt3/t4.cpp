#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <iterator>
#include <cmath>

int32_t getRandomNum(int32_t min, int32_t max)
{
    const static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937_64 generator(seed);
    std::uniform_int_distribution<int32_t> dis(min,max);
    return dis(generator);
}

template <class Container>
void display(Container& in_array)
{
    using element_type = typename Container::value_type;
    std::for_each(in_array.begin(), in_array.end(), [](element_type i){std::cout << i << ", ";});
    std::cout << "\b\b " << std::endl;
}

template <typename T, class Container>
void insert_sorted(Container& in_array, T newvalue)
{
    in_array.emplace(lower_bound(in_array.begin(), in_array.end(), newvalue), newvalue);
}

float ErrorMargin(std::vector<float> Vreal, std::vector<int> Vdigit)
{
    float difference = 0;
    return inner_product(Vreal.begin(), Vreal.end(), Vdigit.begin(), difference, [](float a, float b){return a+b;}, [](float a, int b){return (a-b)*(a-b); });
}


int main()
{
    int ins1 = getRandomNum(1,400);
    std::vector<int> firstline(15);
    generate(firstline.begin(), firstline.end(), [](){return getRandomNum(1,400);});
    std::sort(firstline.begin(), firstline.end());
    
    std::cout << std::endl << "-- Vector of integers --" << std::endl ;
    display(firstline);

    insert_sorted(firstline, ins1);
    std::cout << "adding a " << ins1 << std::endl;
    display(firstline);

/////
    char ins2 = getRandomNum(33,126);
    std::deque<char> secondline(13);
    generate(secondline.begin(), secondline.end(), [](){return getRandomNum(33,126);});
    std::sort(secondline.begin(), secondline.end());

    std::cout << std::endl << "-- Deque of characters --" << std::endl ;
    display(secondline);

    insert_sorted(secondline, ins2);
    std::cout << "adding a " << ins2 << std::endl;
    display(secondline);
/////
    float ins3 = getRandomNum(1,3) + 0.01 * getRandomNum(1,100);
    std::list<float> thirdline(15);
    std::generate(thirdline.begin(), thirdline.end(), [](){return getRandomNum(1,3) + 0.01 * getRandomNum(1,100);});
    thirdline.sort();

    std::cout << std::endl << "-- List of floats --" << std::endl;
    display(thirdline);

    insert_sorted(thirdline, ins3);
    std::cout << "adding a " << ins3 << std::endl;
    display(thirdline);

/////////////////
    std::vector<float> waveform(100);
    std::vector<int> digitized(100);
    float ctr = 0;
    generate(waveform.begin(), waveform.end(),[](){return sin(0.00002*getRandomNum(0,314159));});

    std::cout << std::endl << "Second part. Generating a new waveform. " << std::endl;
    display(waveform);

    transform(waveform.begin(), waveform.end(), digitized.begin(), [](float i){
        return round(i);
    });
    std::cout << std::endl << "Digitized version - " << std::endl;
    display(digitized);

    std::cout << std::endl << "total error according to formula is " << ErrorMargin(waveform, digitized);
    return 0;
}
