#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::string;


//Functions used in multiple questions

template<typename T>
void PrintArray(T arr, int size)
{
	for (int index = 0; index < size; ++index)
	{
		cout << arr[index] << ", ";
	}
}

template<typename T>
void Swap(T& var1, T& var2)
{
	T temp = var1;
	var1 = var2;
	var2 = temp;
}


//Question 1

string ReverseString(string str)// O(N) = (N / 2)
{
	int endIndex = str.size() - 1;
	for (int index = 0; index < str.size() / 2; ++index)
	{
		Swap(str[index], str[endIndex]);
		--endIndex;
	}
	return str;
}


//Question 2

struct Pair
{
	int item1 = 0;
	int item2 = 0;
};

Pair GetPairToSumFromArray(int arr[], int size, int sum)// O(N) = N^2
{
	Pair pair;
	while ((arr[pair.item1] + arr[pair.item2]) != sum && pair.item1 < size)
	{
		if (pair.item2 < size)
		{
			pair.item2++;
		}
		else
		{
			pair.item2 = 0;
			pair.item1++;
		}
	}

	if ((arr[pair.item1] + arr[pair.item2]) != sum)
	{
		pair = { -1, -1 };
	}

	return pair;
}


//Question 3

Pair FindFirstAndLast(int arr[], int size, int find)// O(N) = N
{
	Pair pair;
	pair.item1 = -1;
	pair.item2 = -1;

	for (int index = 0; index < size; ++index)
	{
		if (arr[index] == find)
		{
			if (pair.item1 == -1)
			{
				pair.item1 = index;
			}
			else
			{
				pair.item2 = index;
			}
		}
	}
	if (pair.item2 == -1)
	{
		pair.item2 = pair.item1;
	}

	return pair;
}

//Question 4

string SortString(string str)// O(N) = N^2
{
	for (int index1 = 0; index1 < str.size() - 1; index1++)
		for (int index2 = 0; index2 < str.size() - index1 - 1; index2++)
			if (str[index2] > str[index2 + 1])
				Swap(str[index2], str[index2 + 1]);
	return str;
}

int main()
{
	int ans;

	cout << "Enter question number: ";
	cin >> ans;

	while (ans < 1 || ans > 4)
	{
		system("cls");
		cout << "1 - 4" << endl;
		cout << "Enter question number: ";
		cin >> ans;
	}

	system("cls");

	if (ans == 1)
	{
		std::string str;
		cout << "Enter a string to reverse: ";
		cin >> str;
		cout << "The reversed string is " << ReverseString(str) << endl;
	}
	else if (ans == 2)
	{
		const int arraySize = 10;
		int arr[arraySize];
		int sum;
		for (int index = 0; index < arraySize; ++index)
		{
			system("cls");
			cout << "Enter a number for array[" << index << "]: ";
			cin >> arr[index];
		}
		system("cls");
		cout << "Enter a number to sum to: ";
		cin >> sum;

		system("cls");
		Pair pair = GetPairToSumFromArray(arr, arraySize, sum);
		PrintArray(arr, arraySize);
		cout << endl;
		if (pair.item1 == -1 && pair.item2 == -1)
		{
			cout << "There is not a pair in the array that adds to " << sum << endl;
		}
		else
		{
			cout << "The two numbers that add to " << sum << 
				" are " << pair.item1 << ", " << pair.item2 << endl;
		}

	}
	else if (ans == 3)
	{
		const int arraySize = 10;
		int arr[arraySize];
		int find;
		for (int index = 0; index < arraySize; ++index)
		{
			system("cls");
			cout << "Enter a number for array[" << index << "]: ";
			cin >> arr[index];
		}
		system("cls");
		cout << "Enter a number to find: ";
		cin >> find;
		Pair pair = FindFirstAndLast(arr, arraySize, find);

		system("cls");
		PrintArray(arr, arraySize);
		cout << endl;
		if (pair.item1 == -1 || pair.item2 == -1)
		{
			cout << "The number " << find << " is not in the array" << endl;
		}
		else
		{
			cout << "The first occurence of " << find << " is found at array pos " << pair.item1 << endl;
			cout << "The second occurence is found at array pos " << pair.item2 << endl;
		}
	}
	else
	{
		string str;
		cout << "Enter an array of characters: " << endl;
		cin >> str;

		str = SortString(str);

		cout << "The sorted array of characters is ";
		PrintArray(str, str.size());
		cout << endl;
	}
	system("pause");
	return 0;
}