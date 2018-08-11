#include<iostream>
#include"Stack.h"
#include"LinkedList.h"
#include"Queue.h"

using namespace std;

int main()
{
	Queue<int>* test1 = new Queue<int>();

	test1->Push(0);
	test1->Push(1);
	test1->Push(2);

	Queue<int> test = std::move(*test1);
	
	//test = *test1;

	delete test1;

	for (int index = 0; index < 3; ++index)
	{
		cout << test.Pop() << endl;
	}

	system("pause");
	return 0;
}