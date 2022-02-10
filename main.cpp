#include <iostream>
#include <fstream>
#include <optional>
#include <variant>
#include <vector>
#include <tuple>
#include <gtest/gtest.h>
#include "students.pb.h"
#include "altstudents.h"

void StudentDisplay(StudentsGroup& stgroup)
{
	std::cout << "Students: " << std::endl;
	for (int j=0; j<stgroup.students_size(); j++)
	{
		std::cout << stgroup.students(j).fio().surname() << " " << stgroup.students(j).fio().name() << " ";
		if (stgroup.students(j).fio().has_patronymic())
			std::cout << stgroup.students(j).fio().patronymic();
		std::cout << ": ";

		for (int i = 0; i < stgroup.students(j).grades().size(); i++)
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

class TestStudentgroup : public testing::Test
{
	protected:
		void SetUp() override
		{
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
		}
		void TearDown() override
		{
			delete experimentalgroup;
		}
		
		LOCALSTUDENT::StudentsGroup* experimentalgroup;
};

class TestProtogroup : public testing::Test
{
	protected:
		void SetUp() override
		{
			StudentsGroup pstudyclass;

			Student* st1 = pstudyclass.add_students();
			st1->mutable_fio()->set_surname("Ivanov");
			st1->mutable_fio()->set_name("Ivan");
			st1->mutable_fio()->set_patronymic("Ivanovich");

			int a[3] = { 2,4,5 };
			for (int i = 0; i < 3; i++)
				st1->add_grades(a[i]);
			st1->set_avggrade(3);

			Student* st2 = pstudyclass.add_students();
			st2->mutable_fio()->set_surname("Petrov");
			st2->mutable_fio()->set_name("Petr");
			int b[4] = { 3,3,4,4 };
			for (int i = 0; i < 3; i++)
				st2->add_grades(b[i]);
			st2->set_avggrade(1);

			Student* st3 = pstudyclass.add_students();
			st3->mutable_fio()->set_surname("Sidorov");
			st3->mutable_fio()->set_name("Sidor");
			st3->mutable_fio()->set_patronymic("Sidorovich");
			int c[5] = { 5,4,5,5,3 };
			for (size_t i = 0; i < 5; i++)
				st3->add_grades(c[i]);
			st3->set_avggrade(5);
		}

		void TearDown() override
		{
			pstudyclass->clear_students();
			delete pstudyclass;
		}

	StudentsGroup* pstudyclass;
};

bool ProtobufSerializationCheck (StudentsGroup stgr, StudentsGroup stgr2)
{
	if (stgr.students_size() != stgr2.students_size())
		return false;

	std::string gr1;
	std::string gr2;

	for (int j = 0; j < stgr.students_size(); j++)
	{
		gr1 = stgr.students(j).fio().surname() + stgr.students(j).fio().name() + (stgr.students(j).fio().has_patronymic() ? stgr.students(j).fio().patronymic() : "");
		gr2 = stgr2.students(j).fio().surname() + stgr2.students(j).fio().name() + (stgr2.students(j).fio().has_patronymic() ? stgr2.students(j).fio().patronymic() : "");;
		for (int i = 0; i < stgr.students(j).grades().size(); i++)
		{
			gr1 += stgr.students(j).grades(j) + " ";
			gr2 += stgr2.students(j).grades(j) + " ";
		}

		if (stgr.students(j).avggrade())
		{
			gr1 += stgr.students(j).avggrade();
			gr2 += stgr2.students(j).avggrade();
		}
	}

	return gr1 == gr2;
}

TEST(TestProtogroup, ProtobufSerializationCheck)
{
	/// pstudyclass is undefined in the test despite similar implementation for other class in the test

	std::ofstream out("C:/studfiles/students.bin", std::ios_base::binary);
		EXPECT_TRUE(pstudyclass->SerializeToOstream(&out)) << "Error saving proto structure into file";
	out.close();

StudentsGroup preceiverclass;
	std::ifstream in("C:/studfiles/students.bin", std::ios_base::binary);
		EXPECT_TRUE(preceiverclass.ParseFromIstream(&in)) << "Fail reading proto structure from file";
	in.close();

	ASSERT_EQ(pstudyclass, preceiverclass); << "Difference between serialized and deserialized data";
}

TEST_F(TestStudentgroup, StudentSerializationCheck)   
{
	experimentalgroup->GetAllInfo();	///Attempt to invoke class from Test_studentsgroup causes interrupt from protobuf yet again.

	LOCALSTUDENT::StudentsGroup expgroup;
		int list1[] = { 2,3,4 };
		LOCALSTUDENT::Student exst1(std::make_tuple("Ivanov", "Ivan", "Ivanovich"), list1, std::extent<decltype(list1)>::value);
		expgroup.AddStudent(exst1);

		int list2[] = { 3,2,2,4 };
		LOCALSTUDENT::Student exst2(std::make_tuple("Petrov", "Petr", "Petrovich"), list2, std::extent<decltype(list2)>::value);
		expgroup.AddStudent(exst2);

		int list3[] = { 5,5,4,5,5 };
		LOCALSTUDENT::Student exst3(std::make_tuple("Sidorov", "Sidor", "Sidorovich"), list3, std::extent<decltype(list3)>::value);
		expgroup.AddStudent(exst3);
		
		EXPECT_TRUE(expgroup.Serialize("students2.bin")) << "Failed saving into file";
		
	LOCALSTUDENT::StudentsGroup expreceptiongroup;
		std::string deserresult;
		EXPECT_TRUE(expreceptiongroup.Deserialize("students2.bin", deserresult)) << "Failed reading from file";
		ASSERT_EQ(expgroup.GetAllInfo(), deserresult) << "Deserialization happened with data loss" ; 
}

int main()
{
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}