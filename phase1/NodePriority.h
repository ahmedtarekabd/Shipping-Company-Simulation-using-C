#ifndef _NODE_PRIORITY
#define _NODE_PRIORITY

//First let's declare a single NodePriority in the list
template<typename T, typename U>
class NodePriority
{
private:
	T item;	// A data item (can be any complex sturcture)
	NodePriority<T, U>* next;	// Pointer to next NodePriority
	U key;

public:

	NodePriority() //default constructor
	{
		next = nullptr;
		key = 1;
	}

	NodePriority(T newItem, U k) //non-default constructor
	{
		item = newItem;
		next = nullptr;
		key = k;
	}

	void setItem(T newItem)
	{
		item = newItem;
	} // end setItem

	void setNext(NodePriority<T, U>* nextNodePtr)
	{
		next = nextNodePtr;
	} // end setNext

	void setKey(U k)
	{

		key = k;

	} // end setKey

	T getItem() const
	{
		return item;
	} // end getItem

	NodePriority<T, U>* getNext() const
	{
		return next;
	}

	U getKey()
	{

		return key;

	}

}; // end NodePriority

#endif	
