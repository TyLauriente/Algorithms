#pragma once

#include<iostream>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include<functional>
#include<vector>
#include<thread>
#include<mutex>
#include<string>
#include<fstream>

enum class ArraySize
{
	Low = 10000,
	MediumLow = 100000,
	MediumHigh = 1000000,
	High = 10000000
};


template<typename T>
class DataLogger
{
public:
	DataLogger(const std::function<std::string(T)> writeFunction, ArraySize size = ArraySize::MediumLow);

	~DataLogger();

	void LogItem(T item);

	void ForceLogAll();


private:
	//consts and helper functions

	void StartLogThread(int pos);
	void TransferToBaseQueue(std::vector<T> baseArrayCopy);
	void TransferToSubQueues();
	void Reset();

	const int BASE_ARRAY_SIZE;
	const int SUB_QUEUE_DIVIDE_RATE;
	const float TRANSFER_RATE;// if( m_baseArray.size() >= (BASE_ARRAY_SIZE * TRANSFER_RATE) ) Transfer to queue
	const std::function <std::string(T)> ConvertToText;
	
	//Data Structures and mutexes
	std::vector<T> m_baseArray;

	std::vector<T> m_baseQueue;
	std::mutex m_baseQueueLock;

	std::vector<std::vector<T>> m_subQueues;
	std::vector<std::mutex*> m_subQueueLocks;
	
	int m_logCount;
	int m_loggedItems;
	std::mutex m_logCountLock;

};

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=IMPLEMENTATION-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
*/

template<typename T>
DataLogger<T>::DataLogger(std::function<std::string(T)> writeFunction, ArraySize size = ArraySize::MediumLow)
	: BASE_ARRAY_SIZE{ static_cast<int>(size) }
	, SUB_QUEUE_DIVIDE_RATE{ 10000 }
	, TRANSFER_RATE{ 0.25f }
	, ConvertToText{ writeFunction }
	, m_logCount{ 0 }
	, m_loggedItems{ 0 }
{
	mkdir("Logs");

	std::vector<T> tempSubQueue;
	for (int subQueue = 0; subQueue < BASE_ARRAY_SIZE / SUB_QUEUE_DIVIDE_RATE; ++subQueue)
	{
		m_subQueues.push_back(tempSubQueue);
		m_subQueueLocks.push_back(new std::mutex());
	}
}



template<typename T>
DataLogger<T>::~DataLogger()
{
	ForceLogAll();
}



template<typename T>
void DataLogger<T>::LogItem(T item)
{
	m_baseArray.push_back(item);
	m_loggedItems++;

	if (m_baseArray.size() >= BASE_ARRAY_SIZE / (BASE_ARRAY_SIZE / SUB_QUEUE_DIVIDE_RATE))
	{
		std::thread transfer(&DataLogger::TransferToBaseQueue, this, m_baseArray);
		transfer.detach();
		m_baseArray.clear();
	}
	if (m_loggedItems == BASE_ARRAY_SIZE)
	{
		Reset();
	}
}


