#pragma once

#include"Node.h"
#include"..\Stack\StackArray.h"


template<typename T>
class LinkedList
{
public:

	LinkedList() {}
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

	//Copy Constructor
	LinkedList(const LinkedList<T>& other)
	{
		if (other.head)
		{
			head = new Node<T>;
			head->data = other.head->data;
			Node<T>* otherCurrent = other.head;
			Node<T>* thisCurrent = head;
			while (otherCurrent->next)
			{
				thisCurrent->next = new Node<T>;
				thisCurrent->next->data = otherCurrent->next->data;
				thisCurrent = thisCurrent->next;
				otherCurrent = otherCurrent->next;
			}
			tail = thisCurrent;
		}
	}

	//Copy assignment
	LinkedList& operator = (const LinkedList<T>& other)
	{
		if (this != &other)
		{
			if (other.head)
			{
				this->~LinkedList();
				head= new Node<T>;
				head->data = other.head->data;
				Node<T>* otherCurrent = other.head;
				Node<T>* thisCurrent = head;
				while (otherCurrent->next)
				{
					thisCurrent->next = new Node<T>;
					thisCurrent->next->data = otherCurrent->next->data;
					thisCurrent = thisCurrent->next;
					otherCurrent = otherCurrent->next;
				}
				tail = thisCurrent;
			}
		}
		return *this;
	}

	//Move Construcotr
	LinkedList(LinkedList<T>& other)
		: head{ nullptr }
		, tail{ nullptr }
	{
		head = other.head;
		tail = other.tail;
		other.head = nullptr;
		other.tail = nullptr;
	}

	//Move Assignment operator
	LinkedList& operator = (LinkedList<T>& other)
	{
		if (this != &other)
		{
			this->~LinkedList();
			head = other.head;
			tail = other.tail;
			other.head = nullptr;
			other.tail = nullptr;
		}
		return *this;
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
		if (head)
		{
			if (head == tail)
			{
				delete head;
				head = nullptr;
				tail = nullptr;
			}
			else
			{
				Node<T>* next = head->next;
				delete head;
				head = next;
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

	void Clear()
	{
		Node<T>* node = head;
		while (head->next)
		{
			Node<T>* temp = node;
			node = node->next;
			delete temp;
			temp = nullptr;
		}
		delete node;
		node = nullptr;
	}

	void Reverse()
	{
		StackArray<T> stack;
		Node<T>* node = head;
		stack.Push(node->data);
		while (node->next)
		{
			node = node->next;
			stack.Push(node->data);
			RemoveFirst();
		}
		RemoveFirst();
		while (stack.Size() > 0)
		{
			AddLast(stack.Pop());
		}
	}

protected:
	Node<T> *head = nullptr;
	Node<T> *tail = nullptr;
};