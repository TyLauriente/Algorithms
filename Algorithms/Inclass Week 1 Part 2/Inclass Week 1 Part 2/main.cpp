#include<iostream>
#include<string>
#include<assert.h>

using namespace std;

//Forward Decleration
void ReverseStringHappyPathTest();
void EfficientReverseStringTest();
string ReverseString(string input);
string EfficientReverseString(string input);


//Functions
void UnitTest()
{
	ReverseStringHappyPathTest();
	EfficientReverseStringTest();
}


void ReverseStringHappyPathTest()
{
	string test_str = "1234";
	assert(ReverseString(test_str) == "4321");
}

void EfficientReverseStringTest()
{
	string test_str = "1234";
	assert(EfficientReverseString(test_str) == "4321");
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

template<typename T>
void Swap(T& input1, T& input2)
{
	T temp = input1;
	input1 = input2;
	input2 = temp;
}

string EfficientReverseString(string input)
{
	int endPos = input.size() - 1;
	char temp;
	for (int index = 0; index < input.size() / 2; ++index)
	{
		Swap(input[index], input[endPos]);
		endPos--;
	}

	return input;
}

//main
int main()
{
	UnitTest();

	string input;

	cout << "Enter string: ";
	cin >> input;

	cout << "Reversed String: " << EfficientReverseString(input) << endl;

	system("pause");
	return 0;
}