#pragma once
#include<iostream>
using namespace std;
#include <string>
#include "Identity.h"

class Teacher : public Identity
{
public:
	Teacher();//default constructor

	Teacher(int id, string name, string pwd);//parameterized constructor

	//abstract function in parent class must be rewritten in child class
	virtual void  m_OperMenu();
	

	void showAllOrder();	

	void reviewOrder();

	int m_TID; //student ID

	



};

