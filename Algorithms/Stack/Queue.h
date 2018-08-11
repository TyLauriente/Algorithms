#pragma once

#include<exception>
#include<iostream>
#include"LinkedList.h"
#include"Node.h"



struct QueueEmptyException : public std::exception
{
	const char * what() const throw ()
	{
		return "Queueis Empty";
	}
};


template <typename T>
class Queue
{
public:

	Queue() {}

	~Queue() { m_list.~LinkedList(); count = 0; }

	//Copy Constructor
	Queue(const Queue<T>& other) { m_list = other.m_list; count = other.count; }

	//Copy assignment
	Queue& operator = (const Queue<T>& other) 
	{
		if (this != &other)
		{
			this->~Queue();
			m_list = other.m_list;
			count = other.count;
		}
		return *this;
	}

	//Move Constructor
	Queue(Queue<T>&& other)
		: m_list{ LinkedList<T>() }
		, count{ 0 }
	{
		m_list = other.m_list;
		count = other.count;
		other.m_list.~LinkedList();
		other.count = 0;
	}

	//Move Assignment operator
	Queue& operator = (Queue<T>&& other)
	{
		if (this != &other)
		{
			m_list = other.m_list;
			count = other.count;
			other.m_list.~LinkedList();
			other.count = 0;
		}
		return *this;
	}

	void Push(T value)
	{
		m_list.AddLast(value);
		count++;
	}

	T Peak()
	{
		CheckNull();
		return m_list.Get(0);
	}

	T Pop()
	{
		CheckNull();
		T data = m_list.Get(0);
		m_list.RemoveFirst();
		count--;
		return data;
	}

	int count = 0;
protected:
	LinkedList<T> m_list;

	void CheckNull()
	{
		if (count <= 0)
		{
			throw StackEmptyException();
		}
	}
};