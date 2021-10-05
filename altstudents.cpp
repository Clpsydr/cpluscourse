#include <iostream>
#include <fstream>
#include <optional>
#include <variant>
#include <vector>
#include <string>
#include <tuple>
#include "altstudents.h"

namespace LOCALSTUDENT
{
	FullName::FullName(std::string S, std::string N, std::string P) : Surname(S), Name(N), Patronymic(P)
	{}

	FullName::FullName(std::string S, std::string N) : Surname(S), Name(N)
	{}

	FullName::~FullName()
	{}

	std::string FullName::GetFio()
	{
		return Surname + " " + Name + " " + (Patronymic.has_value() ? Patronymic.value() : " - ");
	}

	Student::Student(std::tuple<const char*, const char*, const char*> fio, const int gradelist[], const int gradesize) : Gradesize(gradesize), Fio(std::get<0>(fio), std::get<1>(fio), std::get<2>(fio))
	{
		Grades = new int[Gradesize];
		for (size_t i = 0; i < Gradesize; i++)
		{
			Grades[i] = gradelist[i];
		}
		
		Avggrade = GetAverageScore();
	}

	Student::~Student()
	{		
		/*delete[] Grades;					// TODO: unable to figure out exception issue - memory fault caused by protobuf. 
		Grades = nullptr;*/
	}

	double Student::GetAverageScore()
	{
		double total = 0;
		if (Gradesize > 0)
		{
			for (size_t i = 0; i < Gradesize; i++)
			{
				total += Grades[i];
			}
			return total / Gradesize;
		}
		else return 0;
	}

	std::string Student::GetAllInfo()
	{
		std::string grds;
		for (size_t i = 0; i < Gradesize; i++)
		{
			grds += std::to_string(Grades[i]) + " ";
		}
		return Fio.GetFio() + "/ " + grds + "/avg grade: " + std::to_string(Avggrade);
	}

	StudentsGroup::StudentsGroup()
	{
	}

	StudentsGroup::~StudentsGroup()
	{
		students.clear();
	}

	void StudentsGroup::AddStudent(Student& newst)
	{
		students.push_back(newst);
	}

	std::string StudentsGroup::GetAllInfo()
	{
		std::string result;
		for (Student& st : students)
		{
			result += st.GetAllInfo();
			result += "\n";
		}
		
		return result;
	}

	bool StudentsGroup::Serialize(std::string path)
	{
		std::ofstream out(path, std::ios::binary);
		if (out)
		{
			//out.write(reinterpret_cast<const char*>(&GetAllInfo()), sizeof(GetAllInfo()));		// TODO: actual binary serialization
			out.write(GetAllInfo().c_str(), GetAllInfo().size());
			out.close();
			return true;
		}
		else
		{
			out.close();
			return false;
		}
	}

	bool StudentsGroup::Deserialize(std::string path, std::string& output)							// TODO: doesn't actually store acquired data in invoked class
	{
		std::ifstream in(path, std::ios::binary);
		if (in)
		{
			output.resize(1024);
			in.read(output.data(), output.size());
			output.resize(in.gcount());
			in.close();
			return true;
		}
		else
		{
			in.close();
			return false;
		}
	}
}