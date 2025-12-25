/*
 * Name: Mhamad El Ayoubi, Ali Zreikat, Nehme Nehme
 * Date Started: November 15, 2025
 * Date Ended:  November **, 2025
 * Assignment: NodePool Implementation
 *
 * Description:
 * This file implements a node pool for managing fixed-size nodes.
 * Nodes are acquired and released through a free list mechanism.
 * Provides efficient memory reuse for array-based linked list structures.
 */

#include "nodepool.h"
#include <iostream>
using namespace std;

/* -----------------------------
   Node Default Constructor
   Purpose: Initialize a node with default values.
   Input: None
   Output: Node with default data and null link
   ----------------------------- */
Node::Node()
{
    data = ElementType();   // Default-initialize the data
    next = NULL_INDEX;      // Mark as not linked
}

/* -----------------------------
   Node Parameterized Constructor
   Purpose: Initialize a node with given data and next index.
   Input: value (ElementType), nextIndex (int)
   Output: Node with specified data and link
   ----------------------------- */
Node::Node(const ElementType& value, int nextIndex)
{
    data = value;
    next = nextIndex;
}

/* -----------------------------
   NodePool Constructor
   Purpose: Initialize the node pool and set up free list.
   Input: None
   Output: NodePool with all nodes linked in free list
   ----------------------------- */
NodePool::NodePool()
{
    initializePool(); // Set up the free list
}

/* -----------------------------
   initializePool()
   Purpose: Link all nodes into the free list.
   Input: None
   Output: Free list initialized with all nodes
   ----------------------------- */
void NodePool::initializePool()
{
    for (int i = 0; i < NUM_NODES - 1; i++) {
        pool[i].next = i + 1; // Link to the next node
    }
    pool[NUM_NODES - 1].next = NULL_INDEX; // Last node ends the list
    freePtr = 0; // Start of the free list
}

/* -----------------------------
   isFull()
   Purpose: Check if the node pool has no free nodes available.
   Input: None
   Output: true if the pool is full, false otherwise
   ----------------------------- */

bool NodePool::isFull() const
{
    return freePtr == NULL_INDEX;
}

/* -----------------------------
   acquireNode()
   Purpose: Acquire a free node from the pool.
   Input: None
   Output: Index of acquired node, or NULL_INDEX if none available
   ----------------------------- */
int NodePool::acquireNode()
{
    if (freePtr == NULL_INDEX) {
        cerr << "Error: No free nodes available." << endl;
        return NULL_INDEX;
    }

    int index = freePtr;            // Take the first free node
    freePtr = pool[freePtr].next;   // Advance freePtr to next free node
    return index;
}

/* -----------------------------
   releaseNode()
   Purpose: Release a node back into the free list.
   Input: index (int) - node index to release
   Output: None
   ----------------------------- */
void NodePool::releaseNode(int index)
{
    pool[index].next = freePtr; // Link this node to current free list
    freePtr = index;            // Update freePtr to point to this node
}

/* -----------------------------
   getNode()
   Purpose: Access a node by index.
   Input: index (int)
   Output: Reference to node at given index
   ----------------------------- */
Node& NodePool::getNode(int index)
{
    if (index < 0 || index >= NUM_NODES) {
        cerr << "Error: Invalid node index " << index << endl;
        return pool[0]; // Returns first node 
    }
    return pool[index];
}

/* -----------------------------
   displayFreeList()
   Purpose: Display indices of nodes in free list.
   Input: None
   Output: Prints free list to console
   ----------------------------- */
void NodePool::displayFreeList() const
{
    cout << "Free List: ";
    int current = freePtr;
    while (current != NULL_INDEX) {
        cout << current << " ";
        current = pool[current].next;
    }
    cout << endl;
}

/* -----------------------------
   list()
   Purpose: Display contents of the entire node pool.
   Input: None
   Output: Prints data and next index of each node
   ----------------------------- */
void NodePool::list() const
{
    cout << "Node Pool Contents" << endl;
    for (int i = 0; i < NUM_NODES; i++) {
        cout << "[" << i << "] "
            << "Data: \"" << pool[i].data << "\", "
            << "Next: " << pool[i].next << endl;
    }
}

/* -----------------------------
   clear()
   Purpose: Reset the pool by reinitializing free list and clearing data.
   Input: None
   Output: NodePool reset to default state
   ----------------------------- */
void NodePool::clear()
{
    initializePool();  // Re-link all nodes into free list
    for (int i = 0; i < NUM_NODES; i++) {
        pool[i].data = ElementType();  // Clear data
    }
}

/* -----------------------------
   length()
   Purpose: Return number of nodes currently in use.
   Input: None
   Output: Count of used nodes
   ----------------------------- */
int NodePool::length() const
{
    int count = 0;
    int current = freePtr;

    // Count how many nodes are in the free list
    while (current != NULL_INDEX) {
        count++;
        current = pool[current].next;
    }

    return NUM_NODES - count;  // Total nodes minus free ones = used nodes
}