#ifndef TEMPLATE_LINKED_LIST_H_INCLUDED
#define TEMPLATE_LINKED_LIST_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

template <class GenericLinkedListItem> class LinkedListItem;
template <class GenericLinkedListItem> class ListIterator;
template <class GenericLinkedListItem> class LinkedList;

template <class GenericLinkedListItem> class LinkedListItem
{
	public:
	
		friend class LinkedList<GenericLinkedListItem>;
		friend class ListIterator<GenericLinkedListItem>;

		/*
		* Create a new list-entry
		*/
		LinkedListItem(GenericLinkedListItem value)
		{
			this->value = value;			
			prev = next = NULL;
		};
	
		GenericLinkedListItem value;
		LinkedListItem * prev, * next;
};

template <class GenericLinkedListItem> class ListIterator
{
	public:
	
		friend class LinkedList<GenericLinkedListItem>;

		/*
		* Prefix++: Returns and sets internal pointer to next item in list
		*/
		LinkedListItem<GenericLinkedListItem> * operator++()
		{
			if(item)
			{
				item = item->next;
			}
			
			return item;
		};
	
		/*
		* Prefix--: Returns and sets internal pointer to previous item in list
		*/
		LinkedListItem<GenericLinkedListItem> * operator--()
		{
			if(item)
			{
				item = item->prev;
			}
			
			return item;
		};

		/*
		* Postfix++: Returns pointer to current item and then increments to next item in list
		*/
		LinkedListItem<GenericLinkedListItem> * operator++(int)
		{
			LinkedListItem<GenericLinkedListItem> * temp = item;
		
			if(item)
			{
				item = item->next;
			}
			
			return temp;
		};
	
		/*
		* Postfix--: Returns pointer to current item and then decrements to previous item in list
		*/
		LinkedListItem<GenericLinkedListItem> * operator--(int)
		{
			LinkedListItem<GenericLinkedListItem> * temp = item;
		
			if(item)
			{
				item = item->prev;
			}
			
			return temp;
		};
	
		/*
		* Returns current item
		*/
		LinkedListItem<GenericLinkedListItem> * operator*()
		{
			return item;
		};
		
	private:
	
		LinkedListItem<GenericLinkedListItem> * item;
};

template <class GenericLinkedListItem> class LinkedList
{
	public:

		LinkedList();
		virtual ~LinkedList();
		
		/*
		* Insert new item at beginning of list
		*/
		bool prepend(GenericLinkedListItem value);
		
		/*
		* Insert new item a position (0 to getLength() - 1),
		* if pos is out of range, the item is pre-/appended
		*/
		bool insert(GenericLinkedListItem value, int pos);
		
		/*
		* Appends item at end of list
		*/
		bool append(GenericLinkedListItem value);
		
		/*
		* Removes list entry at position, if pos is out of
		* range false is returned
		*/
		virtual bool remove(int pos);
		
		/*
		* Remove pointed to item. No safety checks are performed.
		* The caller must ensure that value is actually pointing to sth.
		*/
		virtual bool remove(LinkedListItem<GenericLinkedListItem> * value);
		
		/*
		* Removes all items from the list
		*/
		virtual bool clear(void);
		
		/*
		* Returns number of items in list
		*/
		int getSize(void);
		
		/*
		* Returns item at position
		*/
		LinkedListItem<GenericLinkedListItem> * getItem(int pos);
		
		/*
		* Returns a list-iterator object
		*/
		ListIterator<GenericLinkedListItem> getIterator(int pos = 0);
		
	protected:

		ListIterator<GenericLinkedListItem> iter;
		LinkedListItem<GenericLinkedListItem> * head, * tail;
		int size;
};

template <class GenericLinkedListItem> LinkedList<GenericLinkedListItem>::LinkedList()
{
	head = tail = NULL;
	size = 0;
}

template <class GenericLinkedListItem> LinkedList<GenericLinkedListItem>::~LinkedList()
{
	clear();
}

template <class GenericLinkedListItem> bool LinkedList<GenericLinkedListItem>::prepend(GenericLinkedListItem value)
{
	LinkedListItem<GenericLinkedListItem> * item = new LinkedListItem<GenericLinkedListItem>(value);

	if(!item)
	{
		return false;
	}

	if(head)
	{
		item->next = head;	
		head->prev = item;
	}
	
	head = item;
	
	if(!tail)
	{
		tail = head;
	}
	
	size++;
	return true;
}

