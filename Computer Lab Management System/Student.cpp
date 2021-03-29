#include <iostream>
using namespace std;
#include "Student.h"
#include <fstream>
#include "GlobalFile.h"
#include "OrderFile.h"

Student::Student()
{

}

Student::Student(int sid, string name, string pwd)
{
	this->m_SID = sid;
	this->m_Username = name;
	this->m_Password = pwd;

	this->initVector();
}

void Student::initVector()
{
	//make sure vectors are empty before they are used to store data 

	vCom.clear();
	//read data from file	
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "Fail to read computer file!" << endl;
		return;
	}
	ComputerLab c;
	while (ifs >> c.m_ComId && ifs >> c.m_comlabMax)
	{
		vCom.push_back(c);
	}
	ifs.close();
}



//abstract function in parent class must be rewritten in child class
void Student::m_OperMenu()
{
	cout << "********************************* Welcome " << this->m_Username << "!********************************" << endl;
	cout << endl;
	cout << "\t\t---------------------------------------------\n";
	cout << "\t\t|                                           |\n";
	cout << "\t\t|            1. Submit orders               |\n";
	cout << "\t\t|                                           |\n";
	cout << "\t\t|            2. Show My Orders              |\n";
	cout << "\t\t|                                           |\n";
	cout << "\t\t|            3. Show All Orders             |\n";
	cout << "\t\t|                                           |\n";
	cout << "\t\t|            4. Cancel my Orders            |\n";
	cout << "\t\t|                                           |\n";
	cout << "\t\t|            0. Logout                      |\n";
	cout << "\t\t|                                           |\n";
	cout << "\t\t---------------------------------------------\n";
	cout << endl;

	cout << "Please select a function: " << endl;
}

//submit reservation request
void Student::submitOrder()
{
	cout << "Open time: Monday ~ Friday, 9:00AM - 5:00PM" << endl;
	cout << "Please choose a date you want to use the computer lab (number): " << endl;
	cout << "1. Monday"<<endl;
	cout << "2. Tuesday" << endl;
	cout << "3. Wednesday" << endl;
	cout << "4. Thursday" << endl;
	cout << "5. Friday" << endl;
	int date = 0;	
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "Invalid choice! Please enter a correct number." << endl;
	}
	
	int time = 0;
	cout<<"Please choose a time period you want to use the computer lab (number): " << endl;
	cout << "1. 9:00 AM - 12:00 PM" << endl;
	cout << "2. 12:00 PM - 5:00 PM" << endl;
	while (true)
	{
		cin >> time;
		if (time == 1 || time == 2)
		{
			break;
		}
		cout << "Invalid choice! Please enter a correct number." << endl;
	}

	cout << "Please choose a computer lab (number): " << endl;
	
	cout<<"*** "<<vCom.size()<<" Labs Available! ***"<<endl;	
	for (int i = 0; i < vCom.size(); i++)
	{
		cout <<this->vCom[i].m_ComId << " Lab Capacity: " << this->vCom[i].m_comlabMax << endl;//***
		cout << "----" << endl;
	}

	int lab = 0;
	while (true)
	{
		cin >> lab;
		if (lab >0 && lab <= vCom.size())
		{
			break;
		}
		cout << "Invalid choice! Please enter a correct lab ID number." << endl;
	}
	cout << "Order submitted successfully! Waiting for reveiw and approval. " << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
	ofs << "Date:" << date << " ";
	ofs << "Time:" << time << " ";
	ofs << "LabID:" << lab << "  ";
	ofs << "StuID:" << this->m_SID << " ";
	ofs << "StuName:" << this->m_Username << " ";
	ofs<<"OrderStatus:" <<2<< endl;
	ofs.close();
	system("pause");
	system("cls");

}

