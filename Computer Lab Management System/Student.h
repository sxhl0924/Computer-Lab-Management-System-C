#pragma once
#include<iostream>
using namespace std;
#include <string>
#include "Identity.h"
#include <vector>
#include "ComputerLab.h"
#include "OrderFile.h"

class Student: public Identity
{
public:
	Student();//default constructor

	Student(int id, string name, string pwd);//parameterized constructor

	//abstract function in parent class must be rewritten in child class
	virtual void  m_OperMenu();

	//submit reservation request
	void submitOrder();

	void showMyOrder();

	void showAllOrder();

	void cancelOrder();

	void initVector();

	//create a vector to store info of computer lab
	vector<ComputerLab> vCom;

	int m_SID = 0; //student ID



	//~Student();



};

