#include <iostream>
using namespace std;
#include "Teacher.h"
#include "OrderFile.h"
#include <vector>


Teacher::Teacher()
{

}

Teacher::Teacher(int tid, string name, string pwd)
{
	this->m_TID = tid;
	this->m_Username = name;
	this->m_Password = pwd;
}

//abstract function in parent class must be rewritten in child class
void Teacher::m_OperMenu()
{
	cout << "********************************* Welcome " << this->m_Username << "!********************************" << endl;
	cout << endl;
	cout << "\t\t---------------------------------------------\n";	
	cout << "\t\t|                                           |\n";
	cout << "\t\t|            1. Show All Orders             |\n";
	cout << "\t\t|                                           |\n";
	cout << "\t\t|            2. Reveiw Orders               |\n";
	cout << "\t\t|                                           |\n";
	cout << "\t\t|            0. Logout                      |\n";
	cout << "\t\t|                                           |\n";
	cout << "\t\t---------------------------------------------\n";
	cout << endl;

	cout << "Please select a function: " << endl;
}

void Teacher::showAllOrder()
{
	OrderFile of;
	of.printOrder();
}

void Teacher::reviewOrder()
{
	OrderFile of;
	if (of.m_orderNum == 0)
	{
		cout << "No Order Records!" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "***Only Orders Under Review Can Be Reviewed ***" << endl;
	cout << endl;
	int index = 1;
	vector<int> v;
	for (int i = 0; i < of.m_orderNum; i++)
	{
		if (of.m_orderRecords[i]["OrderStatus"] == "2")//2 under review
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

	cout << "Please select the order you want to review (enter 0 if you want to give up reviewing)." << endl;

	int select = 0;
	int ret;
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
				cout << "Please make your decision on the order:" << endl;
				cout << "1. Approved " << endl;
				cout << "2. Rejected" << endl;
				while (true)
				{
					cin >> ret;
					if (ret == 1)
					{
						of.m_orderRecords[v[select - 1]]["OrderStatus"] = "1";//1 
						of.updateOrder();
						cout << "Order have been Reviewed!" << endl;
						break;
					}
					else if(ret == 2)
					{
						of.m_orderRecords[v[select - 1]]["OrderStatus"] = "-1";//-1 rejected
						of.updateOrder();
						cout << "Order have been Reviewed!" << endl;
						break;
					}

					cout << "Invalid Input! Please choose a correct decision" << endl;

					
					

				}
				
			}
				
			break;
			
		}
		cout << "Invalid Input! Please re-enter the ID number of order you want to cancel." << endl;
	}

	system("pause");
	system("cls");
}