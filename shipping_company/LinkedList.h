#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
#include <iostream>

using namespace std;

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
	int size;

public:


	LinkedList()
	{
		Head = nullptr;
		size = 0;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{
		Node<T>* p = Head;

		while (p)
		{

			if (p->getNext() == nullptr)
				cout << p->getItem()->getId();
			else
				cout << p->getItem()->getId() << ",";
			p = p->getNext();
		}
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		size++;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}

		size = 0;

	}



	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data)
	{



		Node<T>* newNode = new Node<T>(data);

		if (newNode == nullptr)
			return;

		newNode->setNext(nullptr);

		// Empty
		if (Head == nullptr)
		{

			Head = newNode;
			size++;
			return;

		}


		Node<T>* trav = Head;
		while (trav->getNext())
			trav = trav->getNext();

		trav->setNext(newNode);
		size++;

	}

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	T Find(int Key)
	{
		bool found = false;
		Node<T>* curr = Head;
		while (curr)
		{
			if (curr->getItem()->getId() == Key) // Truck* 
			{
				return curr->getItem();
			}
			curr = curr->getNext();
		}
		return nullptr;
	}

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value);

	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst(T& value, bool deletePermenant = false)
	{

		Node<T>* p = Head;

		if (p)
		{
			Head = Head->getNext();
			if (deletePermenant)
				delete p;
			else
				value = p->getItem();
			//Head = p->getNext();
			size--;
		}
	}


	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast()
	{
		Node<T>* p = Head;
		Node<T>* temp = new Node<T>;

		if (p)
		{
			if (Head->getNext() == nullptr)
			{
				DeleteFirst();
				return;
			}
			while (p->getNext()->getNext())
			{
				p = p->getNext();
			}

			temp->setNext(p->getNext());
			p->setNext(nullptr);
			delete temp;
			size--;
		}
	}


	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(T& value, bool deletePermenant = false)
	{
		if (!Head) return false;
		Node<T>* p = Head;
		Node<T>* prev = Head;
		Node<T>* temp = nullptr;

		for (int i = 0; i < size; i++)
		{


			if (p->getItem() == value)
			{

				// first node
				if (i == 0)
				{

					DeleteFirst(value);
					return true;

				}

				temp = p;
				prev->setNext(p->getNext());
				//delete temp;
				value = temp->getItem();
				size--;
				return true;

			}
			prev = p;
			p = p->getNext();

		}
		return false;

	}
	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T& value);

	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	void Merge(const LinkedList& L);

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse();

	//[10]sethead

	void Sethead(Node<T>* newhead)
	{
		Head = newhead;
	}

	//[11] gethead
	Node<T>* Gethead()
	{
		return Head;
	}

	int getSize()
	{

		return size;

	}

	T GetFirstObj()
	{

		return Head->getItem();

	}

};

#endif	
