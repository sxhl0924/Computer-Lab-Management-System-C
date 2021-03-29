#include "OrderFile.h"
#include<string>


void OrderFile::getData(string &s)
{	
	//s Date:1
	int pos = s.find(":"); //pos = 4
	if (pos != -1)
	{
		string key = s.substr(0, pos);//key = date
		string value = s.substr(pos + 1, s.size());//size = 9, pos = 4
		//cout << "Key = " << key << endl;
		//cout << "Value = " << value << endl;
	    m.insert(make_pair(key, value));	
		//cout << "*" << m.size() << "*" << endl;		
	}
}

OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);
	string date;
	string time;
	string labID;
	string stuID;
	string stuName;
	string status;
	int m_orderNum = 0;

	while (ifs >> date && ifs >> time && ifs >> labID && ifs >> stuID && ifs >> stuName && ifs >> status)
	{
		this->getData(date);
		this->getData(time);
		this->getData(labID);
		this->getData(stuID);
		this->getData(stuName);
		this->getData(status);
		this->m_orderRecords.insert(make_pair(this->m_orderNum, this->m));
		this->m_orderNum++;
		this->m.clear();
	}

	ifs.close();
	//for (map<int, map<string, string>>::iterator it = m_orderRecords.begin(); it != m_orderRecords.end(); it++)
	//{
		//cout << "Order " << it->first + 1 << endl;

		//for (map<string, string>::iterator mit = (*it).second.begin(); mit != (*it).second.end(); mit++)
		//{
			//cout << mit->first << ": " << mit->second << endl;

		//}
		//cout << "-----------------------------" << endl;
	//}
}		

void OrderFile::updateOrder()
{
	if (this->m_orderNum == 0)
	{
		return;
	}
	ofstream ofs(ORDER_FILE, ios::out|ios::trunc);
	for (int i = 0; i < m_orderNum; i++)
	{
		ofs << "Date:" << this->m_orderRecords[i]["Date"]<<" ";
		ofs << "Time:" << this->m_orderRecords[i]["Time"]<<" ";
		ofs << "LabID:" << this->m_orderRecords[i]["LabID"]<<" ";
		ofs << "StuID:" << this->m_orderRecords[i]["StuID"]<<" ";
		ofs << "StuName:" << this->m_orderRecords[i]["StuName"]<<" ";
		ofs << "OrderStatus:" << this->m_orderRecords[i]["OrderStatus"]<<endl;
	}
	ofs.close();
}

void OrderFile:: printOrder()
{
	
	if (this->m_orderNum == 0)
	{
		cout << "No Order Records!" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < this->m_orderNum; i++)
	{
		cout << "Order " << i + 1 << endl;
		int d = atoi(this->m_orderRecords[i]["Date"].c_str());
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
		cout << "Time: " << (this->m_orderRecords[i]["Time"] == "1" ? "9:00 AM - 12:00 PM" : "12:00 PM - 5:00 PM") << endl;
		cout << "Lab ID: " << this->m_orderRecords[i]["LabID"] << endl;
		cout << "Student ID: " << this->m_orderRecords[i]["StuID"] << endl;
		cout << "Student Username: " << this->m_orderRecords[i]["StuName"] << endl;
		
		int s = atoi(this->m_orderRecords[i]["OrderStatus"].c_str());
		switch (s)// 1 approved 2 under review -1 disapproved 0 canceled
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
		cout << "--------------------------" << endl;
	}
}
