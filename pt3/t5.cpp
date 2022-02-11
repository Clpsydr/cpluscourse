/* Task 5 - assotiative STL containers
1. Template function that receives iterators to the start and end of the word sequence, and outputs list of unique words.
2. Using assotiative container, make an algorithm that uses text input , splits it into sentences and makes ordered list of words sorted by length
*/
#include <cstdio>
#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <iterator>
#include <algorithm>
#include <regex>

template <class Iterator>
void showUniqueWords (Iterator it1, Iterator it2)                       // fuction for 5.1
{
    std::set<std::string> tempstorage;
    
    copy(it1, it2, inserter(tempstorage, tempstorage.end()));
    std::cout << "\nUnique word count:" << tempstorage.size() << std::endl;
    std::copy(tempstorage.begin(), tempstorage.end(), std::ostream_iterator<std::string>(std::cout, " | "));
}

void StrDowncast (std::string& input)                                   // string decapitalization
{
    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c){return std::tolower(c);});
}

////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
//1. Returning unique set of words out of various containers
    std::vector<std::string> textvec;
    std::deque<std::string> textdeq;
    std::list<std::string> textlist;

    std::string text;
    std::regex c_forword("[A-Za-z]+[^,’. -;]");
    std::smatch sample;

    std::string tempphrase;
    std::ifstream file("randomsentence.txt");               // program saves file into a string, which is used twice
    if (file.is_open())
    {
        while(getline(file, tempphrase))
            text += tempphrase;
    }
    else
    {
        std::cerr << "\nfile not found!";
        exit(1);
    }
        
    std::string tempstring;
    tempstring = text;                                      // this algorithm relies on destroying the source string
                                                            // could be done better in a function body, without string dupes, 
                                                            // if I knew reliable way to differentiate in a template
                                                            // between associative container and some other one,
                                                            // and somehow write function for either type
    while (std::regex_search(tempstring, sample, c_forword))
    {
        std::string newstr = sample.str();
        StrDowncast(newstr);
        textvec.push_back(newstr);
        textdeq.push_back(newstr);
        textlist.push_back(newstr);
        tempstring = sample.suffix().str();
    }

    std::cout << std::endl << "Sending vector, total words: " << textvec.size() << std::endl;
    showUniqueWords(textvec.begin(), textvec.end());

    std::cout << std::endl << "Sending deque, total words: " << textdeq.size() << std::endl;
    showUniqueWords(textdeq.begin(), textdeq.end());

    std::cout << std::endl << "Sending list, total words: " << textlist.size() << std::endl;
    showUniqueWords(textlist.begin(), textlist.end());

//2. using associative container, arrange sentences by their size
    std::multimap<int, std::string> sentencearchive;
    std::regex c_forsentence("[^\\s][A-Za-z-,;’'\"\\s]+[.!]");                

                                                            // essentially similar cycle that makes use of double container.    
    while (std::regex_search(text, sample, c_forsentence))      
    {
        sentencearchive.insert({sample.str().size(), sample.str()});
        text = sample.suffix().str();
    }
    
    std::cout << std::endl << "Checking how sentences got sorted out! " << std::endl;
    for_each(sentencearchive.begin(), sentencearchive.end(),
        [](std::pair<int, std::string> record){ std::cout << record.first << " : " << record.second << std::endl;}
    );

    return 0;
}