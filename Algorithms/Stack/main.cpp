#include<iostream>
#include<string>
#include<fstream>
#include"Queue.h"
#include"StackArray.h"
#include<vector>

using namespace std;

const int AMOUNT_OF_CHARACTERS = 3;

char openSymbols[AMOUNT_OF_CHARACTERS] = { '(', '[', '{' };
char closeSymbols[AMOUNT_OF_CHARACTERS] = { ')', ']', '}' };
char operators[4] = { '+', '-', '*', '/' };

bool IsOperator(char c)
{
	for (int index = 0; index < 4; ++index)
	{
		if (operators[index] == c)
		{
			return true;
		}
	}
	return false;
}

float Evaluate(float num1, float num2, char op)
{
	if (op == '+')
	{
		return num1 + num2;
	}
	else if (op == '-')
	{
		return num1 - num1;
	}
	else if (op == '*')
	{
		return num1 * num2;
	}
	else
	{
		return num1 / num2;
	}
}

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
	StackArray<char> stack;
	
	for (char c : code)
	{
		if (Contains(openSymbols, c))
		{
			stack.Push(c);
		}
		if (Contains(closeSymbols, c))
		{
			if (stack.size == 0 || stack.Pop() != InvertChar(c))
			{
				return true;
			}
		}
	}
	if (stack.size > 0)
	{
		return true;
	}
	return false;
}

void ErrorCheckTest()
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
}

bool IsValidExpression(string expression)
{
	int operators = 0;
	int numbers = 0;

	for (int index = 0; index < expression.size(); ++index)
	{
		char c = expression[index];
		if (((c - '0') < 0 || (c - '0') > 9) && !IsOperator(c) && c != ' ')
		{
			return false;
		}
		if (index == expression.size() - 1 && !IsOperator(c))
		{
			return false;
		}
	}
	return true;
}

void PostfixCalculator(string expression)
{
	if (IsValidExpression(expression))
	{

		StackArray<float> stack;
		int base = 1;
		char lastPushed = ' ';

		for (int index = 0; index < expression.size(); ++index)
		{
			char c = expression[index];
			if (IsOperator(c))
			{
				float push = Evaluate(stack.Pop(), stack.Pop(), c);
				stack.Push(push);
				lastPushed = push;
				base = 1;
			}
			else if (c != ' ')
			{
				float push = 0;
				if (IsOperator(lastPushed))
				{
					stack.Push(push);
				}
				else
				{
					int nextNum = index + 1;
					std::vector<float> numberChars;
					numberChars.push_back(static_cast<float>(c - '0'));
					while (nextNum < expression.size() && !IsOperator(expression[nextNum]) && expression[nextNum] != ' ')
					{
						numberChars.push_back(static_cast<float>(expression[nextNum] - '0'));
						nextNum++;
						index++;
					}
					int base = numberChars.size() - 1;
					for (auto num : numberChars)
					{
						push += num * pow(10, base);
						base--;
					}
					stack.Push(push);
					base++;
				}
				lastPushed = push;
			}
		}
		string answer = expression + " = " + to_string(stack.Pop());
		std::cout << answer << endl;
		answer += "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";
		ofstream file("Postfix Results.txt", ios::app);
		file.write(answer.c_str(), answer.size());
	}
	else
	{
		cout << expression << " is not a valid postfix expression" << endl;
	}
}

int main()
{
	//ErrorCheckTest();

	string expression;
	std::cout << "Enter a postfix expression: ";
	getline(cin, expression);
	PostfixCalculator(expression);

	system("pause");
	return 0;
}