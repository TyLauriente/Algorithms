#pragma once

#include"DoubleNode.h"

template<typename T>
class DoubleLinkedList
{
public:
	~DoubleLinkedList()
	{
		if (head)
		{
			while (head->next)
			{
				DoubleNode<T>* temp = head->next;
				delete head;
				head = temp;
			}
			delete head;
		}
		head = nullptr;
		tail = nullptr;
	}

	T& Get(int pos)
	{
		DoubleNode<T>* node = head;
		int index = 0;
		while (node->next && index != pos)
		{
			node = node->next;
			index++;
		}
		return node->data;
	}

	DoubleNode<T>* GetNode(int pos)
	{
		DoubleNode<T>* node = head;
		int index = 0;
		while (node->next && index != pos)
		{
			node = node->next;
			index++;
		}
		return node;
	}

	void AddFirst(T value)
	{
		DoubleNode<T>* add = new DoubleNode<T>();
		add->data = value;

		if (head)
		{
			add->next = head;
			head->previous = add;
			head = add;
		}
		else
		{
			head = add;
			tail = add;
		}
	}

	void AddLast(T value)
	{
		DoubleNode<T>* add = new DoubleNode<T>();
		add->data = value;

		if (tail)
		{
			add->previous = tail;
			tail->next = add;
			tail = add;
		}
		else
		{
			head = add;
			tail = add;
		}
	}

	DoubleNode<T>* Find(T value)
	{
		if (!head)
		{
			throw;
		}

		DoubleNode<T>* node = head;
		while (node->next && node->data != value)
		{
			node = node->next;
		}
		return node;
	}

	DoubleNode<T>* FindPrevious(DoubleNode<T>* node)
	{
		return node->previous;
	}

	void Remove(DoubleNode<T>* node)
	{
		if (node == head)
		{
			RemoveFirst();
		}
		else if (node == tail)
		{
			RemoveLast();
		}
		else
		{
			node->previous->next = node->next;
			node->next->previous = node->previous;
			delete node;
			node = nullptr;
		}
	}

	void RemoveFirst()
	{
		if (head && head != tail)
		{
			auto newHead = head->next;
			delete head;
			head = newHead;
		}
		else
		{
			if (head)
			{
				delete head;
				head = nullptr;
			}
			if (tail)
			{
				delete tail;
				tail = nullptr;
			}
		}
	}

	void RemoveLast()
	{
		if (tail && tail != head)
		{
			auto newTail = FindPrevious(tail);
			delete tail;
			tail = newTail;
			tail->next = nullptr;
		}
		else
		{
			if (head)
			{
				delete head;
				head = nullptr;
			}
			if (tail)
			{
				delete tail;
				tail = nullptr;
			}
		}
	}

	int GetSize()
	{
		if (!head)
		{
			return 0;
		}

		int size = 1;
		while (head->next)
		{
			size++;
			head = head->next;
		}
		return size;
	}

private:
	DoubleNode<T> *head = nullptr;
	DoubleNode<T> *tail = nullptr;
};