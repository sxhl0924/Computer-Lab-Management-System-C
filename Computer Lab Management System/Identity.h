#pragma once
#include<iostream>
using namespace std;
#include <string>

//Abstract base class
class Identity
{
public:	
	
	//operation menu
	virtual void  m_OperMenu() = 0; //pure virtual function(or abstract function)

	string m_Username;
	string m_Password;	

};

