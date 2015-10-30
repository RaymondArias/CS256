#include <iostream>
#include <string>
#include <stack>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <Windows.h>

using namespace std;


class Node
{
private:
	double numData;
	string stringData;
	string variableName;
	Node *next;


public:
	//add number to list
	Node(double numData, string variableName, Node *&next)
	{
		this->variableName = variableName;
		this->numData = numData;
		this->next = next;
		this->stringData = "/0";
	}
	Node(string stringData, string variableName, Node *&next)
	{
		this->stringData = stringData;
		this->variableName = variableName;
		this->numData = NULL;
		this->next = next;
	}
	Node()
	{
		next = NULL;
	}
	double getData()
	{
		return numData;
	}
	string getStrData()
	{
		return stringData;
	}
	Node * getNext()
	{
		return next;
	}
	string getVarName()
	{
		return variableName;
	}
	
	
};