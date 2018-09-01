#pragma once


#include<iostream>
#include<string>
#include<vector>
#include"HashItem.h"

using std::string;

template<typename T>
class HashTable
{
public:

	HashTable(int size)
		: m_items{ size }
		, m_size{ size }
	{

	}

	~HashTable()
	{

	}

	T GetItem(string key)
	{
		return m_items[HashFunction(key)].GetObject();
	}

	bool Insert(string key, T object)
	{
		HashItem<T> item;
		item.SetObject(object);
		item.SetKey(HashFunction(key));
		if (item.GetKey() < m_size)
		{
			m_items[item.GetKey()] = item;
			return true;
		}
		return false;
	}

	void Delete(string key)
	{
		int hashKey = HashFunction(key);
		for (auto it = m_items.begin(); it != m_items.end(); ++it)
		{
			if ((*it).GetKey() == hashKey)
			{
				m_items.erase(it);
				return;
			}
		}
	}

	bool Find(string key, T object)
	{
		int hashKey = HashFunction(key);

		if (m_items[hashKey].GetObject() == object)
		{
			return true;
		}
		return false;
	}


private:

	int HashFunction(string str)
	{
		int hash = 0;
		for (int index = 0; index < (int)str.size(); ++index)
		{
			int val = (int)str[index];
			hash = (hash * 256 + val);
		}
		return hash % m_size;
	}

	std::vector<HashItem<T>> m_items;
	int m_size;
};