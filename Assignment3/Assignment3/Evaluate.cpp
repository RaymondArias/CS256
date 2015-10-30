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
	

	//main evaluator for the program
	void evaluate(string input)
	{

		TokenizeStatement(input);
		string firstValue = _exprTokens.at(0);
		vector<string> fileName;
		lookUpFiles("*.pst", fileName);

		//check for commands
		if (firstValue == "CREATE")
		{
			writeToFile();

		}
		else if (firstValue == "RUN")
		{
			runFile();
		}
		else if (firstValue == "DIR")
		{
			for (int i = 0; i < fileName.size(); i++)
			{
				cout << fileName[i] << endl;
			}
			//DIRfileSearch();
		}
		else if (firstValue == "VARLIST")
		{

			printOutVariable();
		}
		else
		{
			cout << "Error command not recogized" << endl;
			cout << "Command List" << endl << endl;
			cout << "CREATE:  Create new file" << endl;
			cout << "SAVE:    Save data to file" << endl;
			cout << "RUN:     Run file" << endl;
			cout << "DIR:     Display all.pst files that can be executed" << endl;
			cout << "VARLIST: Display variable values for this file" << endl;
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

	
	//search linked list for variable name
	void printVariable()
	{
		list->displayVariable(_exprTokens[1]);
	}
	void writeToFile()
	{

		string fileName = _exprTokens[1];
		string userInput = "";
		ofstream fileWriteTo;
	

		
		fileWriteTo.open(fileName.c_str());
		if (fileWriteTo.fail())
		{
			cout << fileName << " failed to open" << endl;
			return;
		}

		cout << "Enter in the all commands for this file, when finished type SAVE: " << endl;
		while (true)
		{
			
			getline(cin, userInput);

			if (userInput == "SAVE")
				break;
			fileWriteTo << userInput << endl;
		}
		fileWriteTo.close();
	}
	void runFile()
	{
		string fileName = _exprTokens[1];
		string fileData = "";
		vector <string> tokenizedFile;
		ifstream fileReading;
		fileReading.open(fileName.c_str());
		if (fileReading.fail())
		{
			cout << fileName << " failed to open" << endl;
			return;
		}
		list = new LinkedList();
		while (!fileReading.eof())
		{
			getline(fileReading, fileData);
			TokenizeFileReading(fileData, tokenizedFile);
			if (fileReading.eof())
				break;
			
			
			if (tokenizedFile[0] == "OUT")
			{
				printFileVar(tokenizedFile);
			}
			else if (tokenizedFile[0] == "RUN")
			{
				runFile(tokenizedFile[1]);
			}
			else if (tokenizedFile[0] == "VARLIST")
			{
				printOutVariable();
			}
			else if (tokenizedFile[0] == "SAVE")
			{

			}
			else
			{
				evalFile(tokenizedFile);
			}
			tokenizedFile.clear();
		}
		fileReading.close();
	}
	void runFile(string fileName_)
	{
		string fileName = fileName_;
		string fileData = "";
		vector <string> tokenizedFile;
		ifstream fileReading;
		fileReading.open(fileName.c_str());

		if (fileReading.fail())
		{
			cout << fileName << " failed to open" << endl;
			return;
		}
		//list = new LinkedList();
		while (!fileReading.eof())
		{
			getline(fileReading, fileData);
			TokenizeFileReading(fileData, tokenizedFile);
			if (fileReading.eof())
				break;

			if (tokenizedFile[0] == "OUT")
			{
				printFileVar(tokenizedFile);
			}
			else if (tokenizedFile[0] == "RUN")
			{
				runFile(tokenizedFile[1]);
			}
			else
			{
				
				evalFile(tokenizedFile);
				
			}

			 
			tokenizedFile.clear();
		}
		fileReading.close();

	}
	void TokenizeFileReading(string expr, vector <string> &tokenizedFile)

	{

		string a[100];

		char* context = NULL;

		char *pch = strtok_s((char *)expr.c_str(), " ", &context);

		while (pch != NULL)

		{

			tokenizedFile.push_back(pch);

			//cout << pch << endl;

			pch = strtok_s(NULL, " ", &context);

		}

	}
	double evalFile(vector <string> _exprTokens)
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
				if (list->searchVariable(_exprTokens[i]))
				{
					if (list->getNumData(_exprTokens[i]) != NULL)
					{
						double numPush = list->getNumData(_exprTokens[i]);
						nums.push(numPush);

					}
					else
					{
						nums.push(0.0);
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
	void printFileVar(vector <string> &tokenizedFile)
	{
		list->displayVariable(tokenizedFile[1]);
	}
	void fileSearch()
	{
		system("dir *.pst");
	}
	void printOutVariable()
	{
		list = new LinkedList();
		string fileName = _exprTokens[1];
		string fileData = "";
		vector <string> tokenizedFile;
		ifstream fileReading;
		fileReading.open(fileName.c_str());
		if (fileReading.fail())
		{
			cout << fileName << " failed to open" << endl;
			return;
		}
		while (!fileReading.eof())
		{
			getline(fileReading, fileData);
			TokenizeFileReading(fileData, tokenizedFile);
			if (fileReading.eof())
				break;

			if (tokenizedFile[0] == "RUN")
			{
				runFileDisplayVar(tokenizedFile[1]);
			}
			else if (tokenizedFile[0] != "OUT")
			{
				evalFile(tokenizedFile);
			}
			
			tokenizedFile.clear();
		}
		fileReading.close();

		list->displayList();
	}
	void runFileDisplayVar(string fileName_)
	{
		string fileName = fileName_;
		string fileData = "";
		vector <string> tokenizedFile;
		ifstream fileReading;
		fileReading.open(fileName.c_str());
		if (fileReading.fail())
		{
			cout << fileName << " failed to open" << endl;
			return;
		}
		//list = new LinkedList();
		while (!fileReading.eof())
		{
			getline(fileReading, fileData);
			TokenizeFileReading(fileData, tokenizedFile);
			if (fileReading.eof())
				break;

			
			if (tokenizedFile[0] == "RUN")
			{
				runFileDisplayVar(tokenizedFile[1]);
			}
			else if ((tokenizedFile[0] != "OUT") || (tokenizedFile[0] != "SAVE") || (tokenizedFile[0] != "VARLIST"))
			{

				evalFile(tokenizedFile);

			}


			tokenizedFile.clear();
		}
		fileReading.close();

	}
	void lookUpFiles(string dirPath, vector<string> &fileNames)
	{
		WIN32_FIND_DATA ffd;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		DWORD dwError = 0;

		// Clear out Filenames Vector
		fileNames.clear();

		wstring dirPathWildCard(dirPath.begin(), dirPath.end());

		hFind = FindFirstFile(dirPathWildCard.c_str(), &ffd);
		if (INVALID_HANDLE_VALUE == hFind)
		{
			cout << "Invalid Directory: " << dirPathWildCard.c_str() << endl;
			return;
		}

		// List all the files in the directory with some info about them.
		do
		{
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// Ignore Subdirectories
			}
			else
			{
				wstring fileName1 = ffd.cFileName;
				string fileName2(fileName1.begin(), fileName1.end());
				fileNames.push_back(fileName2);
			}
		} while (FindNextFile(hFind, &ffd) != 0);

		dwError = GetLastError();
		if (dwError != ERROR_NO_MORE_FILES)
		{
			cout << "Unable to read filenames" << endl;
		}

		FindClose(hFind);
	}
	
};