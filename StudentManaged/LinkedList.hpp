#include "LinkedList.h"

#pragma warning(disable:26495)
template <typename T>
Node<T>::Node() :_pNext(nullptr), _pPrev(nullptr)
{
}
#pragma warning(default:26495)

template <typename T>
Node<T>::Node(T data) :_data(data), _pNext(nullptr), _pPrev(nullptr)
{
}

template <typename T>
Node<T>::~Node()
{
	_pNext = nullptr;
	_pPrev = nullptr;
}


template <typename T>
Iterator<T>::Iterator() :_pNode(nullptr)
{
}

template <typename T>
Iterator<T>::Iterator(Node<T>* pNode) : _pNode(pNode)
{
}

template <typename T>
Iterator<T>::~Iterator()
{
}

template <typename T>
Iterator<T>& Iterator<T>::operator++()
{
	_pNode = _pNode->_pNext;
	return *this;
}

template <typename T>
Iterator<T>& Iterator<T>::operator--()
{
	_pNode = _pNode->_pPrev;
	return *this;
}

template <typename T>
const Iterator<T> Iterator<T>::operator++(int)
{
	Iterator<T> _temp = *this;
	_pNode = _pNode->_pNext;
	return _temp;
}

template <typename T>
const Iterator<T> Iterator<T>::operator--(int)
{
	Iterator<T> _temp = *this;
	_pNode = _pNode->_pPrev;
	return _temp;
}

template <typename T>
bool Iterator<T>::operator==(const Iterator& it) const
{
	return _pNode == it._pNode;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator& it) const
{
	return !(*this == it);
}

template <typename T>
T Iterator<T>::operator*() const
{
	return _pNode->_data;
}

template <typename T>
T* Iterator<T>::operator->() const
{
	return &(_pNode->_data);
}


template <typename T>
LinkedList<T>::LinkedList():_pHead(new Node<T>()), _pTail(new Node<T>()), _size(0)
{
	_pHead->_pNext = _pTail;
	_pHead->_pPrev = _pTail;
	_pTail->_pNext = _pHead;
	_pTail->_pPrev = _pHead;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	clear();
	delete _pHead;
	delete _pTail;
}

template <typename T>
void LinkedList<T>::push_back(T data)
{
	Node<T>* pNewNode = new Node<T>(data);
	Node<T>* pTempPrev = _pTail->_pPrev;
	_pTail->_pPrev = pNewNode;
	pTempPrev->_pNext = pNewNode;
	pNewNode->_pNext = _pTail;
	pNewNode->_pPrev = pTempPrev;
	++_size;
}

template <typename T>
void LinkedList<T>::push_front(T data)
{
	Node<T>* pNewNode = new Node<T>(data);
	Node<T>* pTempNext = _pHead->_pNext;
	_pHead->_pNext = pNewNode;
	pTempNext->_pPrev = pNewNode;
	pNewNode->_pNext = pTempNext;
	pNewNode->_pPrev = _pHead;
	++_size;
}

template <typename T>
void LinkedList<T>::insert(Iterator<T> iter, T data)
{
	Node<T>* pNewNode = new Node<T>(data);
	Node<T>* pIterNode = iter._pNode;
	Node<T>* pTempPrev = pIterNode->_pPrev;
	pIterNode->_pPrev = pNewNode;
	pTempPrev->_pNext = pNewNode;
	pNewNode->_pNext = pIterNode;
	pNewNode->_pPrev = pTempPrev;
	++_size;
}

template <typename T>
Iterator<T> LinkedList<T>::erase(Iterator<T> iter)
{
	Node<T>* eraseNode = iter._pNode;
	Node<T>* pTempNextNode = eraseNode->_pNext;
	Node<T>* pTempPrevNode = eraseNode->_pPrev;

	delete eraseNode;

	pTempPrevNode->_pNext = pTempNextNode;
	pTempNextNode->_pPrev = pTempPrevNode;

	--_size;
	return Iterator<T>(pTempNextNode);
}

template <typename T>
Iterator<T> LinkedList<T>::begin()
{
	return Iterator<T>(_pHead->_pNext);
}

template <typename T>
Iterator<T> LinkedList<T>::end()
{
	return Iterator<T>(_pTail);
}

template <typename T>
Iterator<T> LinkedList<T>::find(T data)
{
	Iterator<T> iter = begin();
	for (; iter != end(); ++iter)
	{
		if (iter._pNode->_data == data)
		{
			break;
		}
	}
	return iter;
}

template <typename T>
int LinkedList<T>::size()
{
	return _size;
}

template <typename T>
bool LinkedList<T>::empty()
{
	return (_size <= 0);
}

template <typename T>
void LinkedList<T>::clear()
{
	Node<T>* pNode = _pHead->_pNext;
	while (pNode != _pTail)
	{
		Node<T>* pNext = pNode->_pNext;
		delete pNode;
		pNode = pNext;
		--_size;
	}
	_pHead->_pNext = _pTail;
	_pHead->_pPrev = _pTail;
	_pTail->_pNext = _pHead;
	_pTail->_pPrev = _pHead;
}
