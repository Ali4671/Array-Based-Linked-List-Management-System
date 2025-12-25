/*
 * Name: Mhamad El Ayoubi, Ali Zreikat, Nehme Nehme
 * Assignment: Tester for Array-Based Linked List Project
 *
 * Description:
 * This program provides an interactive menu to test the ArrayBasedList class.
 * It demonstrates list operations (insert, remove, search, display, clear)
 * while showing the state of the NodePool including the free list.
 */

#include <iostream>
#include "nodePool.h"
#include "ArrayBasedList.h"

 // Function to display menu
void showMenu()
{
    cout << "\n==================== MENU ====================\n";
    cout << "1. Insert element\n";
    cout << "2. Remove element\n";
    cout << "3. Search for element\n";
    cout << "4. Display list\n";
    cout << "5. Display free list\n";
    cout << "6. Clear list\n";
    cout << "0. Exit\n";
    cout << "==============================================\n";
    cout << "Enter choice: ";
}

int main()
{
    // Create node pool and list
    NodePool pool;
    ArrayBasedList list(&pool);

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice)
        {
        case 1: {// Insert
            string value;
            int position;

            cout << "Enter value to insert: ";
            cin >> value;

            cout << "Enter position (0 to " << list.length() << "): ";
            cin >> position;

            if (list.insert(value, position))
                cout << "Inserted successfully.\n";
            else
                cout << "Insert failed.\n";

            break;
        }

        case 2: {// Remove
            int position;
            cout << "Enter position to remove (0 to "
                << list.length() - 1 << "): ";
            cin >> position;

            if (list.remove(position))
                cout << "Removed successfully.\n";
            else
                cout << "Remove failed.\n";

            break;
        }

        case 3: {// Search
            string value;
            cout << "Enter value to search: ";
            cin >> value;

            int pos = list.search(value);
            if (pos != -1)
                cout << "Found at position " << pos << ".\n";
            else
                cout << "Value not found.\n";

            break;
        }

        case 4:// Display list
            list.display();
            break;

        case 5:// Display free list
            pool.displayFreeList();
            break;

        case 6:// Clear list
            list.clear();
            cout << "List cleared.\n";
            break;

        case 0:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid option.\n";
        }

        // Show node pool state after each operation
        cout << "\nCurrent NodePool State:\n";
        pool.list();

    } while (choice != 0);

    return 0;
}
