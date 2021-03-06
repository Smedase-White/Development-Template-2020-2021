#pragma once
#include <iostream>

template <class T>
struct Link
{
	T value;
	Link* next;
	Link(Link* _next = NULL, T _value = 0) : next(_next), value(_value) {}
};

template <class T>
class Iterator
{
private:
	Link<T>* curr;
public:
	Iterator() {};
	Iterator(Link<T>* start) { this->curr = start; };
	T current()
	{
		return this->curr->value;
	}
	T next()
	{
		Link<T>* temp = this->curr;
		this->curr = this->curr->next;
		return temp->value;
	}
	bool hasNext()
	{
		return (this->curr != NULL);
	}
};

template <class T>
class LinkList
{
private:
	Link<T>* first;
	Link<T>* last;

	template <class T>
	class ListManager;
	static ListManager<T>* listManager;
	Link<T>* newLink(Link<T>* _next = NULL, T _value = 0)
	{
		Link<T>* temp = listManager->get();
		temp->next = _next;
		temp->value = _value;
		return temp;
	}
	void deleteLink(Link<T>* element)
	{
		listManager->give(element);
	}
public:
	template <class T>
	class ListManager
	{
	private:
		Link<T>* start;
	public:
		ListManager(const int& size = 1000)
		{
			start = new Link<T>;
			Link<T>* temp = start;
			for (int i = 0; i < size; i++)
			{
				temp->next = new Link<T>;
				temp = temp->next;
			}
		}
		~ListManager()
		{
			Link<T>* temp;
			while (start != NULL)
			{
				temp = start->next;
				delete start;
				start = temp;
			}
		}
		Link<T>* get()
		{
			if (start == NULL)
			{
				start = new Link<T>;
			}
			Link<T>* temp = start;
			start = start->next;
			return temp;
		}
		void give(Link<T>* element)
		{
			element->next = start;
			start = element;
		}
	};
	LinkList() { this->first = NULL; this->last = NULL; };
	LinkList(const LinkList& list)
	{
		Link<T>* tempOld = list.first;
		this->first = NULL;
		this->last = NULL;
		this->listManager = list.listManager;
		if (tempOld == NULL)
			return;
		Link<T>* tempNew = newLink(NULL, tempOld->value);
		this->first = tempNew;
		tempOld = tempOld->next;
		while (tempOld != NULL)
		{
			tempNew->next = newLink(NULL, tempOld->value);
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
			deleteLink(first);
			first = temp;
		}
		
	}

	LinkList<T>& operator=(const LinkList<T>& list)
	{
		if (this != &list)
		{
			~LinkList();
			Link<T>* tempOld = list.first;
			this->first = NULL;
			this->last = NULL;
			if (tempOld == NULL)
				return NULL;
			Link<T>* tempNew = newLink(NULL, tempOld->value);
			this->first = tempNew;
			tempOld = tempOld->next;
			while (tempOld != NULL)
			{
				tempNew->next = newLink(tempNew, tempOld->value);
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
		this->first = newLink(this->first, _value);
		if (this->last == NULL)
			this->last = this->first;
	}
	void addLast(const T& _value)
	{
		Link<T>* temp = this->last;
		this->last = newLink(NULL, _value);
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
		deleteLink(this->first);
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
	Iterator<T> begin() const
	{
		return Iterator<T>(this->first);
	}
};

template <class T>
typename LinkList<T>::ListManager<T>* LinkList<T>::listManager = new ListManager<T>;