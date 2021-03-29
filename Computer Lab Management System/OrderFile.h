#pragma once
#include<iostream>
using namespace std;
#include <fstream>
#include "GlobalFile.h"
#include <map>
#include <string>

class OrderFile
{
public:
	OrderFile();

	//update order file
	void updateOrder();

	void getData(string &);

	void printOrder();

	//numbers of order records
	int m_orderNum = 0;


	//store all order data key: int(No. of records) value: map<s,s> info of each order record. 
	map<int, map<string, string>> m_orderRecords;
	map<string, string> m;

};