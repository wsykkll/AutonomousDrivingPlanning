#pragma once
#include <iostream>
using namespace std;

template<class T>
struct DoubleLinkedNode
{
	T value;
	DoubleLinkedNode* pPrevious;
	DoubleLinkedNode* pNext;
	DoubleLinkedNode()
	{

	}
	DoubleLinkedNode(T t, DoubleLinkedNode* prev, DoubleLinkedNode* next)
	{
		this->value = t;
		this->pPrevious = prev;
		this->pNext = next;
	}
};

template<class T>
class CDoubleLinkedList
{
public:
	CDoubleLinkedList();
	~CDoubleLinkedList();

	int size();
	bool empty();
	T get(int index);
	T get_front();
	T get_back();

	void insert(int index, T t);
	void insert_front(T t);
	void apend_back(T t);
	
	void delete_node(int index);
	void delete_front();
	void delete_back();
private:
	int count;
	DoubleLinkedNode<T>* pHead;
	DoubleLinkedNode<T>* get_node(int index);
};

