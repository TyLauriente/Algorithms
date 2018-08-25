#pragma once

#include<iostream>
#include"Stack.h"

template<typename T>
class Queue2StacksFastDeqeue
{
public:
	Queue2StacksFastDeqeue() {}

	~Queue2StacksFastDeqeue() {}

	Queue2StacksFastDeqeue(const Queue2StacksFastDeqeue<T>& other)
	{
		this->m_stack1 = other.m_stack1;
		this->m_stack2 = other.m_stack2;
	}

	Queue2StacksFastDeqeue<T>& operator=(const Queue2StacksFastDeqeue<T>& other)
	{
		if (this != &other)
		{
			this->m_stack1 = other.m_stack1;
			this->m_stack2 = other.m_stack2;
		}
		return *this;
	}

	Queue2StacksFastDeqeue(Queue2StacksFastDeqeue&& other)
	{
		this->m_stack1 = other.m_stack1;
		this->m_stack2 = other.m_stack2;
		other.m_stack1.~Stack();
		other.m_stack2.~Stack();
	}

	Queue2StacksFastDeqeue& operator=(Queue2StacksFastDeqeue&& other)
	{
		if (this != &other)
		{
			this->m_stack1 = other.m_stack1;
			this->m_stack2 = other.m_stack2;
			other.m_stack1.~Stack();
			other.m_stack2.~Stack();
		}
		return *this;
	}

	void Enqueue(T data)
	{
		while (!m_stack1.CheckNull())
		{
			m_stack2.Push(m_stack1.Pop());
		}
		m_stack1.Push(data);
		while (!m_stack2.CheckNull())
		{
			m_stack1.Push(m_stack2.Pop());
		}
	}

	T Dequeue()
	{
		return m_stack1.Pop();
	}

	T Peek()
	{
		return m_stack1.Peak();
	}

	void Clear()
	{
		m_stack1.clear();
	}


private:
	Stack<T> m_stack1;
	Stack<T> m_stack2;
};


template<typename T>
class Queue2StacksFastEnqeue
{
public:

	void Enqueue(T data)
	{
		m_stack1.Push(data);
	}

	T Dequeue()
	{
		while (!m_stack1.CheckNull())
		{
			m_stack2.Push(m_stack1.Pop());
		}
		T data = m_stack2.Pop();
		while (!m_stack2.CheckNull())
		{
			T temp = m_stack2.Pop();
			m_stack1.Push(temp);
		}
		return data;
	}

	T Peek()
	{
		while (!m_stack1.CheckNull())
		{
			m_stack2.Push(m_stack1.Pop());
		}
		T data = m_stack2.Peak();
		while (!m_stack2.CheckNull())
		{
			m_stack1.Push(m_stack1.Pop());
		}
		return data;
	}

private:
	Stack<T> m_stack1;
	Stack<T> m_stack2;
};