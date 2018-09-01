#pragma once

#include<iostream>

template<typename T>
class HashItem
{
public:
	HashItem()
	{

	}

	~HashItem()
	{

	}


	int GetKey()
	{
		return m_key;
	}

	void SetKey(int key)
	{
		m_key = key;
	}

	void SetObject(T object)
	{
		m_object = object;
	}

	T GetObject() { return m_object; }

	bool operator==(const HashItem<T>& other)
	{
		return (m_object == other.m_object) && (m_key == other.m_key);
	}

	void operator=(const HashItem<T>& other)
	{
		m_object = other.m_object;
		m_key = other.m_key;
	}

private:
	T m_object;
	int m_key = 0;
};