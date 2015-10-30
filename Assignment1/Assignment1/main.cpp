#include "Evaluate.cpp"

int main()
{
	Evaluate input;
	double test;
	string expression = "";
	
	cout << "Enter an equation: ";
	getline(cin, expression);
	test = input.Eval(expression);

	cout << "Input expression: "<< expression << endl;
	cout << "Output: " << test;
	cin.get();
	return 0;
}