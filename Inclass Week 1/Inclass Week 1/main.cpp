#include<iostream>
#include<assert.h>

using namespace std;

float CalculateAverage(int size, int arr[]);

void UnitTest()
{
	int size = 5;
	int arr[5] = { 1, 2, 3, 4, 5 };
	assert(CalculateAverage(size, arr) == 3);
}

float CalculateAverage(int size, int arr[])
{
	float average = 0;
	for (int index = 0; index < size; index++)
	{
		average += static_cast<float>(arr[index]);
	}
	
	return average / size;
}

int main()
{
	UnitTest();


	system("pause");
	return 0;
}