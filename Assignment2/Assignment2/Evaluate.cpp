#include "LinkedList.cpp"


class Evaluate
{
private:
	string input;
	string firstValue;
	stack<double> nums;
	vector<string> _exprTokens;
	LinkedList *list;
	

public:
	Evaluate()
	{
		list = new LinkedList();
	}
	~Evaluate()
	{

	}

	//Evaluates numeric expressions
	double Eval()
	{
		this->input = input;
		//int strLength = input.length();
		double num = 0;
		double result = 0;
		double num1 = 0;
		double num2 = 0;
		

		for (int i = 0; i < _exprTokens.size(); i++)
		{
			if (i == 0)
			{
				this->firstValue = _exprTokens.at(i);
			}
			else
			{
				if (convertNumToString(_exprTokens[i]))
				{
					cout << "Error trying to convert number intro string in a numeric statement\n";
				}
				else if (convertStringToNum(_exprTokens[i]))
				{
					
					nums.push(convertToNum());	
				
					
				}
				else if (list->searchVariable(_exprTokens[i]))
				{
					if (list->getNumData(_exprTokens[i]) != NULL)
					{
						double numPush = list->getNumData(_exprTokens[i]);
						nums.push(numPush);

					}
					else
					{
						cout << "ERROR Variable is not a number.\n";
					}
				}
				else if (_exprTokens.at(i) == "+")
				{


					num1 = nums.top();
					nums.pop();
					num2 = nums.top();
					nums.pop();
					result = num1 + num2;
					nums.push(result);
				}
				else if (_exprTokens.at(i) == "-")
				{
					num1 = nums.top();
					nums.pop();
					num2 = nums.top();
					nums.pop();
					result = num2 - num1;
					nums.push(result);
				}
				else if (_exprTokens.at(i) == "*")
				{
					num1 = nums.top();
					nums.pop();
					num2 = nums.top();
					nums.pop();
					result = num1 * num2;
					nums.push(result);
				}
				else if (_exprTokens.at(i) == "/")
				{
					num1 = nums.top();
					nums.pop();
					num2 = nums.top();
					nums.pop();
					result = num2 / num1;
					nums.push(result);


				}
				else if (_exprTokens.at(i) == "=")
				{
					//assign to linked list;
					list->addNum(result, firstValue);
					break;
				}
				else if (!checkIfVarOrNum(_exprTokens[i]))
				{
					nums.push(0.0);
				}
				else if ((_exprTokens.at(i) != "+") || (_exprTokens.at(i) != "-") || (_exprTokens.at(i) != "*") || (_exprTokens.at(i) != "/"))
				{
					double numberPushed = stod(_exprTokens.at(i));
					nums.push(numberPushed);

				}
				else
				{
					nums.push(0.0);
				}
				

				num1 = 0;
				num2 = 0;
			}
			
		}
		while (!nums.empty())
		{
			num1 = nums.top();
			nums.pop();

		}

		return result;

	}

	//main evaulater for program
	void evaluate(string input)
	{
		
		TokenizeStatement(input);
		string firstValue = _exprTokens.at(0);
		
		//if the first value is not equal to out then its a variable
		if (firstValue != "OUT")
		{
			if (checkDataType())
			{

				Eval();

			}
			else
			{

				putString();


			}



		}
		else
		{
			printVariable();
		}
		//list->displayList();
		_exprTokens.clear();
		
	}
	
	//tokenize expression into vector
	void TokenizeStatement(string expr)

	{

		string a[100];

		char* context = NULL;

		char *pch = strtok_s((char *)expr.c_str(), " ", &context);

		while (pch != NULL)

		{

			_exprTokens.push_back(pch);

			//cout << pch << endl;

			pch = strtok_s(NULL, " ", &context);

		}

	}

	//Check to see if second value in vector is a number or expression
	bool checkDataType()
	{
		
		for (int i = 1; i < _exprTokens.size(); i++)
		{
			for (int j = 0; j < _exprTokens[i].length(); j++)
			{
				if (_exprTokens[i][j] == '"')
				{
					return false;
				}
			}
		}
		return true;
	}
	//put a variable name and string in the linked list
	void putString()
	{
		string firstValue = _exprTokens.at(0);
		string strInput = "";
		
		for (int i = 1; i < _exprTokens.size(); i++)
		{
			string qouteParse = "";
			if ((convertNumToString(_exprTokens[i])) && (list->searchVariable(getVarName(_exprTokens[i])) && (list->getStrData(getVarName(_exprTokens[i])) != "/0")))
			{
				qouteParse = list->getStrData(getVarName(_exprTokens[i]));
				
				
			}
			else if (convertNumToString(_exprTokens[i]))
			{
				qouteParse = convertToString();
			}
			else if (convertStringToNum(_exprTokens[i]))
			{
				cout << "Error cannot convert string to num in string statment" << endl;
				return;
			}
			else
			{

				for (int j = 0; j < _exprTokens[i].length(); j++)
				{
					if (_exprTokens[i][j] != '"')
					{
						qouteParse += _exprTokens[i][j];
					}
				}
			}
				if (_exprTokens[i] == "=")
					break;

			
				
				
			strInput += qouteParse + " ";

			
		}
		
		list->addString(strInput, firstValue);
	}
	//search linked list for variable name
	void printVariable()
	{
		list->displayVariable(_exprTokens[1]);
	}

	//Searches for @ symbol to change number to string
	//returns true if the symbol is found
	bool convertNumToString(string token)
	{
		for (int i = 0; i < token.length(); i++)
		{
			
				if (token[i] == '@')
				{
					return true;
				}
			
		}
		return false;
	}

	//Search for # symbol to change string to number
	//returns true if the symbol is found
	bool convertStringToNum(string token)
	{
		for (int i = 1; i < token.length(); i++)
		{
			
				if (token[i] == '#')
				{
					return true;
				}
			
		}
		return false;

	}
	//converts string data to numeric data
	double convertToNum()
	{
		string returnString = "";
		string variableName = "";
		//check each string for the # symbol
		for (int i = 1; i < _exprTokens.size(); i++)
		{
			for (int j = 0; j < _exprTokens[i].length(); j++)
			{
				if (_exprTokens[i][j] == '#')
				{
					returnString = _exprTokens[i];
				}
			}
		}
		for (int i = 0; i < returnString.length(); i++)
		{
			if (returnString[i] != '#')
			{
				variableName += returnString[i];
			}
		}
		

		return stod(list->getStrData(variableName));
	}

	//covert number data to string data
	string convertToString()
	{
		string returnString = "";
		string variableName = "";
		//check each string for the @ symbol
		for (int i = 1; i < _exprTokens.size(); i++)
		{
			for (int j = 0; j < _exprTokens[i].length(); j++)
			{
				if (_exprTokens[i][j] == '@')
				{
					returnString = _exprTokens[i];
				}
			}
		}
		for (int i = 0; i < returnString.length(); i++)
		{
			if (returnString[i] != '@')
			{
				variableName += returnString[i];
			}
		}

		
		return to_string(list->getNumData(variableName));

	}

	//check if a tokenized string to see if its a number or variable
	bool checkIfVarOrNum(string token)
	{
		for (int i = 0; i < token.length(); i++)
		{
			if (((token[i] >= 48) && (token[i] <= 57)) || (list->searchVariable(token)))
			{
				return true;
			}
		}
		return false; 
	}

	//get variable name
	string getVarName(string token)
	{
		string parse;

		for (int i = 0; i < token.length(); i++)
		{
			if (token[i] != '@')
			{
				parse += token[i];
			}
		}
		return parse;
	}
};