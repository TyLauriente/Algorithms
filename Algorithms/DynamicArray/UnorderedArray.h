#ifndef UNORDERRED_ARRAY_INCLUDED_H
#define UNORDERRED_ARRAY_INCLUDED_H

#include<iostream>

template<typename T>

class UnorderredArray
{
public:

	UnorderredArray(int size, int growthFactor = 2)
		: GROWTH_FACTOR{ growthFactor }
		, m_size{ size }
		, m_nextToAdd{ size }
		, m_endOfArray{ size - 1 }
		, m_array{ new T[size] }
	{
	}

	~UnorderredArray()
	{
		delete[] m_array;
		m_array = nullptr;
	}

	T& operator[](int index) { return Get(index); }

	T& Get(int index)
	{
		if (index >= 0 && index < m_size)
		{
			return m_array[index];
		}
		else
		{
			throw;
		}
	}

	void Add(T data)
	{
		if (m_nextToAdd > m_endOfArray)
		{
			Expand();
		}
		m_array[m_nextToAdd] = data;
		m_nextToAdd++;
		m_size++;
	}

	void RemoveByIndex(int index)
	{
		for (; index < m_endOfArray; ++index)
		{
			m_array[index] = m_array[index + 1];
		}
		m_size--;
	}

	void RemoveByValue(T value)
	{
		bool found = false;
		for (int index = 0; index < m_size; ++index)
		{
			if (m_array[index] == value)
			{
				found = true;
			}
			if (found)
			{
				m_array[index] = m_array[index + 1];
			}
		}
		m_size--;
	}

	void PrintAll()
	{
		for (int index = 0; index < m_size; ++index)
		{
			std::cout << index << ": " << m_array[index] << std::endl;
		}
	}

	void Clear()
	{
		for (int index = 0; index < m_size; ++index)
		{
			m_array[index] = T();
		}
	}

	bool Contains(T value)
	{
		for (int index = 0; index < m_size; ++index)
		{
			if (m_array[index] == value)
			{
				return true;
			}
		}
		return false;
	}

	int BinarySearch(T value)
	{
		Sort();
		int startIndex = 0;
		int endIndex = m_size - 1;

		while (endIndex != startIndex)
		{
			int index = static_cast<int>((startIndex + endIndex) * 0.5);
			if (m_array[index] > value)
			{
				endIndex = index;
			}
			else if (m_array[index] < value)
			{
				startIndex = index;
			}
			else
			{
				return index;
			}
		}

		return -1;
	}

	template<typename Type>
	void Swap(Type& var1, Type& var2)
	{
		Type temp = var1;
		var1 = var2;
		var2 = temp;
	}

	void Sort()
	{
		for (int index1 = 0; index1 < m_size; ++index1)
		{
			for (int index2 = 0; index2 < m_size - index1 - 1; ++index2)
			{
				if (m_array[index2] > m_array[index2 + 1])
				{
					Swap(m_array[index2], m_array[index2 + 1]);
				}
			}
		}

	}
	
	int Size() { return m_size; }
	
private:
	const int GROWTH_FACTOR = 2;
	int m_size = 0;
	int m_nextToAdd;
	int m_endOfArray;
	T* m_array;

	void Expand()
	{
		int newSize = m_size * GROWTH_FACTOR;
		T* newArray = new T[newSize];
		m_endOfArray = newSize - 1;
		for (int index = 0; index < m_size; ++index)
		{
			newArray[index] = m_array[index];
		}
		delete[] m_array;
		m_array = newArray;
	}
};

#endif