void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_orderNum == 0)
	{
		cout << "No Order Records!" << endl;
		system("pause");
		system("cls");
		return;
	}
	
	cout << "-------All of My Orders-------" << endl;

	for (int i = 0; i < of.m_orderNum; i++)
	{
		cout << "Order " << i + 1 << endl;
		if (atoi(of.m_orderRecords[i]["StuID"].c_str()) == this->m_SID)//convert string to C++ type integer
		{			
			int d = atoi(of.m_orderRecords[i]["Date"].c_str());
			switch (d)
			{
			case 1:
				cout << "Order Date: Monday" << endl;
				break;
			case 2:
				cout << "Order Date: Thuesday" << endl;
				break;
			case 3:
				cout << "Order Date: Wednesday" << endl;
				break;
			case 4:
				cout << "Order Date: Thursday" << endl;
				break;
			case 5:
				cout << "Order Date: Friday" << endl;
				break;
			default:
				break;
			}
			cout << "Time: " << (of.m_orderRecords[i]["Time"] == "1" ? "9:00 AM - 12:00 PM":"12:00 PM - 5:00 PM") << endl;
			cout << "LabID: " << of.m_orderRecords[i]["LabID"] << endl;
			// 1 approved ; 2 under review ;-1 disapproved ; 0 canceled
			int s = atoi(of.m_orderRecords[i]["OrderStatus"].c_str());
			switch (s)
			{
			case 0:
				cout << "Order Status: Canceled" << endl;
				break;
			case 1:
				cout << "Order Status: Approved" << endl;
				break;
			case 2:
				cout << "Order Status: Under Review" << endl;
				break;
			case -1:
				cout << "Order Status: Rejected" << endl;
				break;							
			default:
				cout << "Abnormal Order Status! Please contact xxx@email.com for help. " << endl;
				break;
			}
			cout << endl;
		}
	}
	system("pause");
	system("cls");
}

void Student::showAllOrder()
{
	OrderFile of;
	of.printOrder();
	system("pause");
}
	

void Student::cancelOrder()
{
	OrderFile of;	
	if (of.m_orderNum == 0)
	{
		cout << "No Order Records!" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "***Only Orders Under Review or Approved Can Be Canceled***" << endl;	
	cout << endl;
	int index = 1;
	vector<int> v;//store the orders that can be canceled
	for (int i = 0; i < of.m_orderNum; i++)
	{
		if (this->m_SID == atoi(of.m_orderRecords[i]["StuID"].c_str()))
		{
			if (of.m_orderRecords[i]["OrderStatus"] == "1" || of.m_orderRecords[i]["OrderStatus"] == "2")//1 approved 2 under review 
			{
				v.push_back(i);

				cout << "Order " << index++ << endl;
				cout << "Date: ";
				int d = atoi(of.m_orderRecords[i]["Date"].c_str());
				switch (d)
				{
				case 1:
					cout << "Monday" << endl;
					break;
				case 2:
					cout << "Thuesday" << endl;
					break;
				case 3:
					cout << "Wednesday" << endl;
					break;
				case 4:
					cout << "Thursday" << endl;
					break;
				case 5:
					cout << "Friday" << endl;
					break;
				default:
					break;
				}

				cout << "Time: " << (of.m_orderRecords[i]["Time"] == "1" ? "9:00 AM - 12:00 PM" : "12:00 PM - 5:00 PM") << endl;
				cout << "LabID: " << of.m_orderRecords[i]["LabID"] << endl;
				cout << "OrderStatus: " << (of.m_orderRecords[i]["OrderStatus"] == "1" ? "Approved" : "Under Review") << endl;
				cout << endl;
			}
		}
	}
		
		cout << "Please select the order you want to cancel (enter 0 if you want to give up canceling)." << endl; 
		
		int select = 0;
		while (true)
		{
			cin >> select;
			if (select >= 0 && select <= v.size())
			{
				if (select == 0)
				{
					break;
				}
				else
				{
					of.m_orderRecords[v[select - 1]]["OrderStatus"] = "0";
					
					of.updateOrder();
					cout << "Order canceled Successfully!" << endl;
					break;
				}
			}
			cout << "Invalid Input! Please re-enter the ID number of order you want to cancel." << endl;
		}		
	
	system("pause");
	system("cls");
}

