#pragma once

#include<exception>
#include<iostream>
#include"..\DynamicArray\UnorderedArray.h"

struct StackEmptyException : public std::exception
{
	const char * what() const throw ()
	{
		return "Stack is Empty";
	}
};


template <typename T>
class StackArray
{
public:

	StackArray<T>() : m_array(10, 2), m_size(0) { }


	~StackArray() { }

	//Copy Constructor
	

	//Copy assignment
	
	//Move Constructor
	

	//Move Assignment operator
	

	void Push(T value)
	{
		m_array.Add(value);
		m_size++;
	}

	T Peak()
	{
		if (CheckNull())
		{
			throw StackEmptyException();
		}
		return m_array.Get(m_size - 1);
	}

	T Pop()
	{
		if (CheckNull())
		{
			throw StackEmptyException();
		}
		T data = m_array.Get(m_size - 1);
		m_array.RemoveByIndex(m_size - 1);
		m_size--;
		return data;
	}

	void Clear()
	{
		m_size = 0;
		m_array.Clear();
	}

	int Size() { return m_size; }

	bool CheckNull()
	{
		if (m_size <= 0)
		{
			return true;
		}
		return false;
	}
	
protected:
	UnorderredArray<T> m_array;
	int m_size;
};

/*

//Copy Constructor
StackArray(const Stack<T>& other) { m_list = other.m_list; count = other.count; }

//Copy assignment
StackArray& operator = (const Stack<T>& other)
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

*/