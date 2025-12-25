/*-- nodePool.h -------------------------------------------------------------

  This header file defines the data types Node and NodePool for managing
  a fixed-size array-based storage pool used in linked list implementations.

  The Node class represents individual nodes containing a data element and
  an integer link to the next node. The NodePool class manages a static array
  of Node objects and simulates dynamic memory allocation using a free list.

  Basic operations are:
     Node:Represents a single node with data and link index
     NodePool:Manages allocation and deallocation of nodes
     initializePool:Set up the free list
     acquireNode:Allocate a node from the pool
     releaseNode:Return a node to the pool
     getNode:Access a node by index
     displayFreeList: Show the current free list
     clear:Reset the pool
     list:Display all nodes
     length:Count used nodes

-----------------------------------------------------------------------------*/

#ifndef NODEPOOL_H
#define NODEPOOL_H

using namespace std;
#include <iostream>
#include <string>
const int NUM_NODES = 10; // The capacity of the node pool.
const int NULL_INDEX = -1;//value representing a null or invalid index.
typedef string ElementType;//Defines the type of data stored in each node.

/*** Node class ***/
class Node
{
public:
    /***** Constructors *****/
    Node();
    /*----------------------------------------------------------------------
     Construct a Node object with default values.

     Precondition:  None
     Postcondition: data is empty string, next is NULL_INDEX.
    -----------------------------------------------------------------------*/

    Node(const ElementType& value, int nextIndex = NULL_INDEX);
    /*----------------------------------------------------------------------
     Construct a Node object with given data and next index.

     Precondition:  value is the data to store; nextIndex is the link.
     Postcondition: data and next are initialized accordingly.
    -----------------------------------------------------------------------*/

    /***** Data Members *****/
    ElementType data;// Data stored in the node
    int next;// Index of the next node
};

/*** NodePool class ***/
class NodePool
{
public:
    /***** Function Members *****/
    NodePool();
    /*----------------------------------------------------------------------
     Construct a NodePool object and initialize the free list.

     Precondition:  None
     Postcondition: All nodes are linked into a free list.
    -----------------------------------------------------------------------*/

    void initializePool();
    /*----------------------------------------------------------------------
     Initialize the node pool by linking all nodes into a free list.

     Precondition:  None
     Postcondition: Nodes are linked from 0 to NUM_NODES - 1; freePtr = 0.
    -----------------------------------------------------------------------*/

    bool isFull() const;
    /*----------------------------------------------------------------------
      Check if the node pool is full (no free nodes available).

      Precondition:  None
      Postcondition: Returns true if no nodes are available, false otherwise.
    -----------------------------------------------------------------------*/

    int acquireNode();
    /*----------------------------------------------------------------------
     Allocate a node from the free list.
     Precondition:  At least one node is available
     Postcondition: Returns index of allocated node.
    -----------------------------------------------------------------------*/

    void releaseNode(int index);
    /*----------------------------------------------------------------------
     Return a node to the free list.

     Precondition:  index is a valid node index.
     Postcondition: Node is inserted at the front of the free list.
    -----------------------------------------------------------------------*/

    Node& getNode(int index);
    /*----------------------------------------------------------------------
     Access a node by index.

     Precondition:  index is a valid node index.
     Postcondition: Returns a reference to the node at given index.
    -----------------------------------------------------------------------*/

    void displayFreeList() const;
    /*----------------------------------------------------------------------
     Display the indices of the current free list.

     Precondition:  None
     Postcondition: Outputs the free list to standard output.
    -----------------------------------------------------------------------*/

    void clear();
    /*----------------------------------------------------------------------
     Reset the node pool to its initial state.

     Precondition:  None
     Postcondition: All nodes are returned to the free list.
    -----------------------------------------------------------------------*/

    void list() const;
    /*----------------------------------------------------------------------
     Display all nodes in the pool with their data and next index.

     Precondition:  None
     Postcondition: Outputs each node's index, data, and next value
    -----------------------------------------------------------------------*/

    int length() const;
    /*----------------------------------------------------------------------
     Return the number of nodes currently in use.

     Precondition:  None
     Postcondition: Returns the count of nodes not in the free list.
    -----------------------------------------------------------------------*/

private:
    /***** Data Members *****/
    Node pool[NUM_NODES];// Array of nodes
    int freePtr;// Index of first free node
};

#endif