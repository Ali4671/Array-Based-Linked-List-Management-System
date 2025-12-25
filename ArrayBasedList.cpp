/*
 * Name: Mhamad El Ayoubi, Ali Zreikat, Nehme Nehme
 * Date Started: November 15, 2025
 * Date Ended:  November **, 2025
 * Assignment: ArrayBasedList Implementation
 *
 * Description:
 * This file implements an array-based linked list using a node pool.
 * It supports insertion, removal, searching, display, deep copy, and assignment.
 * All nodes are managed through the NodePool to avoid dynamic allocation.
 */

#include "ArrayBasedList.h"
#include <iostream>
using namespace std;

/* -----------------------------
   Constructor
   Purpose: Initialize an empty list with a given external node pool.
   Input: externalPool (pointer to NodePool)
   Output: A new empty list
   ----------------------------- */
ArrayBasedList::ArrayBasedList(NodePool* externalPool)
{
    pool = externalPool;       // Node pool used for memory management
    head = NULL_INDEX;         // Head index starts as null
    mySize = 0;                // Start with empty list
}

/* -----------------------------
   Destructor
   Purpose: Release all nodes back to the pool.
   Input: None
   Output: Frees all nodes, resets list to empty
   ----------------------------- */
ArrayBasedList::~ArrayBasedList()
{
    int current = head;
    while (current != NULL_INDEX) {
        int next = pool->getNode(current).next; // Save next before releasing
        pool->releaseNode(current);             // Return node to pool
        current = next;
    }
    head = NULL_INDEX;
    mySize = 0;
}

/* -----------------------------
   empty()
   Purpose: Check if the list is empty.
   Input: None
   Output: true if empty, false otherwise
   ----------------------------- */
bool ArrayBasedList::empty() const {
    return head == NULL_INDEX;
}

/* -----------------------------
   length()
   Purpose: Return the number of active elements in the list.
   Input: None
   Output: Count of nodes in the list
   ----------------------------- */
int ArrayBasedList::length() const
{
    return mySize;
}


/* -----------------------------
   clear()
   Purpose: Remove all nodes from the list and return them to the pool.
   Input: None
   Output: List becomes empty and all nodes are released
   ----------------------------- */
void ArrayBasedList::clear()
{
    int current = head;

    while (current != NULL_INDEX) {
        int next = pool->getNode(current).next; // Save next
        pool->releaseNode(current);             // Return node to pool
        current = next;
    }

    head = NULL_INDEX;
    mySize = 0;
}

/* -----------------------------
   getHead()
   Purpose: Retrieve the index of the head node.
   Input: None
   Output: Index of the first node in the list
   ----------------------------- */
int ArrayBasedList::getHead() const
{
    return head;
}

/* -----------------------------
   insert()
   Purpose: Insert a new element at a given position.
   Input: value (ElementType), position (int)
   Output: true if successful, false otherwise
   ----------------------------- */
bool ArrayBasedList::insert(const ElementType& value, int position)
{
    // Validate position
    if (position < 0 || position > mySize) {
        cerr << "Error: Invalid position" << endl;
        return false;
    }

    // Acquire new node from pool
    int newIndex = pool->acquireNode();
    if (newIndex == NULL_INDEX) {
        cerr << "Error: Node pool exhausted" << endl;
        return false;
    }

    pool->getNode(newIndex).data = value;

    if (position == 0) {
        // Insert at beginning
        pool->getNode(newIndex).next = head;
        head = newIndex;
    }
    else {
        // Traverse to node before insertion point
        int prev = head;
        for (int i = 0; i < position - 1; i++) {
            prev = pool->getNode(prev).next;
        }
        pool->getNode(newIndex).next = pool->getNode(prev).next;
        pool->getNode(prev).next = newIndex;
    }

    mySize++; // Update size
    return true;
}

