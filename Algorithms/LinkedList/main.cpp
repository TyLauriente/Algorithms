#include"Node.h"
#include"LinkedList.h"
#include"DoubleLinkedList.h"

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

DoubleLinkedList<int> linkList;

struct Number
{
	bool operator==(Number& other) { return (this->number == other.number); }
	int number;
	int count = 1;
};


void TryLeak()
{
	for (int index = 0; index < 1000; index++)
	{
		linkList.AddLast(index);
		linkList.AddFirst(index);
	}
}

int GetElementByValue(std::vector<Number> list, int value)
{
	int index = 0;
	for (auto element : list)
	{

		if (element.number == value)
		{
			return index;
		}
		index++;
	}
	return -1;
}

bool ContainsInList(std::vector<Number> list, int value)
{
	for (auto element : list)
	{
		if (element.number == value)
		{
			return true;
		}
	}
	return false;
}

bool Contains(std::vector<int> list, int value)
{
	for (auto element : list)
	{
		if (element == value)
		{
			return true;
		}
	}
	return false;
}



void FindRecurringNumbers(int arr[], int size)
{
	std::vector<int> usedNumbers;

	for (int index = 0; index < size; ++index)
	{
		if (Contains(usedNumbers, arr[index]))
		{
			int count = 0;
			usedNumbers.push_back(arr[index]);
			for (int index2 = 0; index2 < size; ++index2)
			{
				if (arr[index2] == arr[index])
				{
					count++;
				}
			}
			cout << "The number " << arr[index] << " appears " << count << " times" << endl;
		}
	}
}

void FindRecurringNumbersEfficient(int arr[], int size)
{
	std::vector<Number> usedNumbers;

	for (int index = 0; index < size; ++index)
	{
		if (ContainsInList(usedNumbers, arr[index]))
		{
			int pos = GetElementByValue(usedNumbers, arr[index]);
			usedNumbers[pos].count++;
		}
		else
		{
			Number add;
			add.number = arr[index];
			usedNumbers.push_back(add);
		}
	}

	for (auto element : usedNumbers)
	{
		cout << "The number " << element.number << " appears " << element.count << " times" << endl;
	}
}


int main()
{
	int test[10] = { 1, 5, 3, 1, 4, 5, 7, 8, 9, 3 };

	FindRecurringNumbersEfficient(test, 10);


	if (false)
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

			linkList.~DoubleLinkedList();
		}
	}


	system("pause");
	return 0;
}