/*
1. Person structure with name fields, patronymic is an optional type. Output and comparison are overloaded for that structure, using tie type.
2. PhoneNumber structure with an overloaded output operator that keeps phone number format +7(911)1234567, Comparison operator is also overloaded.
3. PhoneBook class containing pairs person-phonenumber. Constructor accepts ifstream from a file and parses its contents into container.
- contains output overload.
- Methods SortByName, SortByPhone, GetPhoneNumber, ChangePhoneNumber
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include <optional>
#include <tuple>
#include <vector>
#include <fstream>
#include <algorithm>

struct Person                   
{
    public: 
        std::string Surname;
        std::string Name;
        std::optional<std::string> Patronymic; 

    friend std::ostream& operator<<(std::ostream& out, const Person& p1);

    bool operator<(const Person& rhs) const;
    bool operator==(const Person& rhs) const;
};

struct PhoneNumber                  
{
    public: 
        int countrycode;
        int citycode;
        std::string number;
        std::optional<int> addnumber;      

    friend std::ostream& operator<<(std::ostream& out, const PhoneNumber& pn1);

    bool operator<(const PhoneNumber& rhs) const;
};

std::ostream& operator<<(std::ostream &out, const Person& p1)
{
    out << p1.Surname << " " << std::right << p1.Name << " " ;
    if (p1.Patronymic.has_value())
        out << p1.Patronymic.value();
    out << "\t | ";
    return out;
}

std::ostream& operator<<(std::ostream &out, const PhoneNumber& pn1)
{
    out << "+" << pn1.countrycode << "(" << pn1.citycode << ")" << pn1.number;
    if (pn1.addnumber.has_value())
        out << " " << pn1.addnumber.value();
    return out;
}

bool Person::operator<(const Person& rhs) const
{
    return tie(Surname, Name, Patronymic) < tie(rhs.Surname, rhs.Name, rhs.Patronymic);
}

bool Person::operator==(const Person& rhs) const
{
    return tie(Surname, Name, Patronymic) == tie(rhs.Surname, rhs.Name, rhs.Patronymic);
}

bool PhoneNumber::operator<(const PhoneNumber& rhs) const
{
    int addn1 = addnumber.value_or(0);      // failed here to use optional in tie constructor, had to first init an integer with value
    int addn2 = rhs.addnumber.value_or(0);
    return tie(countrycode, citycode, number, addn1) < tie(rhs.countrycode, rhs.citycode, rhs.number, addn2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

class PersonSearch          // functor for searching in phonebook
{
    private:
        std::string Request;
        std::pair<std::string, std::optional<PhoneNumber>>& SearchResult;
        int counter {0};
    public:

    //dangerous reference to results here, might invalidate before construct. Also searchresult is rewritten inside of the code
        explicit PersonSearch(std:: string newreq, std::pair<std::string, std::optional<PhoneNumber>>& results) : Request(newreq), SearchResult(results)
        {
            SearchResult = std::pair<std::string, std::optional<PhoneNumber>>("not found", std::nullopt);
        }

        void operator()(const std::pair<Person, PhoneNumber>& entry) 
        {
            if (entry.first.Surname == Request)
                {
                    counter++;

                    if (counter == 1)
                    {
                        SearchResult = std::pair<std::string, std::optional<PhoneNumber>>("", entry.second);
                    }
                    else if (counter > 1)
                        SearchResult.first = "found more than 1";
                }
        }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
const char RECORD_DELIIMITER{','};          // phonebook parsing symbols
const char PHONE_COUNTRY{'+'};
const char PHONE_REGIONAL_L{'('};
const char PHONE_REGIONAL_R{')'};
const char PHONE_BEFOREADD{' '};

class Phonebook                     
{
    private:
        std::vector<std::pair<Person, PhoneNumber>> entries;

        static auto constexpr sortByName = [](const std::pair<Person, PhoneNumber>& p1, const std::pair<Person, PhoneNumber>& p2) -> bool
                {
                    return p1.first < p2.first;
                };

        static auto constexpr sortByPhone = [](const std::pair<Person, PhoneNumber>& ph1, const std::pair<Person, PhoneNumber>& ph2) -> bool
                {
                    return ph1.second < ph2.second;
                };

    public:
        std::string getdata(std::string src, char start, char end)          // helper for text parsing, returning data from one symbol to the next one
        {
            return src.substr(src.find(start)+1, src.find(end)-src.find(start)-1);
        }

        Phonebook(std::ifstream &src)        //constructor taking data from .svg/txt that has phone number written as is. 
                                             //method involves using searchmarker as cursor position to skip over anchor symbols in the phone nubmer
                                             //possible exceptions caused by wrong format are not processed individually
        {
            if (src.is_open())
            {
                int searchmarker;
                std::string eachline;
                
                while(getline(src, eachline))
                {
                    Person newperson;
                    PhoneNumber newphone;

                    searchmarker = eachline.find(RECORD_DELIIMITER, 0);
                    newperson.Surname = eachline.substr(0,searchmarker);
                    
                    searchmarker++;
                    newperson.Name = eachline.substr(searchmarker, eachline.find(RECORD_DELIIMITER , searchmarker) - searchmarker);
                    searchmarker = eachline.find(RECORD_DELIIMITER , searchmarker);
                    
                    searchmarker++;
                    if  (eachline.substr(searchmarker,eachline.find(RECORD_DELIIMITER , searchmarker) - searchmarker).length() > 0)
                        newperson.Patronymic = eachline.substr(searchmarker,eachline.find(RECORD_DELIIMITER , searchmarker) - searchmarker);
                    else
                        newperson.Patronymic = std::nullopt;

                    newphone.countrycode = std::stoi(getdata(eachline, PHONE_COUNTRY, PHONE_REGIONAL_L));
                    newphone.citycode = std::stoi(getdata(eachline, PHONE_REGIONAL_L, PHONE_REGIONAL_R));
                    newphone.number = getdata(eachline, PHONE_REGIONAL_R, PHONE_BEFOREADD);
                    newphone.addnumber = (getdata(eachline, PHONE_BEFOREADD, '\r').length() > 0) ? std::stoi(getdata(eachline, PHONE_BEFOREADD, '\r')) : std::optional<int>{};
                    
                    entries.push_back(std::pair<Person, PhoneNumber> (newperson, newphone));            // no data reservation for unclear amount of info written. Vector might be reallocated
                }

                src.close();

            }
            else
            {
                std::cerr << "File not found, phonebook will be empty";
                exit(1);
            }
        }
        ~Phonebook()
        {
        }

        const std::vector<std::pair<Person, PhoneNumber>>& getEntries()
        {
            return entries;
        }
    
        void SortByName()       
        {
            sort(entries.begin(), entries.end(), sortByName); 
        }

        void SortByPhone()      
        {
            sort(entries.begin(), entries.end(), sortByPhone);
        }

        std::pair<std::string,std::optional<PhoneNumber>> GetPhoneNumber(std::string request)          // Number search implemented through function object
        {
            
            std::pair<std::string,std::optional<PhoneNumber>> result;
            for_each(entries.begin(), entries.end(), PersonSearch(request, result));
            return result;           
        }

        void ChangePhoneNumber(Person p1, PhoneNumber newphone)                         // changing phone just uses builtin expression.
        {
            find_if(entries.begin(), entries.end(),
                [&p1, newphone](std::pair<Person, PhoneNumber>& entry)
                {
                    if (entry.first == p1)
                    {
                        entry.second = newphone;
                        return true;
                    }
                    return false;
                });
        }

};

std::ostream& operator<<(std::ostream &out, Phonebook &pbook)
{
    for (const std::pair<Person, PhoneNumber>& pbookrecord : pbook.getEntries())
    {
        out << pbookrecord.first << " \t " << pbookrecord.second << std::endl; 
    }
    return out;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::ifstream sourcefile("phonenumber.txt");
    Phonebook phonebook(sourcefile);
    
    std::cout << std::endl << "--- Initial output: " << std::endl;
    std::cout << phonebook;

    std::cout << std::endl << "--- book sorted by name " << std::endl;
    phonebook.SortByName();
    std::cout << phonebook;

    std::cout << std::endl << "--- book sorted by phone " << std::endl;
    phonebook.SortByPhone();
    std::cout << phonebook;

    std::cout << std::endl << "--- Requesting some phone numbers..." << std::endl;

    auto print_phone_number = [&phonebook](const std::string& surname)
    {
        std::cout << surname << "\t";
        std::pair<std::string, std::optional<PhoneNumber>> answer = phonebook.GetPhoneNumber(surname);
        if (answer.first.empty())
            std::cout << answer.second.value() << std::endl;
        else    
            std::cout << answer.first << std::endl;
    };

    print_phone_number("Ivanov");
    print_phone_number("Petrov");

    std::cout << std::endl << "--- Changing some phone numbers " << std::endl;

    phonebook.ChangePhoneNumber(Person{"Kotov", "Vasilii", "Eliseevich"}, PhoneNumber{7, 123, "15344458", std::nullopt});
    phonebook.ChangePhoneNumber(Person{"Mironova", "Margarita", "Vladimirovna"}, PhoneNumber{16, 465, "9155448", 13});
    std::cout << phonebook;

    return 0;
}