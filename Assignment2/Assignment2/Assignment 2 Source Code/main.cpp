#include "Evaluate.cpp"

int main()
{
	Evaluate input;
	string expression = "";
	
	cout << "Enter an expression: ";
	getline(cin, expression);
	while (true)
	{
		
		
		//test = input.Eval(expression);
		input.evaluate(expression);
		cout << "Enter another expression or type quit to end: ";
		getline(cin, expression);
		
		if (expression == "quit")
			break;
		
		
	}
	
	cin.get();
	return 0;
}