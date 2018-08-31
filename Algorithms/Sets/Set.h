#pragma once

#include<iostream>
#include<functional>
#include<vector>

template<typename Type>
class Set
{
public:
	Set(std::function<bool(Type)> isSetMember) : m_isSetMember{ isSetMember } {}
	
	//Copy Constructor
	Set(const Set<Type>& other) 
	{
		m_isSetMember = other.m_isSetMember;
		m_set = other.m_set;
		m_size = other.m_size;
	}

	//Copy Assignment
	Set<Type>& operator=(const Set<Type>& other)
	{
		m_isSetMember = other.m_isSetMember;
		m_set = other.m_set;
		m_size = other.m_size;
		return *this;
	}

	//Move Constructor
	Set(Set<Type>&& other)
	{
		m_isSetMember = other.m_isSetMember;
		m_set = other.m_set;
		m_size = other.m_size;
		other.Clear();
	}

	//Move Assignment
	Set<Type>& operator=(Set<Type>&& other)
	{
		if (this != &other)
		{
			m_isSetMember = other.m_isSetMember;
			m_set = other.m_set;
			m_size = other.m_size;
			other.Clear();
		}
		return *this;
	}

	//Destructor
	~Set() { Clear(); }

	//Used for iteration
	auto begin() 
	{
		m_copySet = m_set;
		return m_copySet.begin();
	}
	auto end() { return m_copySet.end(); }

	//+ operator = Union
	Set<Type> operator+(const Set<Type>& other)
	{
		return this->Union(other);
	}

	//- operator = Difference
	Set<Type> operator-(const Set<Type>& other)
	{
		return this->Difference(other);
	}


	void Clear()
	{
		m_set.clear();
		m_copySet.clear();
		m_size = 0;
	}



	bool Contains(Type value)
	{
		for (const auto& item : m_set)
		{
			if (item == value)
			{
				return true;
			}
		}
		return false;
	}

	void Add(Type value)
	{
		if (m_isSetMember(value))
		{
			m_set.push_back(value);
			m_size++;
		}
	}

	void Remove(Type value)
	{
		for (auto it = m_set.begin(); it != m_set.end(); ++it)
		{
			if (*it == value)
			{
				m_set.erase(it);
				m_size--;
				break;
			}
		}
	}

	std::vector<Type> GetSet() { return m_set; }

	void AddRange(std::vector<Type> values)
	{
		for (const auto& item : values)
		{
			if (m_isSetMember(item))
			{
				m_set.push_back(item);
				m_size++;
			}
		}
	}

	void AddSkipDuplicate(Type value)
	{
		if (m_isSetMember(value) && !Contains(value))
		{
			m_set.push_back(value);
			m_size++;
		}
	}

	void AddRangeSkipDuplicate(std::vector<Type> values)
	{
		for (const auto& item : values)
		{
			if (m_isSetMember(item) && !Contains(item))
			{
				m_set.push_back(item);
				m_size++;
			}
		}
	}

	Set<Type> Union(Set<Type> otherSet)
	{
		Set<Type> result(Set<Type>(*this));
		result.AddRangeSkipDuplicate(otherSet.GetSet());
		return result;
	}

	Set<Type> Intersection(Set<Type> otherSet)
	{
		Set<Type> result(m_isSetMember);
		for (const auto& item : m_set)
		{
			if (otherSet.Contains(item))
			{
				result.Add(item);
			}
		}
		return result;
	}

	Set<Type> Difference(Set<Type> otherSet)
	{
		Set<Type> result(*this);
		for (const auto& item : otherSet)
		{
			if (result.Contains(item))
			{
				result.Remove(item);
			}
		}
		return result;
	}

	Set<Type> SymetricDifference(Set<Type> otherSet)
	{
		Set<Type> result(this->Union(otherSet));
		for (const auto& item : otherSet)
		{
			if (this->Contains(item) && otherSet.Contains(item))
			{
				result.Remove(item);
			}
		}
		return result;
	}



protected:
	std::function<bool(Type)> m_isSetMember;
	std::vector<Type> m_set;
	std::vector<Type> m_copySet;
	int m_size = 0;
};

