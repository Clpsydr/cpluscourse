#include <iostream>
#include <fstream>
#include <optional>
#include <variant>
#include <tuple>
#include "../students.pb.h"
#include "altstudents.h"

void StudentDisplay(StudentsGroup& stgroup)
{
	std::cout << "Students: " << std::endl;
	for (size_t j=0; j<stgroup.students_size(); j++)
	{
		std::cout << stgroup.students(j).fio().surname() << " " << stgroup.students(j).fio().name() << " ";
		if (stgroup.students(j).fio().has_patronymic())
			std::cout << stgroup.students(j).fio().patronymic();
		std::cout << ": ";

		for (size_t i = 0; i < stgroup.students(j).grades().size(); i++)
		{
			std::cout << stgroup.students(j).grades(i) << " ";
		}

		if (stgroup.students(j).avggrade())
		{
			std::cout << "// average grade - " << stgroup.students(j).avggrade();
		}
		std::cout << std::endl;
	}
}

int main()
{
// first task
	StudentsGroup studyclass;
	StudentsGroup secondclass;

	Student* st1 = studyclass.add_students();
	st1->mutable_fio()->set_surname("Ivanov");
	st1->mutable_fio()->set_name("Ivan");
	st1->mutable_fio()->set_patronymic("Ivanovich");
	
	int a[3] = { 2,4,5 };
	for (int i = 0; i < 3; i++)
		st1->add_grades(a[i]);
	st1->set_avggrade(3);

	Student* st2 = studyclass.add_students();
	st2->mutable_fio()->set_surname("Petrov");
	st2->mutable_fio()->set_name("Petr");
	int b[4] = { 3,3,4,4 };
	for (int i = 0; i < 3; i++)
		st2->add_grades(b[i]);
	st2->set_avggrade(1);

	Student* st3 = studyclass.add_students();
	st3->mutable_fio()->set_surname("Sidorov");
	st3->mutable_fio()->set_name("Sidor");
	st3->mutable_fio()->set_patronymic("Sidorovich");
	int c[5] = {5,4,5,5,3};
	for (size_t i = 0; i < 5; i++)
		st3->add_grades(c[i]);
	st3->set_avggrade(5);

	std::cout << "initial class before deserialization: " << std::endl;
	StudentDisplay(studyclass);

	std::ofstream out("C:/studfiles/students.bin", std::ios_base::binary);
	studyclass.SerializeToOstream(&out);
	out.close();

	std::ifstream in("C:/studfiles/students.bin", std::ios_base::binary);
	if (secondclass.ParseFromIstream(&in))
	{
		std::cout << "Deserialized data below: " << std::endl;

		StudentDisplay(secondclass);
	}
	else
	{
		std::cerr << "error parsing the binary file" << std::endl;
	}
	in.close();

// second task
	std::cout << std::endl << "class display from altstudents.cpp:" << std::endl;

	LOCALSTUDENT::StudentsGroup experimentalgroup;
	int list1[] = { 2,3,4 };	

	LOCALSTUDENT::Student exst1(std::make_tuple("Ivanov", "Ivan", "Ivanovich"), list1, std::extent<decltype(list1)>::value);
	experimentalgroup.AddStudent(exst1);

	int list2[] = { 3,2,2,4 };
	LOCALSTUDENT::Student exst2(std::make_tuple("Petrov", "Petr", "Petrovich"), list2, std::extent<decltype(list2)>::value);
	experimentalgroup.AddStudent(exst2);

	int list3[] = { 5,5,4,5,5 };
	LOCALSTUDENT::Student exst3(std::make_tuple("Sidorov", "Sidor", "Sidorovich"), list3, std::extent<decltype(list3)>::value);
	experimentalgroup.AddStudent(exst3);

	std::cout << experimentalgroup.GetAllInfo();

	std::cout << "saving to file..." << std::endl;
	if (experimentalgroup.Serialize("students2.bin"))
	{
		std::cout << "saving successful." << std::endl;
	}
	else
		std::cout << "something went wrong during saving";

	std::cout << "loading from file..." << std::endl;
	LOCALSTUDENT::StudentsGroup receptiongroup;
	std::string rawformat;
	if (receptiongroup.Deserialize("students2.bin", rawformat))
		std::cout << rawformat;
	else
		std::cout << "error reading from a file";

	return 0;
}