
#include<iostream>
#include<functional>
#include<string>
#include<fstream>
#include<ctime>
#include"DataLogger.h"

static void WriteData(int data)
{
	static int count = 1;
	std::ofstream file("Log.txt", std::ios::app);
	std::string dataToWrite;
	dataToWrite = "=-=-=-=-=-=-= Entry #" + std::to_string(count) + " -=-=-=-=-=-=-=-=-\n" + std::to_string(data);
	file << dataToWrite << std::endl << std::endl;
	count++;	
}


int main()
{
	DataLogger<int> log(WriteData);

	std::cout << "start" << std::endl;
	for (int index = 0; index < 10000; ++index)
	{
		log.AddDataToWrite(index);
	}
	std::cout << "end" << std::endl;

	log.WriteRemaining();

	std::cin.get();

	system("pause");
	return 0;
}