#include<iostream>
#include<string>
#include<assert.h>

using namespace std;

void ReverseStringHappyPathTest();
string ReverseString(string input);

void UnitTest()
{
	ReverseStringHappyPathTest();
}

void ReverseStringHappyPathTest()
{
	string test_str = "1234";
	assert(ReverseString(test_str) == "4321");
}

string ReverseString(string input)
{
	string reversed;

	for (int index = input.size() - 1; index >= 0; --index)
	{
		reversed += input[index];
	}
	return reversed;
}

int main()
{
	UnitTest();

	string input;

	cout << "Enter string: ";
	cin >> input;

	cout << "Reversed String: " << ReverseString(input) << endl;

	system("pause");
	return 0;
}