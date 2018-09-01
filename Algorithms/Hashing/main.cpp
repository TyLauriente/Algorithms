#include<iostream>
#include"HashTable.h"


int main()
{
	HashTable<int> table(1000001);

	for (int i = 0; i < 1000000; ++i)
	{
		table.Insert(std::to_string(i + 15), i);
	}

	std::cout << "Start" << std::endl;

	for (int i = 0; i < 1000000; ++i)
	{
		if (!table.Find(std::to_string(i + 15), i))
		{
			std::cout << "Not goord" << std::endl;
		}
	}

	std::cout << "End" << std::endl;

	std::cout << std::endl;
	system("pause");
	return 0;
}