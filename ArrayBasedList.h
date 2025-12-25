/*-- ArrayBasedList.h ------------------------------------------------------

  This header file defines the class ArrayBasedList for managing a linked list
  using a fixed-size array-based node pool. The list uses integer indices to
  simulate pointers and relies on the NodePool class for memory management.

  Basic operations are:
    Constructor
    Destructor
    empty:Check if list is empty
    insert:Insert an item at a position
    remove:Delete an item at a position
    search:Find the position of a value
    display:Output the list

  Copying and assignment are explicitly disabled to prevent shallow copies
  and unsafe sharing of the underlying node pool.

-------------------------------------------------------------------------*/

#ifndef ARRAYBASEDLIST_H
#define ARRAYBASEDLIST_H
#include <string>
#include "nodePool.h"
#include <iostream>

class ArrayBasedList
{
public:
    /******** Function Members ********/

    ArrayBasedList(NodePool* externalPool);
    /*----------------------------------------------------------------------
      Construct an ArrayBasedList using an external NodePool.

      Precondition:  externalPool points to a valid NodePool object.
      Postcondition: An empty list is created with head = NULL_INDEX.
    -----------------------------------------------------------------------*/

    ~ArrayBasedList();
    /*----------------------------------------------------------------------
     Destroy the list and return all nodes to the free list.

     Precondition:  None
     Postcondition: All nodes in the list are released to the NodePool.
    -----------------------------------------------------------------------*/

    bool empty() const;
    /*----------------------------------------------------------------------
     Check if the list is empty.

     Precondition:  None
     Postcondition: Returns true if list is empty, false otherwise.
    -----------------------------------------------------------------------*/

    bool insert(const ElementType& value, int position);
    /*----------------------------------------------------------------------
     Insert a value at a given position in the list.

     Precondition:  0 <= position <= current list length; node pool has space.
     Postcondition: value is inserted at position; list is updated.
    -----------------------------------------------------------------------*/

    bool remove(int position);
    /*----------------------------------------------------------------------
     Remove the node at a given position.

     Precondition:  0 <= position < current list length.
     Postcondition: Node is removed and returned to the NodePool.
    -----------------------------------------------------------------------*/

    int search(const ElementType& value) const;
    /*----------------------------------------------------------------------
     Search for a value in the list.

     Precondition:  None
     Postcondition: Returns position of value if found, -1 otherwise.
    -----------------------------------------------------------------------*/

    void display() const;
    /*----------------------------------------------------------------------
     Display the contents of the list.

     Precondition:  None
     Postcondition: Outputs list elements in order to standard output.
    -----------------------------------------------------------------------*/

    int length() const;
    /*----------------------------------------------------------------------
      Return the number of elements in the list.

      Precondition:  None
      Postcondition: Returns the count of active nodes in the list.
    -----------------------------------------------------------------------*/

    void clear();
    /*----------------------------------------------------------------------
      Clear the list and return all nodes to the NodePool.

      Precondition:  None
      Postcondition: List is empty and all nodes are released.
    -----------------------------------------------------------------------*/

    int getHead() const;
    /*----------------------------------------------------------------------
      Get the index of the head node.

      Precondition:  None
      Postcondition: Returns the index of the first node in the list.
    -----------------------------------------------------------------------*/

    /***** Copy constructor *****/
    ArrayBasedList(const ArrayBasedList&);
    /*----------------------------------------------------------------------
     Copy constructor.

     Precondition:  None
     Postcondition: A new list is created with the same contents as source.
    -----------------------------------------------------------------------*/

    ArrayBasedList& operator=(const ArrayBasedList&);
    /*----------------------------------------------------------------------
     Assignment operator.

     Precondition:  None
     Postcondition: The current list is cleared and replaced with a copy of source.
    -----------------------------------------------------------------------*/

private:
    /******** Data Members ********/

    int head; // Index of first node in the list
    NodePool* pool; // Pointer to external node pool
    int mySize; // Size of the array

};

#endif