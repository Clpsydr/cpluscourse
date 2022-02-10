#pragma once

namespace LOCALSTUDENT
{ 
	/*class IRepository
	{
		virtual void Open() = 0;
		virtual void Save() = 0;
	};

	class IMethods
	{
		virtual double GetAverageScore(const FullName& name) = 0;
		virtual std::string GetAllInfo(const FullName& name) = 0;
		virtual std::string GetAllInfo() = 0;
	};*/

	class FullName
	{
	private:
		std::string Surname;
		std::string Name;
		std::optional<std::string> Patronymic;
	public:
		FullName(std::string S, std::string N, std::string P);
		FullName(std::string S, std::string N);
		~FullName();
		std::string GetFio();
	};

	class Student
	{
	private:
		FullName Fio;
		int* Grades;
		size_t Gradesize{ 0 };
		double Avggrade{ 0 };
	public:
		Student(std::tuple<const char*, const char*, const char*> fio, const int gradelist[], const int gradesize);
		~Student();
		double GetAverageScore();
		std::string GetAllInfo();
	};

	class StudentsGroup
	{
	private:
		std::vector<Student> students;
	public:
		StudentsGroup();
		~StudentsGroup();
		void AddStudent(Student& newst);
		std::string GetAllInfo();
		bool Serialize(std::string path);
		bool Deserialize(std::string path, std::string& output);
	};

}
