#ifndef LinkedList_h
#define LinkedList_h

#include <string>
using namespace std;

typedef string ItemType;

struct Node {
    ItemType value;
    Node* next;
};

class LinkedList {

private:
    // head node of the linkedlist
    Node* head;

public:
    // Name: LinkedList
    // Input: ----
    // Output: ----
    // Description: default constructor
    LinkedList();

    // Name: LinkedList
    // Input: LinkedList reference rhs
    // Output: ----
    // Description: copy constructor
    LinkedList(const LinkedList& rhs);

    // Name: ~LinkedList
    // Input: ----
    // Output: ----
    // Description: Destroys all the dynamically allocated memory
    // in the list. Acts as desctructor.
    ~LinkedList();

    // Name: operator=
    // Input: LinkedList reference rhs
    // Output: LinkedList reference *this
    // Description: assignment operator
    const LinkedList& operator=(const LinkedList& rhs);

    // Name: insertToFront
    // Input: ItemType reference val
    // Output: ----
    // Description: Inserts val at the front of the list
    void insertToFront(const ItemType& val);

    // Name: printList
    // Input: ----
    // Output: ---- (outputs to screen)
    // Description: Prints the LinkedList
    void printList() const;

    // Name: get
    // Input: integer i (index), and ItemType reference item
    // Output: boolean (successful or not)
    // Description: Sets item to the value at position i in this
    // LinkedList and return true, returns false if
    // there is no element i
    bool get(int i, ItemType& item) const;

    // Name: reverseList
    // Input: ----
    // Output: ----
    // Description: Reverses the LinkedList
    void reverseList();

    // Name: printReverse
    // Input: ----
    // Output: ----
    // Description: Prints the LinkedList in reverse order
    // does NOT reverse it actually
    void printReverse() const;

    // Name: append
    // Input: LinkedList reference other
    // Output: ----
    // Description: Appends the values of other onto the end of this
    // LinkedList.
    void append(const LinkedList& other);

    // Name: swap
    // Input: Linkedlist reference other
    // Output: ----
    // Description: Exchange the contents of this LinkedList with the other
    // one.
    void swap(LinkedList& other);

    // Name: size
    // Input: ----
    // Output: integer (size of the linkedlist)
    // Description: Returns the number of items in the Linked List.
    int size() const;
};

#endif /* LinkedList_h */