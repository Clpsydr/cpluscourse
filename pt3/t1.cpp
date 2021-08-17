#include <iostream>
#include <iomanip>
#include <string>
#include <functional>
#include <optional>
#include <tuple>
#include <vector>
#include <fstream>

struct person                   
{
    std::string Surname;
    std::string Name;
    std::optional<std::string> Patronymic; 
};

struct phonenumber                  
{
    int countrycode;
    int citycode;
    std::string number;
    std::optional<int> addnumber;      
};

std::ostream& operator<<(std::ostream &out, person p1)
{
    out << p1.Surname << " " << std::right << p1.Name << " " ;
    if (p1.Patronymic.has_value())
        out << p1.Patronymic.value();
    out << "\t | ";
    return out;
}

std::ostream& operator<<(std::ostream &out, phonenumber pnumber)
{
    out << "+" << pnumber.countrycode << "(" << pnumber.citycode << ")" << pnumber.number;
    if (pnumber.addnumber.has_value())
        out << " " << pnumber.addnumber.value();
    return out;
}

bool operator<(const person& p1, const person& p2)
{
    return tie(p1.Surname, p1.Name, p1.Patronymic) < tie(p2.Surname, p2.Name, p2.Patronymic);
}

bool operator==(const person& p1, const person& p2)
{
    return tie(p1.Surname, p1.Name, p1.Patronymic) == tie(p2.Surname, p2.Name, p2.Patronymic);
}

bool operator<(const phonenumber& ph1, const phonenumber& ph2)
{
    int addn1 = ph1.addnumber.value_or(0);      // failed here to use optional in tie constructor, had to first init an integer with value
    int addn2 = ph2.addnumber.value_or(0);
    return tie(ph1.countrycode, ph1.citycode, ph1.number, addn1) < tie(ph2.countrycode, ph2.citycode, ph2.number, addn2);
}

class PersonSearch          // functor for searching in phonebook
{
    private:
        std::string request;
        std::pair<std::string, phonenumber>& m_result;
        int counter;
    public:
        explicit PersonSearch(std:: string newreq, std::pair<std::string, phonenumber>& results) : request(newreq), m_result(results)
        {
            m_result = std::pair<std::string, phonenumber>("not found", {0,0,"0"});
            counter = 0;
        }

        void operator()(const std::pair<person, phonenumber>& entry) 
        {
            if (entry.first.Surname == request)
                {
                    counter++;

                    if (counter == 1)
                    {
                        m_result = std::pair<std::string, phonenumber>("", entry.second);
                    }
                    else if (counter > 1)
                        m_result.first = "found more than 1";
                }
        }
};

class Phonebook                     
{
    private:
        std::vector<std::pair<person, phonenumber>> entries;

        static auto constexpr sortByName = [](const std::pair<person, phonenumber>& p1, const std::pair<person, phonenumber>& p2) -> bool
                {
                    return p1.first < p2.first;
                };

        static auto constexpr sortByPhone = [](const std::pair<person,phonenumber>& ph1, const std::pair<person, phonenumber>& ph2) -> bool
                {
                    return ph1.second < ph2.second;
                };

    public:
        std::string getdata(std::string src, char start, char end)          // helper for text parsing, returning data from one symbol to the next one
        {
            return src.substr(src.find(start)+1, src.find(end)-src.find(start)-1);
        }

        Phonebook(std::ifstream &src)        //comically obtuse constructor, taking data from .svg/txt that has phone number written as is. 
                                            // possible exceptions caused by wrong format are not processed
        {
            int searchmarker;
            std::string eachline;

            if (!src)
            {
                std::cerr << "File not found, phonebook will be empty";
                exit(1);
            }

            while(getline(src, eachline))
            {
                person newperson;
                phonenumber newphone;

                searchmarker = eachline.find(',',0);
                newperson.Surname = eachline.substr(0,searchmarker);
                
                searchmarker++;
                newperson.Name = eachline.substr(searchmarker, eachline.find(',',searchmarker)-searchmarker);
                searchmarker = eachline.find(',',searchmarker);
                
                searchmarker++;
                if  (eachline.substr(searchmarker,eachline.find(',',searchmarker)-searchmarker).length() > 0)
                    newperson.Patronymic = eachline.substr(searchmarker,eachline.find(',',searchmarker)-searchmarker);
                else
                    newperson.Patronymic = std::nullopt;

                newphone.countrycode = std::stoi(getdata(eachline, '+', '('));
                newphone.citycode = std::stoi(getdata(eachline, '(', ')'));
                newphone.number = getdata(eachline, ')' , ' ');

                if (getdata(eachline, ' ', '\r').length() > 0)
                    newphone.addnumber = std::stoi(getdata(eachline, ' ', '\r'));
                else 
                    newphone.addnumber = std::nullopt;
                
                entries.push_back(std::pair<person, phonenumber> (newperson, newphone));
            }
        }
        ~Phonebook()
        {
        }

        std::vector<std::pair<person, phonenumber>> getEntries()
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

        std::pair<std::string,phonenumber> GetPhoneNumber(std::string request)          // Number search implemented through function object
        {
            
            std::pair<std::string,phonenumber> result;
            for_each(entries.begin(), entries.end(), PersonSearch(request, result));
            return result;           
        }

        void ChangePhoneNumber(person p1, phonenumber newphone)                         // changing phone just uses builtin expression.
        {
            find_if(entries.begin(), entries.end(),
                [&p1, newphone](std::pair<person, phonenumber>& entry)
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
    for (const std::pair<person, phonenumber>& pbookrecord : pbook.getEntries())
    {
        out << pbookrecord.first << " \t " << pbookrecord.second << std::endl; 
    }
    return out;
}

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
        auto answer = phonebook.GetPhoneNumber(surname);
        if (get<0>(answer).empty())
            std::cout << get<1>(answer) << std::endl;
        else    
            std::cout << get<0>(answer) << std::endl;
    };

    print_phone_number("Ivanov");
    print_phone_number("Petrov");

    std::cout << std::endl << "--- Changing some phone numbers " << std::endl;

    phonebook.ChangePhoneNumber(person{"Kotov", "Vasilii", "Eliseevich"}, phonenumber{7, 123, "15344458", std::nullopt});
    phonebook.ChangePhoneNumber(person{"Mironova", "Margarita", "Vladimirovna"}, phonenumber{16, 465, "9155448", 13});
    std::cout << phonebook;

    return 0;
}