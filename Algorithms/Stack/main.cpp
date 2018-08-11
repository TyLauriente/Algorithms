#include<iostream>
#include<string>
#include<fstream>
#include"Stack.h"
#include"LinkedList.h"
#include"Queue.h"

using namespace std;

const int AMOUNT_OF_CHARACTERS = 3;

char openSymbols[AMOUNT_OF_CHARACTERS] = { '(', '[', '{' };
char closeSymbols[AMOUNT_OF_CHARACTERS] = { ')', ']', '}' };


bool Contains(char arr[], char character)
{
	for (int index = 0; index < AMOUNT_OF_CHARACTERS; ++index)
	{
		if (arr[index] == character)
		{
			return true;
		}
	}
	return false;
}

char InvertChar(char symbol)
{
	for (int index = 0; index < AMOUNT_OF_CHARACTERS; ++index)
	{
		if (openSymbols[index] == symbol)
		{
			return closeSymbols[index];
		}
		else if (closeSymbols[index] == symbol)
		{
			return openSymbols[index];
		}
	}
}

string GetStringOfFile(string fileName)
{
	ifstream file(fileName);

	string returnStr;
	string temp;

	while (getline(file, temp))
	{
		returnStr += temp;
	}
	return returnStr;
}

bool HasError(string code)
{
	Stack<char> stack;
	
	for (char c : code)
	{
		if (Contains(openSymbols, c))
		{
			stack.Push(c);
		}
		if (Contains(closeSymbols, c))
		{
			if (stack.count == 0 || stack.Pop() != InvertChar(c))
			{
				return true;
			}
		}
	}
	if (stack.count > 0)
	{
		return true;
	}
	return false;
}

int main()
{
	string test = GetStringOfFile("code.txt");

	if (HasError(test))
	{
		cout << "Has error" << endl;
	}
	else
	{
		cout << "Does not have any errors" << endl;
	}

	system("pause");
	return 0;
}