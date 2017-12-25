#include "DoubleLinkedList.h"

template<class T>
CDoubleLinkedList<T>::CDoubleLinkedList():
count(0)
{
	pHead = new DoubleLinkedNode<T>();
	pHead->pNext = pHead->pPrevious = pHead;
}

template<class T>
CDoubleLinkedList<T>::~CDoubleLinkedList()
{
	//Delete all the Node
	DoubleLinkedNode<T>* ptmp;
	DoubleLinkedNode<T>* pNode = pHead->pNext;
	while (pNode != pHead)
	{
		ptmp = pNode;
		pNode = pNode->pNext;
		delete ptmp;
	}
	delete pHead;
	pHead = NULL;
}

template<class T>
int CDoubleLinkedList<T>::size()
{
	return count;
}

template<class T>
bool CDoubleLinkedList<T>::empty()
{
	return(count == 0);
}

//search the index Node
template<class T>
DoubleLinkedNode<T>* CDoubleLinkedList<T>::get_node(int index)
{
	if (index < 0 || index > count)
	{
		return NULL;
	}
	//forward search
	if (index <= count/2)
	{
		int i = 0;
		DoubleLinkedNode<T>* pIndexNode = pHead->pNext;
		while (i++ < index)
		{
			pIndexNode = pIndexNode->pNext;
		}
		return pIndexNode;
	}
	//backward search
	int j = 0;
	int ReIndex = count - index - 1;
	DoubleLinkedNode<T>* pReIndexNode = pHead->pPrevious;
	while (j++ < ReIndex)
	{
		pReIndexNode = pReIndexNode->pPrevious;
	}
	return pReIndexNode;
}

//get the index node value;
template<class T>
T CDoubleLinkedList<T>::get(int index)
{
	return get_node(index)->value;
}

template<class T>
T CDoubleLinkedList<T>::get_front()
{
	return get_node(0)->value;
}

template<class T>
T CDoubleLinkedList<T>::get_back()
{
	return get_node(count - 1)->value;
}

template<class T>
void CDoubleLinkedList<T>::insert_front(T t)
{
	DoubleLinkedNode<T>* pNode = new DoubleLinkedNode<T>(t, pHead, pHead->pNext);
	pHead->pNext->pPrevious = pNode;
	pHead->pNext = pNode;
	return;
}

template<class T>
void CDoubleLinkedList<T>::apend_back(T t)
{
	DoubleLinkedNode<T>* pNode = new DoubleLinkedNode<T>(t, pHead->pPrevious, pHead);
	pHead->pPrevious->pNext = pNode;
	pHead->pPrevious = pNode;
	return;
}

//insert node to the place before index
template<class T>
void CDoubleLinkedList<T>::insert(int index, T t)
{
	if (index == 0)
	{
		return insert_front(t);
	}
	DoubleLinkedNode<T>* pIndex = get_node(index);
	DoubleLinkedNode<T>* pInsertNode = new DoubleLinkedNode<T>(t, pIndex->pPrevious, pIndex);
	pIndex->pPrevious->pNext = pInsertNode;
	pIndex->pPrevious = pInsertNode;
	return;
}

//delete the node in index place
template<class T>
void CDoubleLinkedList<T>::delete_node(int index)
{
	DoubleLinkedNode<T>* pIndex = get_node(index);
	pIndex->pNext->pPrevious = pIndex->pPrevious;
	pIndex->pPrevious->pNext = pIndex->pNext;
	delete pIndex;
	count--;
	return;
}

template<class T>
void CDoubleLinkedList<T>::delete_front()
{
	return delete_node(0);
}

template<class T>
void CDoubleLinkedList<T>::delete_back()
{
	return delete_node(count - 1);
}
