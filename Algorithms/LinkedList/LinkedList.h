#pragma once

#include"Node.h"

template<typename T>
class LinkedList
{
public:
	~LinkedList()
	{
		if (head)
		{
			while (head->next)
			{
				Node<T>* temp = head->next;
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
		Node<T>* node = head;
		int index = 0;
		while (node->next && index != pos)
		{
			node = node->next;
			index++;
		}
		return node->data;
	}

	Node<T>* GetNode(int pos)
	{
		Node<T>* node = head;
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
		Node<T>* add = new Node<T>();
		add->data = value;

		add->next = head;
		head = add;
	}

	void AddLast(T value)
	{
		Node<T>* add = new Node<T>();
		add->data = value;

		if (head)
		{
			tail->next = add;
			tail = add;
		}
		else
		{
			head = add;
			tail = add;
		}
	}

	Node<T>* Find(T value)
	{
		Node<T>* node = head;
		while (node->next && node->data != value)
		{
			node = node->next;
		}
		return node;
	}

	Node<T>* FindPrevious(Node<T>* node)
	{
		Node<T>* previous = head;
		while (previous->next != node)
		{
			previous = previous->next;
		}
		return previous;
	}

	void Remove(Node<T>* node)
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
			(FindPrevious(node))->next = node->next;
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

	void RemoveNodeWithoutHead(Node<T>* node)
	{
		if (node->next)
		{
			Node<T>* previous;
			while (node->next)
			{
				node->data = node->next->data;
				previous = node;
				node = node->next;
			}
			delete node;
			previous->next = nullptr;
		}
		else
		{
			cout << "ERROR IN LINKEDLIST: Node given is last node" << endl;
		}
	}

private:
	Node<T> *head = nullptr;
	Node<T> *tail = nullptr;
};