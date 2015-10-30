#include <iostream>
#include <string>
#include <stack>
#include <stdlib.h>

using namespace std;

class Evaluate
{
private:
	string input;
	stack<double> nums;

public:
	Evaluate()
	{

	}
	~Evaluate()
	{

	}
	double Eval(string input)
	{
		//int strLength = input.length();
		double num = 0;
		double result = 0;
		double num1 = 0;
		double num2 = 0;
		string parsedInput = "";

		for (int i = 0; i < input.length(); i++)
		{
			
			if (input[i] == '+')
			{
				
				
				num1 = nums.top();
				nums.pop();
				num2 = nums.top();
				nums.pop();
				result = num1 + num2;
				nums.push(result);
			}
			else if (input[i] == '-')
			{
				num1 = nums.top();
				nums.pop();
				num2 = nums.top();
				nums.pop();
				result = num2 - num1;
				nums.push(result);
			}
			else if (input[i] == '*')
			{
				num1 = nums.top();
				nums.pop();
				num2 = nums.top();
				nums.pop();
				result = num1 * num2;
				nums.push(result);
			}
			else if (input[i] == '/')
			{
				num1 = nums.top();
				nums.pop();
				num2 = nums.top();
				nums.pop();
				result = num2 / num1;
				nums.push(result);


			}
			else if (input[i] == ' ')
			{
				if (parsedInput != "")
				{
					num = stod(parsedInput);
					parsedInput = "";
					nums.push(num);
				}
			}

			else if ((input[i] != '+') || (input[i] != '-') || (input[i] != '*') || (input[i] != '/'))
			{
				parsedInput += input[i];
			}

			num1 = 0;
			num2 = 0;
		}
		while (!nums.empty())
		{
			num1 = nums.top();
			nums.pop();

		}
		
		return result;
		
	}


};