#include "LinkedList.h"
#include <iostream>

using namespace std;

LinkedList::LinkedList()
{
	// initialize the head to a nullptr
	head = nullptr;
}

LinkedList::LinkedList(const LinkedList& rhs)
{
	// if the rhs is an empty linkedlist, then just set head to nullptr
	if (rhs.head == nullptr) {
		head = nullptr;
		return;
	}

	// if the rhs is not empty, then copy the value for rhs over to current linkedlist

	Node* rhsHead = rhs.head;

	// copy over the head node first
	head = new Node;
	head->value = rhsHead->value;
	head->next = nullptr;

	// initialize iterator pointers for both linkedlists
	Node* curIt = head;	
	Node* rhsIt = rhsHead;

	while (rhsIt->next != nullptr) {
		// make a new node for curIt->next
		curIt->next = new Node;
		curIt->next->value = rhsIt->next->value;
		curIt->next->next = nullptr;

		// increment
		rhsIt = rhsIt->next;
		curIt = curIt->next;
	}
	
}

LinkedList::~LinkedList()
{
	// start from the head
	Node* t = head;
	// and loop through every node deleting it
	while (t != nullptr) {
		Node* n = t->next;
		delete t;
		t = n;
	}
	// INCLUDING THE HEAD NODE
}

const LinkedList& LinkedList::operator=(const LinkedList& rhs)
{
	// make sure no aliasing and its not assigning to itself
	if (this != &rhs) {
		// destruct everthing with deep destruction (from destructor)
		Node* t = head;
		while (t != nullptr) {
			Node* n = t->next;
			delete t;
			t = n;
		}

		// initialize head pointer bc we deleted it ^^
		head = nullptr;

		// copy over rhs (same code as copy constructor i think)

		// if the rhs is an empty linkedlist, then just set head to nullptr
		if (rhs.head == nullptr) {
			head = nullptr;
			return *this;
		}

		// if the rhs is not empty, then copy the value for rhs over to current linkedlist

		Node* rhsHead = rhs.head;

		// copy over the head node first
		head = new Node;
		head->value = rhsHead->value;
		head->next = nullptr;

		// initialize iterator pointers for both linkedlists
		Node* curIt = head;
		Node* rhsIt = rhsHead;

		while (rhsIt->next != nullptr) {
			// make a new node for curIt->next
			curIt->next = new Node;
			curIt->next->value = rhsIt->next->value;
			curIt->next->next = nullptr;

			// increment
			rhsIt = rhsIt->next;
			curIt = curIt->next;
		}
	}
	return *this;	
}

void LinkedList::insertToFront(const ItemType& val)
{
	// code taken from lecture slides 
	// ft. Professor Ambrosio :)

	// create a new node with value val and put it in front of head
	Node* temp = new Node;
	temp->value = val;
	temp->next = head;
	head = temp;
}

void LinkedList::printList() const
{
	// loop through every node with while loop and print it out
	Node* temp = head;
	while (temp != nullptr) {
		cout << temp->value << " ";
		temp = temp->next;
	}
	// new line afterwards to clean it up
	cout << endl;
}

bool LinkedList::get(int i, ItemType& item) const
{
	// check if i is valid
	if (i < 0)
		return false;

	// loop through and keep an index of where we are
	Node* temp = head;
	int index = 0;

	// loop through
	while (temp != nullptr) {
		// correct index, replace value, return true
		if (index == i) {
			item = temp->value;
			return true;
		}
		temp = temp->next;
		index++;
	}
	// i too big
	return false;
}

void LinkedList::reverseList()
{
	// reversing each pointer in the linkedlist
	Node* p = nullptr;
	Node* c = head;
	Node* n = nullptr;
	// make sure that we don't reach the end yet
	while (c != nullptr) {
		n = c->next;
		c->next = p;
		p = c;
		c = n;
	}
	head = p;
}

void LinkedList::printReverse() const
{
	// take advantage of get function to print reverse
	int s = size();
	ItemType i;

	// kind of like printing an array in reverse (or vector)
	for (int x = s - 1; x >= 0; x--) {
		get(x, i);
		cout << i << " ";
	}
	cout << endl;
}

void LinkedList::append(const LinkedList& other)
{
	// stick all the elements of other at the bottom
	
	// first loop through all elements in other's linkedlist
	Node* otherIt;
	otherIt = other.head;
	while (otherIt != nullptr) {

		// take each value and add it to the end of current linkedlist

		// code taken from addtoend lecture ft. Professor Ambrosio
		ItemType val = otherIt->value;

		// take advantage of addtoFront 
		if (head == nullptr) {
			insertToFront(val);
		}
		else {
			// go to end of linkedlist and add to the end
			Node* temp;
			temp = head;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			Node* n = new Node;
			n->value = val;
			temp->next = n;

			n->next = nullptr;
		}
		otherIt = otherIt->next;
	}
}

void LinkedList::swap(LinkedList& other)
{
	// only need to swap the header nodes for this
	Node* temp = other.head;
	other.head = head;
	head = temp;
}

int LinkedList::size() const
{
	// loop through and keep a running counter of num elements
	int tot = 0;
	Node* temp = head;

	// loop through and increment tot
	while (temp != nullptr) {
		tot++;
		temp = temp->next;
	}
	return tot;
}
