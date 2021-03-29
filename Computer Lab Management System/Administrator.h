#pragma once
#include<iostream>
using namespace std;
#include <string>
#include "Identity.h"
#include <vector>;
# include "Student.h"
#include "Teacher.h"
#include "ComputerLab.h"

class Administrator : public Identity
{
public:
	Administrator();//default constructor

	Administrator(string name, string pwd);//parameterized constructor

	//abstract function in parent class must be rewritten in child class
	virtual void  m_OperMenu();

	//add user
	void addUser();

	//show user info
	void showUser();

	//show info of computer Lab
	void showComputerLab();
	
	//clear info of all revervation orders
	void clearRecord();

	//initialize vector
	void initVector();

	//check whether the new user to be added has alread existed in the file
	bool checkRepeat(int id, int type);//true = repeat, false = no repeat

	//create a vector to store student data read from file
	vector<Student> vStu;

	//create a vetor to store teacher data read from file
	vector<Teacher>vTea;

	//create a vector to store info of computer lab
	vector<ComputerLab> vCom;
	
};
