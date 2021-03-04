#pragma once
#include <iostream>

template <class T>
struct Link
{
	T value;
	Link* next;
	Link(Link* _next, T _value = 0) : value(_value), next(_next) {}
};

template <class T>
class Iterator
{
private:
	Link<T>* curr;
	Link<T>* prev;
public:
	Iterator() {};
	Iterator(Link<T>* start) { this->curr = start; prev = NULL; };
	T current()
	{
		return this->curr->value;
	}
	T next()
	{
		this->prev = this->curr;
		this->curr = this->curr->next;
		return this->prev->value;
	}
	bool hasNext()
	{
		return (this->curr != NULL);
	}
	void add(const T& value)
	{
		Link<T>* temp = new Link<T>(this->curr, value);
		if (this->prev != NULL)
			this->prev->next = temp;
		this->curr = temp;

	}
	void replace(const T& value)
	{
		this->curr->value = value;
	}
	void remove()
	{
		if (this->prev != NULL)
			this->prev->next = this->curr->next;
		delete this->curr;
		this->curr = this->prev->next;
	}
};

template <class T>
class LinkList
{
private:
	Link<T>* first;
	Link<T>* last;

public:
	LinkList() { this->first = NULL; this->last = NULL; };
	LinkList(const LinkList& list)
	{
		Link<T>* tempOld = list.first;
		this->first = NULL;
		this->last = NULL;
		if (tempOld == NULL)
			return;
		Link<T>* tempNew = new Link<T>(NULL, tempOld->value);
		this->first = tempNew;
		tempOld = tempOld->next;
		while (tempOld != NULL)
		{
			tempNew->next = new Link<T>(NULL, tempOld->value);
			tempNew = tempNew->next;
			tempOld = tempOld->next;
		}
		this->last = tempNew;
	}
	~LinkList()
	{
		Link<T>* temp;
		while (first != NULL)
		{
			temp = first->next;
			delete first;
			first = temp;
		}
	}

	LinkList<T>& operator=(const LinkList<T>& list)
	{
		Link<T>* temp;
		while (first != NULL)
		{
			temp = first->next;
			delete first;
			first = temp;
		}

		if (this != &list)
		{
			Link<T>* tempOld = list.first;
			this->first = NULL;
			this->last = NULL;
			if (tempOld == NULL)
				return;
			Link<T>* tempNew = new Link<T>(NULL, tempOld->value);
			this->first = tempNew;
			tempOld = tempOld->next;
			while (tempOld != NULL)
			{
				tempNew->next = new Link<T>(tempNew, tempOld->value);
				tempNew = tempNew->next;
				tempOld = tempOld->next;
			}
			this->last = tempNew;
			return *this;
		}
		return *this;
	}

	void addFirst(const T& _value)
	{
		this->first = new Link<T>(this->first, _value);
		if (this->last == NULL)
			this->last = this->first;
	}
	void addLast(const T& _value)
	{
		Link<T>* temp = this->last;
		this->last = new Link<T>(NULL, _value);
		if (temp != NULL)
			temp->next = this->last;
		else
			this->first = this->last;
	}

	void removeFirst()
	{
		if (this->empty())
			throw std::logic_error("Список пустой.");
		Link<T>* temp = this->first->next;
		delete this->first;
		this->first = temp;
		if (temp == NULL)
			this->last = NULL;
	}

	void replaceFirst(const T& _value)
	{
		if (this->empty())
			throw std::logic_error("Список пустой.");
		this->first->value = _value;
	}
	void replaceLast(const T& _value)
	{
		if (this->empty())
			throw std::logic_error("Список пустой.");
		this->last->value = _value;
	}

	T getFirst() const
	{
		if (this->empty())
			throw std::logic_error("Список пустой.");
		return this->first->value;
	}
	T getLast() const
	{
		if (this->empty())
			throw std::logic_error("Список пустой.");
		return this->last->value;
	}

	bool empty() const
	{
		return this->first == NULL;
	}
	Iterator<T> getIterator() const
	{
		return Iterator<T>(this->first);
	}
};

template <class T>
class OrderList : public LinkList<T>
{
private:
	Iterator<T> curr;
public:
	OrderList() : LinkList<T>()
	{
		curr = this->getIterator();
	}
	void add(const T& value)
	{
		Iterator<T> first = this->getIterator();
		if (!first.hasNext())
		{
			this->addFirst(value);
			curr = this->getIterator();
			return;
		}
		if (value >= first.next())
		{
			this->addFirst(value);
			curr = this->getIterator();
			return;
		}
		if (curr.next() < value)
			curr = this->getIterator();
		while (curr.hasNext())
		{
			if (value >= curr.current())
				break;
			curr.next();
		}
		curr.add(value);
	}
};