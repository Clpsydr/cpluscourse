#include <iostream>
#include <cstdlib>
#include <ctime>
#include <tgmath.h>
#include <fstream>

using namespace std;

int TASKTWOSCOPE = 250;                     //defines how random the values in 6-2 will be

void clearmem(int* arr)                     // freeing the array
{
    delete[] arr;
    arr = nullptr;
}

void clearmem(int** arr, int depth)         // freeing 2d array
{
    for (size_t i = 0; i < depth; i++)
        delete[] arr[i];
    delete[] arr;
    arr = nullptr;
}

void arrayloadmk2(int* arr, int size)       //displaying the array
{
    cout << "\n following array is loaded: ";
    for (int i = 0; i<size; i++)
        cout << *(arr+i) << " " ;
}

void arrayloadmk3(int** arr, int sizex, int sizey)      //display for two dimensional array
{
    cout << "\n following array is loaded: ";
    for (size_t i = 0; i < sizex; i++)
        {
            cout << "\n ";
            for (size_t j = 0; j < sizey; j++)
                cout << arr[i][j] << " ";
        }
}

void arraypowtwo(int* arr, int size)          // making array for the 6-1
{
    for (int i = 0; i<size; i++)
        arr[i] = pow(2,i);
}

void randomarray(int** arr, int sizex, int sizey, int scope)        // random xy matrix with values going up to scope
{
    for (size_t i = 0; i < sizex; i++)
        for (size_t j = 0; j < sizey; j++)
            arr[i][j] = rand()%scope;
}

// Memory allocation in an absurd manner of returning memory stack opened in the function
// I feel like its not supposed to work but it does
int* arraymem(int size)
{
    int* memstack = new (nothrow) int[size];
    if (memstack != nullptr)
        return memstack;
    else
    {
        cout << "memory allocation failed";
        return {};
    }
}

int** arraymem(int sizex, int sizey)        //memory allcoation overload for 2d arrays
{
    int** memstack = new int* [sizex];

    if (memstack != nullptr)
    {
        for (size_t i = 0; i < sizex; i++)
            memstack[i] = new int[sizey];    
        return memstack;
    }
    else 
    {
        cout << "memory allocation failed";
        return {};
    }
}

void makefile(string filename)          //making a file with some garbage inside
{
    int length = rand()%25+25;
    ofstream fout(filename + ".txt");
    fout << "[ ";
    for (int i=0; i<length; i++)
        fout << filename << i << " \n";
    fout << " ]";
    fout.close();
}

string filereadto(string filename)          //returns contents of a file in a string
{
    string outputs;
    ifstream fin(filename+".txt");
    if (fin.is_open())
    {
        const size_t size = 255;
        char txtline[size];
        while(!fin.eof())
        {
            fin.getline(txtline,size);
            outputs += txtline;
        }
        fin.close();
        return outputs;
    }
    else
        return "error opening file " + filename + ".txt";
}

void makefile(string filename, string source1, string source2)   // produces a file with two other file contents written one after another
{
    ofstream fout(filename + ".txt");
    fout << "[" << source1 << "\n";
    fout << filereadto(source1) << "\n" << source2 << "\n" << filereadto(source2);
    fout << "\n ]";
    fout.close();
}

void simplesearch(string fname, string query)                   // its called simple because I didn't write the actual searching method
{
    int beacon;
    ifstream fin(fname);
            if (fin.is_open())
            {
                string txtline;         // interim space for read text
                int readlines = 0;      // tracking counter for lines
                while(getline(fin, txtline))
                {
                    readlines++;
                    beacon = txtline.find(query);
                    if (beacon!=string::npos)
                    {
                        cout << "\n this word exists at line "<< readlines << " position " << beacon;
                        break;
                    }
                }
                if (beacon==string::npos)
                    cout << "\n no entries of such word";
                fin.close();
            }
            else
                cout << "\n error opening requested file." << fname;
}

bool wordcheck(string query, char buffer[])                // imitation of .find() that tracks the whole line for inclusions of query
{
    int len = query.size();
    int counter = 0;
    for (int i = 0; i<(255-len); i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (query[j] == buffer[i+j])
                counter++;
        }
        if (counter == len)
            return true;
        else counter = 0;
    }
    return false;
}

void textsearch(string fname, string query)                 // file streaming that uses wordcheck()
{
    int searchsize = query.size();
    size_t encounters = 0;

    ifstream fin(fname);
        if (fin.is_open())
        {
            const size_t size = 255;
            char buffer[size];
            while(!fin.eof())
            {
                fin.getline(buffer,size);
                if (wordcheck(query,buffer))
                {
                    cout << "\n found the word!";
                    encounters++;
                }
                
            }
            cout << "\n finished searching, found the word " << encounters << " times";
            fin.close();
        }
        else 
            cout << "\n error opening requested file." << fname;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    srand(static_cast<unsigned int>(time(0)));

    // if (argc > 2)
    //     cout << "passed parameters were " << argv[1] << " " << argv[2];

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   #6.1
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
        int arrsize;
        int* newarray;
        cout << "\n 6.1. Enter the size for an array - ";
        cin >> arrsize;

        newarray = arraymem(arrsize);
        arraypowtwo(newarray, arrsize);
        arrayloadmk2(newarray, arrsize);

        clearmem(newarray);
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   #6.2
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
        int** samplematrix;
        int matrixsizex = 4;
        int matrixsizey = 4;

        cout << "\n\n 6.2. Allocating a square 2d matrix - ";
        samplematrix = arraymem(matrixsizex, matrixsizey);
        randomarray(samplematrix, matrixsizex, matrixsizey, TASKTWOSCOPE);
        arrayloadmk3(samplematrix, matrixsizex, matrixsizey);

        clearmem(samplematrix, matrixsizey);
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   #6.3
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
        string fname;
        string fname2;

        cout << "\n\n 6.3. Enter first filename - ";
        cin >> fname;
        makefile(fname);

        cout << "\n Enter second filename - ";
        cin >> fname2;
        makefile(fname2);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   #6.4
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
        string fname3;
        cout << "\n\n 6.4. Enter filename for a file to combine into - ";
        cin >> fname3;

        makefile(fname3,fname,fname2);
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   #6.5
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {
        if (argc > 2)           //only launches with enough arguments
        {
        string searchquery = argv[1];
        string fname4 = argv[2];
        cout << "\n\n 6.5. Searching for " << searchquery << " in " << fname4;

        //searching starts here
        cout << "\n running through string method... ";
        simplesearch(fname4, searchquery);
        cout << "\n now using our own function...";
        textsearch(fname4, searchquery);
        
        }
        else
            cout << "\n\n Task 6.5 will be executed only if programm will be launched as (./run query fullfilename)";
    }

    return 0;
}
