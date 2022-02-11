/* STL containers
1. Add float number to end of the list, that is an average of sum of all the list elements
2. Class that represents matrix. Method that calculates determinant of the matrix
3. Make your own iterator class for integer numbers in for-range-based range.
*/

#include <cstdio>
#include <iostream>
#include <list>
#include <random>
#include <chrono>
#include <utility>
#include <memory>
#include <math.h>

/////////// randomizer scope for convenience 
#define RANGEX 1
#define RANGEY 15

int32_t getRandomNum(int32_t min, int32_t max)
{
    const static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937_64 generator(seed);
    std::uniform_int_distribution<int32_t> dis(min, max);
    return dis(generator);
}
////////////

float sum (std::list<float>& container)                                                         // task 1 summation helper
{
    if (container.size() == 1)
        return container.front();
    else
    {
        std::list<float> n_cont(next(container.begin(), 1), container.end());
        return container.front() + sum(n_cont);
    }
}

void addNewAverage(std::list<float>& container)                                                 // task 1 function
{
    container.push_back(sum(container)/container.size());
}

template <typename T>                                                                           // override for list outputs
std::ostream& operator<<(std::ostream &out, std::list<T> &outlist)
{
    for (const T element : outlist)
    {
        out << element << " ";
    }
    out << std::endl;
    return out;
}

class Matrix
{
    private:
        std::list<int> elements;
        int size;
    public:
        Matrix(int sz) : size(sz)                                                           // pregenerated matrix with values
        {
            for (int i = 0; i < sz*sz; i++) 
            {
                elements.push_back(getRandomNum(RANGEX,RANGEY));
            }
        }

        Matrix(Matrix& lastlist, int x, int y) : size(lastlist.getSize()-1)                 // add.minor with values from another matrix
        {
            for (int i = 0; i < lastlist.getSize(); i++)
                for (int j = 0; j < lastlist.getSize(); j++)
                    if (i != (x-1) && j != (y-1))
                        elements.push_back(lastlist.ele(i+1,j+1));
            
        }

        ~Matrix()
        {
        }

        std::list<int> getElements() const
        {
            return elements;
        }

        int Determinant()
        {
            switch (size)
            {
            case 1:
                return ele(1,1);
                break;
            case 2:
                return ele(1,1) * ele(2,2) - ele(1,2) * ele (2,1);
                break;
            case 3:
                return ele(1,1) * Matrix(*this,1,1).Determinant() -
                        ele(1,2) * Matrix(*this,1,2).Determinant() +
                         ele(1,3) * Matrix(*this,1,3).Determinant();
                break;
            default:
                int sum = 0;
                for (int j = 1; j <= size; j++)
                {
                    sum += pow(-1, 1+j) * ele(1,j) * Matrix(*this, 1, j).Determinant();

                }
                return sum;
                break;
            }
        }

        int ele(int x, int y)                                                           // compact return of certain value
        {
            return *next(elements.begin(), (x-1)*size+(y-1));
        }

        int getSize()
        {
            return size;
        }
};

std::ostream& operator<<(std::ostream &out, Matrix &matrx)                              // override for matrix output format
{
    int counter = 0;
    for (const int& element : matrx.getElements())
    {
        out << element;
        if (counter == matrx.getSize()-1)
        {
            out << "\n";
            counter = 0;
        }
        else
        {
            out << " \t";
            counter++;
        }
    }
    return out;
}

class IntIterator : public std::iterator<std::input_iterator_tag, int>                      // iterator for custom container
{
    friend class IntContainer;

    private:
        int* value;
        IntIterator(int* val) : value(val){};
    public:
        IntIterator(const IntIterator& iter) : value(iter.value)
        {
        }

        ~IntIterator()
        {
        }

        bool operator!=(IntIterator const& other) const
        {
            return value != other.value;
        }

        reference operator*() const
        {
            return *value;
        }

        IntIterator& operator++()
        {
            ++value;
            return *this;
        }
};

class IntContainer
{
    private:
        const size_t size;
        std::unique_ptr<int[]> data;
    
    public:
        IntIterator begin()
        {
            return IntIterator(data.get());
        }

        IntIterator end()
        {
            return IntIterator(data.get()+ size);
        }

        IntContainer(std::initializer_list<int> values): size(values.size()), data(new int[size])
        {
            std::copy(values.begin(), values.end(), data.get());
        }
};

// iterator for pseudo container that only keeps data about range 
class StepIterator : public std::iterator<std::random_access_iterator_tag, int>                                                    
{
    friend class Diapazone;
    private:
        int m_end;
        int m_step;
        int m_value;
    public:
        StepIterator(int target_range, int target_step,  int start_value) : m_end(target_range), m_step(target_step), m_value(start_value)
        {
        }

        ~StepIterator()
        {
        }

        operator int() const
        {
            return m_value;
        }

        bool operator!=(StepIterator const& other) const
        {
            return m_value != other.m_value+m_step;
        }

        int operator*() const
        {
            return m_value;
        }

        int operator++()
        {
            m_value += m_step;
            return *this;
        }

};

// pseudo container with only range and step for iteration
class Diapazone 
{
    private:
        int i_min;
        int i_max;
        int i_step;
    public:
        Diapazone(int min, int max, int step = int(1)) : i_min(min), i_max(max), i_step(step)
        {
        }

        int operator[](size_t index)
        {
            return (i_min + index*i_step);
        }

        int step()
        {
            return i_step;
        }

        size_t size()
        {
            return int((i_max - i_min) / i_step);
        }

        StepIterator begin()
        {
            return StepIterator(i_max, i_step, i_min);
        }

        StepIterator end()
        {
            return StepIterator(i_max, i_step, i_min + size() * i_step);
        }
    
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //////////////////////////////
    std::list<float> newset = {1.1, 15, 3.013, 26.129, 928.1, 0.6};
    std::cout << "Initial list: " << newset;
    addNewAverage(newset);
    std::cout << "added an element " << newset;
    addNewAverage(newset);
    std::cout << "added another element " << newset;

    //////////////////////////////
    int scope;
    std::cout << "Enter matrix size (takes too long after size>10): ";
    std::cin >> scope;
    Matrix mtr(scope);
    std::cout << "New matrix generated: " << std::endl << mtr;
    std::cout << "Determinant of that matrix is: " << mtr.Determinant();

    /////////////////////////////////
    std::cout << std::endl << "Booting up custom container with its own iterator... " << std::endl;
    IntContainer Frank_int_stein = {4,2,2,5,3,12,1,5,1,24,2};
    for(const int i: Frank_int_stein)
    {   
        std::cout << i << " ";
    }

    std::cout << std::endl << "also just a range of integers, and iterating through them... " << std::endl;
    Diapazone numberblock(15,145,5);
    for(const int i: numberblock)
    {
        std::cout << i << " ";
    }

    return 0;
}