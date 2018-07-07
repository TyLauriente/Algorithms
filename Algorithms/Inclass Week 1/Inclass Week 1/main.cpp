#include<iostream>
#include<assert.h>

using namespace std;

//Constants
const int MAX_ARRAY = 5;


//Forward Decleration
float CalculateAverage(int size, int arr[]);
void CalculateAverageHappyPathTest();
void CalculateAverageArrayIsEmptyTest();

//Funtions
void UnitTest()
{
	CalculateAverageHappyPathTest();
	CalculateAverageArrayIsEmptyTest();
}

void CalculateAverageHappyPathTest()
{
	int size = 5;
	int arr[5] = { 1, 2, 3, 4, 5 };
	assert(CalculateAverage(size, arr) == 3);
}

void CalculateAverageArrayIsEmptyTest()
{
	int size = 5;
	int arr[5] = { 0 };
	assert(CalculateAverage(size, arr) == 0);
}

float CalculateAverage(int size, int arr[])
{
	if (size != 0)
	{
		float average = 0;
		for (int index = 0; index < size; index++)
		{
			average += static_cast<float>(arr[index]);
		}
		return average / size;
	}
	else
	{
		return 0;
	}
}

//Main
int main()
{
	int size = 0;
	int arr[MAX_ARRAY];
	UnitTest();

	while (size <= 0 || size > MAX_ARRAY)
	{
		cout << "Array size: ";
		cin >> size;
	}

	for (int index = 0; index < size; ++index)
	{
		system("cls");
		cout << "Enter number" << endl;
		cout << "Array pos " << index << ": ";
		cin >> arr[index];
	}

	system("cls");

	cout << "The average of all your numbers is: " << CalculateAverage(size, arr) << endl;

	system("pause");
	return 0;
}