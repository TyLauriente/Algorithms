#include<iostream>
#include"UnorderedArray.h"

int main()
{
	UnorderredArray<int> iArray(1);
	iArray[0] = 0;
	
	for (int index = 1; index <= 1000; ++index)
	{
		iArray.Add(index);
	}
	
	for (int index = 100; index <= 200; ++index)
	{
		iArray.RemoveByValue(index);
	}

	iArray.PrintAll();

	system("pause");
	return 0;
}