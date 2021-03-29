#include <iostream>
using namespace std;
#include <string>
#include "Identity.h"
#include <fstream>
#include "GlobalFile.h"
#include "Student.h"
#include "Teacher.h"
#include "Administrator.h"
#include"OrderFile.h"

//define a global function to enter the sub-menu of administrator
void Stu_Menu(Identity*& Stud)
{
	while (true)
	{
		Stud->m_OperMenu();
		//convert the parent class object (Identity Stud) into child class(Student stu) to access more son class properties 
		Student* stu = (Student*)Stud;
		int select;
		cin >> select;
		switch (select)
		{
		case 1:// Submit orders		
			stu->submitOrder();
			break;
		case 2://Show My Orders  
			stu->showMyOrder();
			break;
		case 3://Show All Orders 
			stu->showAllOrder();
			break;
		case 4://Cancel my Orders 
			stu->cancelOrder();
			break;
		case 0:
			delete stu;
			cout << "Log Out" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "Invalid Input!" << endl;
			break;
		}
	}
}

void Tea_Menu(Identity *&Tea)
{
	while (true)
	{
		Tea->m_OperMenu();
		//convert the parent class object (Identity Stud) into child class(Student stu) to access more son class properties 
		Teacher* tea = (Teacher*)Tea;
		int select;
		cin >> select;
		switch (select)
		{
		case 1:// show all orders	
			tea->showAllOrder();
			break;
		case 2://review students' orders 
			tea->reviewOrder();
			break;		
		case 0:
			delete tea;
			cout << "Log Out" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "Invalid Input!" << endl;
			break;
		}
	}
}

//define a global function to enter the sub-menu of administrator
void Admin_Menu(Identity *&admin)//parameter is the "new" administrator  in the login function
{
	while (true)
	{
		admin->m_OperMenu();
		//convert the parent class object (Identity admin) into child class(Administrator Adm) to access more son class properties 
		Administrator* Adm = (Administrator*)admin;

		int select;
		cin >> select;
		switch(select)
		{
		case 1://addUser			
			Adm->addUser();
			break;
		case 2://show user			
			Adm->showUser();
			break;
		case 3://show computer lab
			Adm->showComputerLab();
			break;
		case 4://clear all order records 
			Adm->clearRecord();			
			break;		
		case 0:
			delete admin;
			cout << "Log Out" << endl;
			system("pause");
			system("cls");
			return;
		default:
			cout << "Invalid Input!" << endl;
			break;
		}
	}
}

//define a global function to log in
void Login(string FileName, int UserType)
{
	//create a pointer of Identity(parent class) to refer to  different types of users student/teacher/admin (son class)
	Identity* User = NULL; 

	//read file to check whether the user exists or not
	ifstream ifs;
	ifs.open(FileName, ios::in);

	//check whether the file exists or not
	if (!ifs.is_open())
	{
		cout << "File does not exist!" << endl;
		ifs.close();
		return;
	}
	//receive info of user
	string username;
	string pwd;
    int id = 0;	
	if (UserType == 1)
	{
		
		cout << "Please enter your student ID (number): " << endl;		
		while (!(cin >> id)) //cin>> id, and check if cin >>id is correct; if not correct, !(cin>>id) = true, go into the while(){}
		{
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;				
			}
			cout << "Invalid Input! Please re-enter a correct ID number." << endl;
		}					
	}
	else if (UserType == 2)
	{
		cout << "Please enter your teacher ID: " << endl;
		while (!(cin >> id))
		{
			cin.clear();
			while (cin.get() != '\n')
			{
				continue;
			}
			cout << "Invalid Input! Please re-enter a correct ID number." << endl;			
		}		
	}
	cout << "Please enter your username (6 characters): " << endl;
	while (true)
	{
		cin >> username;
		if (username.size() == 6)
		{
			break;			
		}
		
		cout << "Invalid Name! Please re-enter your username (6 characters):" << endl;
	}	
	cout << "Please enter your password: (8 characters): " << endl;
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

	if (UserType == 1)//student
	{
		int fId = 0;//ID get from the student file
		string fUsername; //ID get from the student file
		string fPwd;//ID get from the student file
		while (ifs >> fId && ifs >> fUsername && ifs >> fPwd)//read one line
		{
			if (fId == id && fUsername == username && fPwd == pwd)
			{
				cout << "Student Logs in Successfully!" << endl;
				system("pause");
				system("cls");
				User = new Student(id, username, pwd);
				//go into the submenu of student class
				Stu_Menu(User);
				return;
			}			
		}
	}
	else if (UserType == 2)//teacher
	{
		int fId = 0;
		string fUsername;
		string fPwd;
		while (ifs >> fId && ifs >> fUsername && ifs >> fPwd)//read one line
		{
			if (fId == id && fUsername == username && fPwd == pwd)
			{
				cout << "Teacher Logs in Successfully!" << endl;
				system("pause");
				system("cls");
				User = new Teacher(id, username, pwd);
				//go into the submenu of teacher class
				Tea_Menu(User);
				return;
			}
			
		}
	}
	else if (UserType == 3)//administrator
	{
		string fUsername;
		string fPwd;
		while (ifs >> fUsername && ifs >> fPwd)//read one line
		{
			if (fUsername == username && fPwd == pwd)
			{
				cout << "Administrator Logs in Successfully!" << endl;
				system("pause");
				system("cls");
				User = new Administrator(username, pwd);
				//go into the menu of Administrator class
				Admin_Menu(User);
				return;
			}
		}
	}
	else
	{
		cout << "User cannot be found!" << endl;
		cout << "Login failed!" << endl;
	}
	system("pause");
	system("cls");
}


int main()
{
	int select;
	while (true)
	{
		cout << "************* Welcome to Computer Lab Management System!  ****************" << endl;
		cout << endl;
		cout << "\t\t-----------------------------------------\n";
		cout << "\t\t|                                       |\n";
		cout << "\t\t|            1. Student                 |\n";
		cout << "\t\t|                                       |\n";
		cout << "\t\t|            2. Teacher                 |\n";
		cout << "\t\t|                                       |\n";
		cout << "\t\t|            3. Administrator           |\n";
		cout << "\t\t|                                       |\n";
		cout << "\t\t|            0. Exit                    |\n";
		cout << "\t\t|                                       |\n";
		cout << "\t\t-----------------------------------------\n";
		cout << endl;	
		cout << "Please select your identity: " << endl;
		cin >> select;
		switch (select)
		{
		case 1:
			Login(STUDENT_FILE, 1);
			break;
		case 2:
			Login(TEACHER_FILE, 2);
			break;
		case 3:
			Login(ADMIN_FILE, 3);
			break;
		case 0:
			cout << "Thanks for using!" << endl;
			system("pause");
			return 0; //exit the main() function
			break;
		default:
			cout << "Invalid input! Please re-enter a valid choice." << endl;
			system("pause");
			system("cls");
			break;
	    }		
	}	
	system("pause");
	return 0;
}