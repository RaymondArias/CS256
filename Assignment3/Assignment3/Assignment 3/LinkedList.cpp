#include "Node.cpp"

class LinkedList
{
private:
	double numData;
	string stringData;
	string variableName;
	Node *head;

public:
	LinkedList()
	{
		head = NULL;

	}
	//adds numeric data to linked list
	void addNum(double num, string variableName)
	{
		head = new Node(num, variableName, head);
	}

	//add string data to linked list
	void addString(string stringData, string variableName)
	{
		head = new Node(stringData, variableName, head);

	}

	//outputs linked list
	void displayList()
	{
		if (head == NULL)
		{
			cout << "List is empty";
			return;
		}
		Node *traverse = head;
		while (traverse != NULL)
		{
			
			
			cout << traverse->getVarName() << ": " << traverse->getData() << endl;
			

			traverse = traverse->getNext();
		}
	}
	//outputs data for a variable
	void displayVariable(string variable)
	{
		Node *search = head;

		while (search != NULL)
		{
			if (variable == search->getVarName())
			{
				if (search->getData() == NULL)
				{
					cout << search->getStrData() << endl;
				}
				else if (search->getStrData() == "/0")
				{
					cout << search->getData() << endl;
				}
			}
			search = search->getNext();
		}
	}

	//searches if variable name is in linked list
	bool searchVariable(string varName)
	{
		Node *search = head;

		while (search != NULL)
		{
			if (varName == search->getVarName())
			{
				return true;
			}
			search = search->getNext();
		}
		return false;
	}
	//return numeric data
	double getNumData(string varName)
	{
		Node *search = head;

		while (search != NULL)
		{
			if (search->getVarName() == varName)
			{
				return search->getData();
			}
			search = search->getNext();
		}

		return 0;
	}

	//return string data
	string getStrData(string varName)
	{
		Node *search = head;

		while (search != NULL)
		{
			if (search->getVarName() == varName)
			{
				return search->getStrData();
			}
			search = search->getNext();
		}
		return "/0";
	}

};