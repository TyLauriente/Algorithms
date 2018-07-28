#include<iostream>
#include"UnorderedArray.h"

int main()
{
	UnorderredArray<int> iArray(1);
	iArray[0] = 10;
	iArray.Add(15);
	iArray.Add(2);
	iArray.Add(6);
	iArray.Add(12);
	iArray.Add(17);
	iArray.Add(54);
	iArray.Add(33);
	iArray.Add(5);
	

	std::cout << "Result: " << iArray.BinarySearch(33) << std::endl;
	iArray.PrintAll();
	

	system("pause");
	return 0;
}