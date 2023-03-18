
/*
This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked nodes that has two pointers,
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

/*

The NodePriority: item of type T and a "next" pointer
-------------
| item| next | --->
-------------
General Queue case:

frontPtr																backPtr
\											   						/
\											  					   /
------------- 	  ------------- 	  ------------- 	  -------------
| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
------------- 	  ------------- 	  ------------- 	  -------------

Empty Case:

frontptr	 backptr
\	 /
\	/
---- NULL ------


Single NodePriority Case:
frontPtr	 backPtr
\		/
\	   /
-----------
|item| next| -->NULL
-----------

*/

#ifndef PRIORITY_QUEUE_
#define PRIORITY_QUEUE_

#include "NodePriority.h"
#include "LinkedQueue.h"
#include "Cargos.h"
#include "Time.h"
#include <vector>
using namespace std;


template <typename T, typename U>
class PriorityQueue
{
private:

	NodePriority<T, U>* backPtr;
	NodePriority<T, U>* frontPtr;
	int size;
public:
	PriorityQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry, U key);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	~PriorityQueue();

	int getSize();
	void printQueue();


	//copy constructor
	PriorityQueue(const PriorityQueue<T, U>& LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T, typename U>
PriorityQueue<T, U>::PriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T, typename U>
bool PriorityQueue<T, U>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T, typename U>
bool PriorityQueue<T, U>::enqueue(const T& newEntry, U key)
{
	NodePriority<T, U>* newNodePtr = new NodePriority<T, U>(newEntry, key);
	// Insert the new NodePriority
	if (isEmpty())	//special case if this is the first NodePriority to insert
		frontPtr = newNodePtr; // The queue is empty
	else
	{

		// newNode has higher priority than the frontPtr
		if (frontPtr->getKey() > newNodePtr->getKey())
		{

			newNodePtr->setNext(frontPtr);
			frontPtr = newNodePtr;

		}
		else
		{

			// DON'T SET backPtr to the newNode

			// Reach to the last node of the same priority
			NodePriority<T, U>* trav = frontPtr;
			while (trav->getNext())
			{

				if (trav->getNext()->getKey() > newNodePtr->getKey())
					break;

				trav = trav->getNext();

			}

			// Last Node
			if (trav->getNext() == nullptr)
			{

				trav->setNext(newNodePtr);
				backPtr = newNodePtr;
				size++;
				return true;

			}

			// Insert newNode
			newNodePtr->setNext(trav->getNext());
			trav->setNext(newNodePtr);
			size++;

			return true;

		}

	}

	backPtr = newNodePtr; // New NodePriority is the last NodePriority now
	size++;

	return true;
} // end enqueue


  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  /*Function: dequeue
  Removes the front of this queue. That is, removes the item that was added
  earliest.

  Input: None.
  Output: True if the operation is successful; otherwise false.
  */

template <typename T, typename U>
bool PriorityQueue<T, U>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	NodePriority<T, U>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last NodePriority in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued NodePriority
	delete nodeToDeletePtr;
	size--;

	return true;

}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/
template <typename T, typename U>
bool PriorityQueue<T, U>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////
/*
Function: destructor
removes all nodes from the queue by dequeuing them
*/
template <typename T, typename U>
PriorityQueue<T, U>::~PriorityQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}

template <typename T, typename U>
int PriorityQueue<T, U>::getSize()
{

	return size;

}

/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: PriorityQueue<T>: The Queue to be copied
Output: none
*/

template <typename T, typename U>
PriorityQueue<T, U>::PriorityQueue(const PriorityQueue<T, U>& LQ)
{
	NodePriority<T, U>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first NodePriority
	NodePriority<T, U>* ptr = new NodePriority<T, U>(NodePtr->getItem(), NodePtr->getKey());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		NodePriority<T, U>* ptr = new NodePriority<T, U>(NodePtr->getItem(), NodePtr->getKey());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}

	size = LQ.size;

}

//Print Queue
template <typename T, typename U>
void PriorityQueue<T, U>::printQueue()
{
	T K;
	//LinkedQueue<T> tempQueue;

	PriorityQueue<T, U> tmp = *this;

	for (int i = 0, n = tmp.getSize(); i < n; i++)
	{

		tmp.dequeue(K);
		if (i == n - 1)
			cout << K->getId();
		else
			cout << K->getId() << ", ";
		//tmp.enqueue(K);

		// see if we should delete the node or not
		// after testing we shouldn't delete as it is deep copy but same objects!
		// because node are carrying pointers to object not the object it self
		// so we don't have to delete K because it is a pointer to the same object not a new object

	}
	//for (int i = 0, n = size; i < n; i++)
	//{
	//	this->dequeue(K);
	//	if (i == n - 1)
	//		cout << K->getId();
	//	else
	//		cout << K->getId() << ", ";
	//	tempQueue.enqueue(K);

	//}

	//while (tempQueue.dequeue(K))
	//	 this->enqueue(K, K->getPriority());

}

#endif