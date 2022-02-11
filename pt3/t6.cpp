/* Task 6 - parallel computing basics
1. cout wrapper safe for parallel use.
2. function that returns Nth prime number, calculate in parallel to the main stream, where progress is displayed
3. simulation of a house owner and a thief, one brings items to the house, another takes them away. Use parallel streams for each accessing the same data.
*/
#include <cstdio>
#include <iostream>
#include "time.h" 
#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>
#include <algorithm>

using namespace std::chrono_literals;

#define PATIENCE 5          // amount of cycles that thief in task 3 goes through

// relatively useless cout wrapper, since it only protects single output.
class pCout
{
    private:
        std::mutex m;
    public:
        pCout()
        {

        }

        ~pCout()
        {      }

        void msg(const std::string&output)
        {
            std::lock_guard<std::mutex> safemsgoption(m);
                std::cout << output;
        }

        void msgdebug(const std::string&output)     //proc id with a pause to display safety of the output
        {
            std::lock_guard<std::mutex> safemsgoption(m);
                std::cout << "prc" << std::this_thread::get_id() << ". ";
                std::this_thread::sleep_for(10ms);
                std::cout << output;
        }
};

void loudnoise(const int n, const int n2, pCout& pcout)
{
    for (int i = n; i<=n2; i++)
        pcout.msgdebug("counting at " + std::to_string(i) + "\n");
}

bool isPrime(const int n)
{
    int divisor = n-1;
    while (divisor != 1)
    {
        if (n%(divisor) == 0)
        {
            return false;
        }
        divisor--;
    }
    return true;
}

int NthPrime(const int n, int& display)
{
    int primecounter = 0;
    int currentnumber = 2;
    int lastprime;
    
    
    //climbing upwards from 2
    while (primecounter != n)
    {
        if (isPrime(currentnumber))
        {
            lastprime = currentnumber;
            primecounter++;
            display++;
        }
        currentnumber++;
    }
    
    return lastprime;
}

    // realtime display process showing progress of Nthprime function through global "current" var, 
    // needs extra mutex safe to avoid roadkilling result output in the main
void ShowProgress(const int final, int& current, pCout& pcout, std::mutex& safe)
{
    std::lock_guard<std::mutex> safecycle(safe);
    while (current < final)
    {
        pcout.msg("processed " + std::to_string(current) + " prime numbers so far\r");//std::flush
        std::this_thread::sleep_for(20ms);
    }
    pcout.msg("finished                                                     \n");
}

std::pair<const int, std::string> itemlib[12] = {
    {50, "chair"}, {200,"couch"}, {500, "TV"},  {5, "spoon"}, {100, "book"}, {100, "phone"}, 
    {600, "cat"}, {120, "table"}, {350, "microwave"}, {80, "shoes"}, {40, "plant"}, {20, "glasses"}
};

class Room
{
    private:
        std::multimap<const int, std::string> items;
        std::mutex& mic;
        bool roomswitch;
    public:
        Room(std::mutex& output) : mic(output)
        {
            roomswitch = true;
            items.insert({1, "porch"});
        }

        ~Room()
        {
        }

        void Describe()
        {
            std::cout << "room contains " << items.size() << " items: \n";
            for (std::pair<const int, std::string>& item : items)
            {
                std::cout << item.second << "(" << item.first << ") ";
            }
            std::cout << std::endl;
        }

        bool GetState()
        {
            return roomswitch;
        }

        void Abandon()
        {
            roomswitch = false;
        }

        void Operate()
        {
            while(roomswitch)
            {
                mic.lock();
                    Describe();
                mic.unlock();
                std::this_thread::sleep_for(500ms);
            }
        }

        void AddItems(int amount)
        {
            if (roomswitch)
            {
                for (int i = 0; i<amount; i++)
                {
                    int newitem = rand()%12;
                    items.insert(itemlib[newitem]);
                    std::cout << "item was brought - " << items.find(itemlib[newitem].first)->second << std::endl;
                }
            }
        }

        std::multimap<const int, std::string> GetItems()
        {
            return items;
        }

        void RemoveBestItem()
        {
            if (items.size() > 0)
            {
                std::cout << items.rbegin()->second << " was stolen" << std::endl;
                items.erase(std::prev(items.end()));
            }
            else
                std::cout << "nothing to steal!\n";
            
        }
};

void homeowner(Room& room, std::mutex& safe)
{
    while(room.GetState())
    {
        std::this_thread::sleep_for(2000ms);
        std::lock_guard<std::mutex> safeadd(safe);
            room.AddItems(2);
    }
        
    std::lock_guard<std::mutex> safemsg(safe);
    std::cout << "No home anymore :(\n";
}

void thief(Room& room, std::mutex& safe)
{
    std::this_thread::sleep_for(2000ms);
    for (int i =0; i<PATIENCE; i++)
    {
        std::this_thread::sleep_for(900ms);
        std::lock_guard<std::mutex> saferemove(safe);
            room.RemoveBestItem();
    }

    std::lock_guard<std::mutex> saferemove(safe);
        room.Abandon();
        std::cout << "burlgar got bored and burned the house\n";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    srand(static_cast<unsigned int>(time(0)));


    std::mutex safetofinish;            // mutex for wrapping the whole progress display cycle.
    pCout pcout;                       
    //1.
        // pcout wrapper for cout, that is safe to work.
        // demonstrating multiple streams referring to pcout
    std::thread thr1(loudnoise, 1, 5, std::ref(pcout));
    std::thread thr2(loudnoise, 10, 15, std::ref(pcout));
    std::thread thr3(loudnoise, 100, 115, std::ref(pcout));
    std::thread thr4(loudnoise, -15, -10, std::ref(pcout));
    thr1.join();
    thr2.join();
    thr4.join();
    thr3.join();

    std::vector<std::thread> threads;
    pcout.msg("ending task 1. \n\n");

    //2.
        // simplenumber(n) returning nth simple number. 
        // calculation is parallel to output, which shows progress

    int request = 0;    // user input    
    int progress = 0;   // currently running calculation
    int foundprime = 0; // ending result

    pcout.msg("2. which prime to search for? ");
    std::cin >> request;
    
    std::thread calc([&](){foundprime = NthPrime(request, progress);});
    std::thread display(ShowProgress, request, std::ref(progress), std::ref(pcout), std::ref(safetofinish));
    display.detach();
    calc.join();

    safetofinish.lock();
    pcout.msg("\n" + std::to_string(request) + "th prime is " + std::to_string(foundprime) +"\n");
    pcout.msg("ending task 2. \n\n");
    safetofinish.unlock();


    //3.
        // 2 streams that get access to the same data
        // one stream adds (1-3) items, another removes whichever is more valuable.
    Room newroom(safetofinish);

     std::thread roomthr(homeowner, std::ref(newroom), std::ref(safetofinish));
     std::thread roomthr2(thief, std::ref(newroom), std::ref(safetofinish));
     newroom.Operate();
     roomthr.join();
     roomthr2.join();

     safetofinish.lock();
    std::cout << "ending task 3. \n\n";
    safetofinish.unlock();

    return 0;
}