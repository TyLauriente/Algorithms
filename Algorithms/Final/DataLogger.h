#pragma once

#include<iostream>
#include<functional>
#include<vector>
#include<thread>
#include<mutex>

static const int BASE_ARRAY_SIZE = 10000;
static const int WRITE_TO_DISK_SIZE = BASE_ARRAY_SIZE * 0.25;


template<typename T>
class DataLogger
{
public:
	DataLogger(std::function<void(T)> writeFunction)
		: m_writeDataFunc{ writeFunction }
		, m_baseArraySize{ 0 }
	{

	}

	~DataLogger()
	{

	}

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
};