template<typename T>
void DataLogger<T>::ForceLogAll()
{
	if (m_baseArray.size() != 0)
	{
		TransferToBaseQueue(m_baseArray);
		m_baseArray.clear();
	}
	while (m_baseQueue.size() != 0)
	{
		TransferToSubQueues();
	}

	int subQueuePos = 0;
	for (; subQueuePos < m_subQueues.size(); ++subQueuePos)
	{
		m_subQueueLocks[subQueuePos]->lock();
		if (!m_subQueues[subQueuePos].size() == 0)
		{
			m_subQueueLocks[subQueuePos]->unlock();
			std::thread log(&DataLogger::StartLogThread, this, subQueuePos);
			log.detach();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		else
		{
			m_subQueueLocks[subQueuePos]->unlock();
		}
	}
}



template<typename T>
void DataLogger<T>::StartLogThread(int pos)
{
	m_subQueueLocks[pos]->lock();

	if (m_subQueues[pos].size() != 0)
	{
		m_logCountLock.lock();
		int count = m_logCount;
		m_logCount++;
		m_logCountLock.unlock();

		std::string fileSource = "Logs\\Log #" + std::to_string(count) + ".txt";

		std::ofstream file(fileSource.c_str(), std::ios::out);


		for (const auto& item : m_subQueues[pos])
		{
			file << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" + ConvertToText(item) << std::endl;
		}
		m_subQueues[pos].clear();
	}
	m_subQueueLocks[pos]->unlock();
}

template<typename T>
void DataLogger<T>::TransferToBaseQueue(std::vector<T> baseArrayCopy)
{
	m_baseQueueLock.lock();
	for (const auto& item : baseArrayCopy)
	{
		m_baseQueue.push_back(item);
	}
	if (m_baseQueue.size() == BASE_ARRAY_SIZE)
	{
		m_baseQueueLock.unlock();
		std::thread transfer(&DataLogger::TransferToSubQueues, this);
		transfer.detach();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	else
	{
		m_baseQueueLock.unlock();
	}
}


template<typename T>
void DataLogger<T>::TransferToSubQueues()
{
	m_baseQueueLock.lock();
	int maxSubQueueSize = BASE_ARRAY_SIZE / (BASE_ARRAY_SIZE / SUB_QUEUE_DIVIDE_RATE);
	int subQueuePos = 0;


	for (; subQueuePos < m_subQueues.size(); ++subQueuePos)
	{
		m_subQueueLocks[subQueuePos]->lock();
		if (m_subQueues[subQueuePos].size() < maxSubQueueSize || subQueuePos == m_subQueues.size() -1)
		{
			break;
		}
		m_subQueueLocks[subQueuePos]->unlock();
	}


	for (auto& item : m_baseQueue)
	{
		m_subQueues[subQueuePos].push_back(item);
		if (m_subQueues[subQueuePos].size() == maxSubQueueSize && subQueuePos < m_subQueues.size() - 1)
		{
			m_subQueueLocks[subQueuePos]->unlock();
			do
			{
				subQueuePos++;
			} while (m_subQueues[subQueuePos].size() == maxSubQueueSize && subQueuePos != m_subQueues.size() - 1);
			m_subQueueLocks[subQueuePos]->lock();
		}
	}
	m_subQueueLocks[subQueuePos]->unlock();
	m_baseQueue.clear();
	m_baseQueueLock.unlock();

	subQueuePos = 0;
	for (; subQueuePos < m_subQueues.size(); ++subQueuePos)
	{
		m_subQueueLocks[subQueuePos]->lock();
		if (m_subQueues[subQueuePos].size() == maxSubQueueSize)
		{
			m_subQueueLocks[subQueuePos]->unlock();
			std::thread log(&DataLogger::StartLogThread, this, subQueuePos);
			log.detach();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		else
		{
			m_subQueueLocks[subQueuePos]->unlock();
		}
	}
}


template<typename T>
void DataLogger<T>::Reset()
{
	ForceLogAll();

	m_baseArray.clear();
	m_baseQueueLock.lock();
	m_baseQueue.clear();
	m_baseQueueLock.unlock();

	for (int subQueuePos = 0; subQueuePos < m_subQueues.size(); ++subQueuePos)
	{
		m_subQueueLocks[subQueuePos]->lock();
		m_subQueues[subQueuePos].clear();
		m_subQueueLocks[subQueuePos]->unlock();
	}
}



/*

void AddDataToWrite(T data)
{
m_array.push_back(data);

if (m_array.size() >= BASE_ARRAY_SIZE * 0.25 && m_queueLock.try_lock())
{
TransferToQueue();
m_queueLock.unlock();
}
}

void WriteRemaining()
{
m_queueLock.lock();
TransferToQueue();
if (m_queue.size() != 0)
{
std::thread writeData(&DataLogger::WriteQueueData, this);
writeData.detach();
}
m_queueLock.unlock();
}


private:


void WriteQueueData()
{
m_queueLock.lock();
for (const auto& item : m_queue)
{
m_writeDataFunc(item);
}
m_queue.clear();
m_queueLock.unlock();
}

void TransferToQueue()
{
for (int index = 0; index < m_array.size(); ++index)
{
m_queue.push_back(m_array[index]);
}
m_array.clear();
if (m_queue.size() >= WRITE_TO_DISK_SIZE)
{
std::thread writeData (&DataLogger::WriteQueueData, this);
writeData.detach();
}
}

private:
std::vector<T> m_array;
int m_baseArraySize;
std::vector<T> m_queue;
std::mutex m_queueLock;

std::function<void(T)> m_writeDataFunc;

*/