/* -----------------------------
   remove()
   Purpose: Remove a node at a given position.
   Input: position (int)
   Output: true if successful, false otherwise
   ----------------------------- */
bool ArrayBasedList::remove(int position)
{
    if (position < 0 || position >= mySize || empty()) {
        cerr << "Error: Invalid position" << endl;
        return false;
    }

    int toRemove;
    if (position == 0) {
        // Remove head
        toRemove = head;
        head = pool->getNode(head).next;
    }
    else {
        // Traverse to node before removal point
        int prev = head;
        for (int i = 0; i < position - 1; i++) {
            prev = pool->getNode(prev).next;
        }
        toRemove = pool->getNode(prev).next;
        pool->getNode(prev).next = pool->getNode(toRemove).next;
    }

    pool->releaseNode(toRemove);
    mySize--; // Update size
    return true;
}

/* -----------------------------
   search()
   Purpose: Search for a specific value in the list.
   Input: value (ElementType)
   Output: Position of value if found, -1 otherwise
   ----------------------------- */
int ArrayBasedList::search(const ElementType& value) const
{
    int current = head;
    int position = 0;

    while (current != NULL_INDEX) {
        if (pool->getNode(current).data == value) {
            return position;
        }
        current = pool->getNode(current).next;
        position++;
    }

    return -1; // Not found
}

/* -----------------------------
   display()
   Purpose: Print the list contents to console.
   Input: None
   Output: Displays list elements
   ----------------------------- */
void ArrayBasedList::display() const
{
    int current = head;
    cout << "List: ";
    while (current != NULL_INDEX) {
        cout << pool->getNode(current).data << " ";
        current = pool->getNode(current).next;
    }
    cout << endl;
}

/* -----------------------------
   Copy Constructor
   Purpose: Create a deep copy of another list.
   Input: source (ArrayBasedList)
   Output: A new list identical to source
   ----------------------------- */
ArrayBasedList::ArrayBasedList(const ArrayBasedList& source)
{
    pool = source.pool;
    head = NULL_INDEX;
    mySize = source.mySize;

    if (source.head == NULL_INDEX)
        return;

    int srcCurrent = source.head;
    int prevNew = NULL_INDEX;

    while (srcCurrent != NULL_INDEX) {
        int newIndex = pool->acquireNode();
        pool->getNode(newIndex).data = pool->getNode(srcCurrent).data;

        if (head == NULL_INDEX) {
            head = newIndex;
        }
        else {
            pool->getNode(prevNew).next = newIndex;
        }

        prevNew = newIndex;
        srcCurrent = pool->getNode(srcCurrent).next;
    }

    if (prevNew != NULL_INDEX)
        pool->getNode(prevNew).next = NULL_INDEX;
}

/* -----------------------------
   operator=
   Purpose: Assignment operator for deep copy.
   Input: source (ArrayBasedList)
   Output: *this updated to match source
   ----------------------------- */
ArrayBasedList& ArrayBasedList::operator=(const ArrayBasedList& source)
{
    if (this != &source) {
        // Clear current list
        int current = head;
        while (current != NULL_INDEX) {
            int next = pool->getNode(current).next;
            pool->releaseNode(current);
            current = next;
        }
        head = NULL_INDEX;
        mySize = 0;

        // Copy from source
        mySize = source.mySize;
        int srcCurrent = source.head;
        int prevNew = NULL_INDEX;

        while (srcCurrent != NULL_INDEX) {
            int newIndex = pool->acquireNode();
            pool->getNode(newIndex).data = pool->getNode(srcCurrent).data;

            if (head == NULL_INDEX) {
                head = newIndex;
            }
            else {
                pool->getNode(prevNew).next = newIndex;
            }

            prevNew = newIndex;
            srcCurrent = pool->getNode(srcCurrent).next;
        }

        if (prevNew != NULL_INDEX)
            pool->getNode(prevNew).next = NULL_INDEX;
    }
    return *this;
}