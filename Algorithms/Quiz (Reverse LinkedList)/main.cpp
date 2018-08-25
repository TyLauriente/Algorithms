#include<iostream>
#include"..\LinkedList\LinkedList.h"

using namespace std;


int main()
{
	LinkedList<int> list;

	for (int index = 0; index < 10; ++index)
	{
		list.AddLast(index);
	}

	for (int index = 0; index < 10; ++index)
	{
		cout << list.Get(index) << ", ";
	}
	list.Reverse();
	cout << endl;
	cout << "Reversed: " << endl;
	for (int index = 0; index < 10; ++index)
	{
		cout << list.Get(index) << ", ";
	}

	cout << endl;
	system("pause");
	return 0;
}