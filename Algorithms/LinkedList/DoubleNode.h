#pragma once

template<typename T>
class DoubleNode
{
public:
	T data;
	DoubleNode* previous = nullptr;
	DoubleNode* next = nullptr;
};