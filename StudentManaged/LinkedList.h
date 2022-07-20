#pragma once
template <typename T>
class Node
{
public:
	T _data;
	Node* _pNext;
	Node* _pPrev;

public:
	Node();
	Node(T data);
	~Node();
};

template <typename T>
class Iterator
{
public:
	Node<T>* _pNode;

public:
	Iterator();
	Iterator(Node<T>* pNode = nullptr);
	~Iterator();

public:
	Iterator& operator++();
	Iterator& operator--();
	const Iterator operator++(int);
	const Iterator operator--(int);
	bool operator==(const Iterator& rhs) const;
	bool operator!=(const Iterator& rhs) const;
	T operator*() const;
	const T* operator->() const;
};


template <typename T>
class LinkedList
{
public:
	Node<T>* _pHead;
	Node<T>* _pTail;

	int _size;

public:
	LinkedList();
	~LinkedList();
	LinkedList(const LinkedList& rhs) = delete;
	LinkedList& operator=(const LinkedList& rhs) = delete;

public:
	void push_front(T data);
	void push_back(T data);

public:
	void insert(Iterator<T> iter, T data);
	Iterator<T> erase(Iterator<T> iter);
	Iterator<T> begin();
	Iterator<T> end();
	Iterator<T> find(T data);

public:
	int size();
	bool empty();
	void clear();
};

#include "LinkedList.hpp"