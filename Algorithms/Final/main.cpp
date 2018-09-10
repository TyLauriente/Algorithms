
#include<iostream>
#include<functional>
#include<string>
#include<fstream>
#include<ctime>
#include"DataLogger.h"


std::string ConvertToTextFunc(int num)
{
	return std::to_string(num);
}

int main()
{
	using namespace std;
	DataLogger<int> log(ConvertToTextFunc, ArraySize::High);
	
	cout << "start" << endl;
	for (int index = 1; index <= 10000000; ++index)
	{
		log.LogItem(index);
	}
	cout << "end" << endl;

	log.ForceLogAll();

	system("pause");
	return 0;
}