template <class GenericLinkedListItem> bool LinkedList<GenericLinkedListItem>::insert(GenericLinkedListItem value, int pos)
{
	LinkedListItem<GenericLinkedListItem> * temp;
	int i;

	if(pos <= 0)
	{
		return prepend(value);
	}
	
	if(pos >= size)
	{
		return append(value);
	}
	
	LinkedListItem<GenericLinkedListItem> * item = new LinkedListItem<GenericLinkedListItem>(value);
	
	if(!item)
	{
		return false;
	}

	temp = head;
	
	for(i = 0; i < pos; i++)
	{
		temp = temp->next;
	}
	
	item->prev = temp->prev;
	item->next = temp;
	
	item->next->prev = item;
	item->prev->next = item;
	
	size++;
	return true;
}

template <class GenericLinkedListItem> bool LinkedList<GenericLinkedListItem>::append(GenericLinkedListItem value)
{
	LinkedListItem<GenericLinkedListItem> * item = new LinkedListItem<GenericLinkedListItem>(value);
	
	if(!item)
	{
		return false;
	}
	
	if(tail)
	{
		item->prev = tail;
		tail->next = item;
	}
	
	tail = item;
	
	if(!head)
	{
		head = tail;
	}
	
	size++;
	return true;
}

template <class GenericLinkedListItem> bool LinkedList<GenericLinkedListItem>::remove(int pos)
{
	LinkedListItem<GenericLinkedListItem> * temp;
	int i;
	
	if(pos < 0 || pos >= size)
	{
		return false;
	}
	
	// fetch entry
	if(pos == 0)
	{
		temp = head;
		if((head = head->next) != NULL)
		{
			head->prev = NULL;
		}
	}
	else if(pos == (size - 1))
	{
		temp = tail;
		if((tail = tail->prev) != NULL)
		{
			tail->next = NULL;
		}
	}
	else
	{
		temp = head;
	
		for(i = 0; i < pos; i++)
		{
			temp = temp->next;
		}
		
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	
	//delete entry
	delete temp;
	
	// list is now one shorter
	size--;
	
	// if list is empty
	if(size == 0)
	{
		head = tail = NULL;
	}

	return true;
}

template <class GenericLinkedListItem> bool LinkedList<GenericLinkedListItem>::remove(LinkedListItem<GenericLinkedListItem> * item)
{
	if(!item)
	{
		return false;
	}
	
	if(item == head)
	{
		head = item->next;	
	}

	if(item == tail)
	{
		tail = item->prev;
	}
	
	if(item->next)
	{
		item->next->prev = item->prev;
	}
	
	if(item->prev)
	{
		item->prev->next = item->next;
	}
	
	delete item;
	
	size--;
	return true;
}

template <class GenericLinkedListItem> bool LinkedList<GenericLinkedListItem>::clear(void)
{
	while(size)
	{
		if(!remove(0))
		{
			return false;
		}
	}
	
	return true;
}

template <class GenericLinkedListItem> int LinkedList<GenericLinkedListItem>::getSize(void)
{
	return this->size;
}

template <class GenericLinkedListItem> LinkedListItem<GenericLinkedListItem> * LinkedList<GenericLinkedListItem>::getItem(int pos)
{
	LinkedListItem<GenericLinkedListItem> * temp;
	int i;
	
	if((pos < 0) || (pos >= size))
	{
		return NULL;
	}
	
	temp = head;
	
	for(i = 0; i < pos; i++)
	{
		temp = temp->next;
	}
	
	return temp;
}

template <class GenericLinkedListItem> ListIterator<GenericLinkedListItem> LinkedList<GenericLinkedListItem>::getIterator(int pos)
{
	int i;
	ListIterator<GenericLinkedListItem> iter;

	if(pos <= 0)
	{
		iter.item = head;
	}
	else if(pos >= (size - 1))
	{
		iter.item = tail;
	}
	else
	{
		iter.item = head;
	
		for(i = 0; (i < pos) && (*iter != NULL); i++)
		{
			iter++;
		}
	}

	return iter;
}

#endif
