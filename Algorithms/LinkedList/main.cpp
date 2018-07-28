#include"Node.h"
#include"LinkedList.h"

#include<iostream>

using namespace std;

LinkedList<int> list;


void TryLeak()
{
	for (int index = 0; index < 1000; index++)
	{
		list.AddLast(index);
		list.AddFirst(index);
	}
}

int main()
{
	while (true)
	{
		system("pause");
		for (int index = 0; index < 1000; ++index)
		{
			TryLeak();
			system("cls");
			cout << index << endl;
		}

		list.~LinkedList();
	}


	system("pause");
	return 0;
}