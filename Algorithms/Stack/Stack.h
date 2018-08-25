#pragma once

#include<exception>
#include<iostream>
#include"LinkedList.h"
#include"Node.h"



//struct StackEmptyException: public std::exception
//{
//	const char * what() const throw ()
//	{
//		return "Stack is Empty";
//	}
//};


template <typename T>
class Stack
{
public:

	Stack() {}


	~Stack() { m_list.~LinkedList(); count = 0; }

	//Copy Constructor
	Stack(const Stack<T>& other) { m_list = other.m_list; count = other.count; }

	//Copy assignment
	Stack& operator = (const Stack<T>& other)
	{
		if (this != &other)
		{
			this->~Stack();
			m_list = other.m_list;
			count = other.count;
		}
		return *this;
	}

	//Move Constructor
	Stack(Stack<T>&& other)
		: m_list{ LinkedList<T>() }
		, count{ 0 }
	{
		m_list = other.m_list;
		count = other.count;
		other.m_list.~LinkedList();
		other.count = 0;
	}

	//Move Assignment operator
	Stack& operator = (Stack<T>&& other)
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
		m_list.AddFirst(value);
		count++;
	}

	T Peak()
	{
		if (CheckNull())
		{
			throw;
		}
		return m_list.Get(0);
	}
	
	T Pop()
	{
		if (CheckNull())
		{
			throw;
		}
		T data = m_list.Get(0);
		m_list.RemoveFirst();
		count--;
		return data;
	}

	bool CheckNull()
	{
		if (count <= 0)
		{
			return true;
		}
		return false;
	}

	int count = 0;
protected:
	LinkedList<T> m_list;

};