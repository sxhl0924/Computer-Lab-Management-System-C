#include <iostream>
using namespace std;
#include "Administrator.h"
#include <fstream>
#include "GlobalFile.h"
#include <algorithm>

Administrator::Administrator()
{

}

Administrator::Administrator(string name, string pwd)
{
	this->m_Username = name;
	this->m_Password = pwd;
	this->initVector();
}

//abstract function in father class must be rewritten in son class
void Administrator::m_OperMenu()
{
	cout << "********************************* Welcome "<<this->m_Username <<"!********************************" << endl;
	cout << endl;
	cout << "\t\t---------------------------------------------\n";
	cout << "\t\t|                                           |\n";
	cout << "\t\t|            1. Add Users                   |\n";
	cout << "\t\t|                                           |\n";
	cout << "\t\t|            2. Show Users                  |\n";
	cout << "\t\t|                                           |\n";
	cout << "\t\t|            3. Show Computer Lab           |\n";
	cout << "\t\t|                                           |\n";
	cout << "\t\t|            4. Clear order records         |\n";
	cout << "\t\t|                                           |\n";
	cout << "\t\t|            0. Logout                      |\n";
	cout << "\t\t|                                           |\n";
	cout << "\t\t---------------------------------------------\n";
	cout << endl;

	cout << "Please select a function: " << endl;
}

//add user
void Administrator::addUser()
{
	cout << "Please select the type of users you want to add:" << endl;
	cout << "1. Student" << endl;
	cout << "2. Teacher" << endl;

	string FileName;
	string tip1;
	string tip2;
	ofstream ofs;

	int select = 0;
	
	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			FileName = STUDENT_FILE;
			tip1 = "Please input student ID of the new user (number): ";
			tip2 = "Student ID alreadly used, please input a new ID! ";
			break;
		}
		else if (select == 2)
		{
			FileName = TEACHER_FILE;
			tip1 = "Please input teacher ID of the new user (number): ";
			tip2 = "Teacher ID alreadly used, please input a new ID! ";
			break;
		}
		else
		{
			cout << "Invalid Input! Please Choose a Correct User Type." << endl;
		}
	}
		
	ofs.open(FileName, ios::out | ios::app);//append new data to file
	int id;
	string name;
	string pwd;
	cout << tip1 << endl;

	while (true)
	{
		cin >> id;//id must not be repeated
		bool ret = checkRepeat(id, select);//bool checkRepeat(int id, int type)
		if (ret)
		{
			cout << tip2 << endl; //go back to cin
		}
		else
		{
			break;//no repeat skip the while cycle
		}
	}	

	cout << "Please input the name of new user (6 characters):  " << endl;
	while (true)
	{
		cin >> name;
		if (name.size() == 6)
		{
			break;
		}

		cout << "Invalid Name! Please re-enter your username (6 characters):" << endl;
	}
	
	cout << "Please input the password of new user (8 characters): " << endl;
	while (true)
	{
		cin >> pwd;
		if (pwd.size() != 8)
		{
			cout << "Invalid Password! Please re-enter your password (8 characters):" << endl;
		}
		else
		{
			break;
		}			
	}
	
	ofs << id << " " << name << " " << pwd << " " << endl;//write the user info to File
	cout << "New User Added Successfully!" << endl;	
	system("pause");
	system("cls");
	ofs.close();
	this->initVector();//read the file with the new user added
	//***to avoid the bug that it is possible to use repeated id without receiving reminding tip if you add more than one new
    //user continuously, becuase the new users haven't been updated in the loaded student/teacher files. *** 
}

//show user info
void printStu(Student &s)//print student info
{
	cout << "Student ID: " << s.m_SID << "  Username: " << s.m_Username << "  Password: " << s.m_Password << endl;
}

void printTea(Teacher& t)//print teacher info
{
	cout << "Teacher ID: " << t.m_TID << "  Username: " << t.m_Username << "  Password: " << t.m_Password << endl;
}

void Administrator::showUser()
{
	cout << "Please select the type of users you want to review: " << endl;
	cout << "1. Student" << endl;
	cout << "2. Teacher" << endl;
	int select = 0;
	while(true)
	{ 
		cin >> select;
		if (select == 1)
		{
			cout << "Information of all student users: " << endl;
			for_each(vStu.begin(), vStu.end(), printStu);//include <algorithm>
			//for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
			//{
				//cout << "Student ID: " << it->m_SID << "  Username: " << it->m_Usename << "  Password: " << it->m_Password << endl;
			//}
			break;
		}
		else if (select == 2)
		{
			cout << "Information of all teacher users: " << endl;
			for_each(vTea.begin(), vTea.end(), printTea);
			//for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
			//{
				//cout << "Teacher ID: " << it->m_TID << "  Username: " << it->m_Usename << "  Password: " << it->m_Password << endl;
			//}
			break;
		}
		else
		{
			cout << "Invalid Input! Please select a Correct Type." << endl;
		}
	}
	system("pause");
	system("cls");
}

//show info of computer Lab
void printCom(ComputerLab &c)
{
	cout << "Computer Lab ID: " << c.m_ComId << "  Maxumun numbers of computers: " << c.m_comlabMax << endl;
	
}
void Administrator::showComputerLab()
{
	cout << "Information of all computer labs: " << endl;
	for_each(vCom.begin(), vCom.end(), printCom);
	system("pause");
	system("cls");
}

//clear info of all revervation orders
void Administrator::clearRecord()
{
	cout << "Are you sure to clear all order records?" << endl;
	cout << "1. Yes, continue" << endl;
	cout << "2. No, return" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs;
		ofs.open(ORDER_FILE, ios::trunc);//trunc:if file already exists, delete and then create a new one. 
		ofs.close();
		cout << "All order records have been cleared!" << endl;
	}
	system("pause");
	system("cls");
}

//
void Administrator:: initVector()
{
	//make sure vectors are empty before they are used to store data 
	vStu.clear();
	vTea.clear();
	vCom.clear();
	//read data from file
	//student
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "Fail to read student file!" << endl;
		return;
	}
	
	Student s;
	while (ifs >> s.m_SID && ifs >> s.m_Username && ifs >> s.m_Password)
	{
		vStu.push_back(s);
	}
	//cout << "The number of current student users is " << vStu.size() << endl;

	//teacher
	ifstream ifs1;
	ifs1.open(TEACHER_FILE, ios::in);
	if (!ifs1.is_open())
	{
		cout << "Fail to read teacher file!" << endl;
		return;
	}
	Teacher t;
	while (ifs1 >>t.m_TID && ifs1 >> t.m_Username && ifs1 >> t.m_Password)
	{
		vTea.push_back(t);
	}
	//cout << "The number of current teacher users is " << vTea.size() << endl;
	//computer lab
	ifstream ifs2;
	ifs2.open(COMPUTER_FILE, ios::in);
	if (!ifs2.is_open())
	{
		cout << "Fail to read computer file!" << endl;
		return;
	}
	ComputerLab c;
	while (ifs2 >> c.m_ComId && ifs2 >> c.m_comlabMax)
	{
		vCom.push_back(c);
	}
	//cout << "The number of current computer lab is " << vCom.size() << endl;
}

bool Administrator::checkRepeat(int id, int type)//username and password may be the same, but id is unique.
{
	if (type == 1)//student
	{
		for(vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{ 
			if (id == it->m_SID)
			{
				//cout << "User ID already existed!" << endl;
				return true;
			}
		}
	}
	else //teacher
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_TID)
			{
				//cout << "User ID already existed!" << endl;
				return true;
			}
		}
	}	
	return false;
}