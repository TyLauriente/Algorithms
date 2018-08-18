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

	StackArray<T>() : m_array(10, 2), size(0) { }


	~StackArray() { }

	//Copy Constructor
	

	//Copy assignment
	
	//Move Constructor
	

	//Move Assignment operator
	

	void Push(T value)
	{
		m_array.Get(size) = value;
		size++;
	}

	T Peak()
	{
		CheckNull();
		return m_array.Get(size - 1);
	}

	T Pop()
	{
		CheckNull();
		T data = m_array.Get(size - 1);
		m_array.RemoveByIndex(size - 1);
		size--;
		return data;
	}

	
	int size;
protected:
	UnorderredArray<T> m_array;

	void CheckNull()
	{
		if (size <= 0)
		{
			throw StackEmptyException();
		}
	}
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