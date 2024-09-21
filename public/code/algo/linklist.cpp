#include "linkedlist.h"

void reverseLinkedList() {
  LinkList list;
  list.pushFront(5);
  list.pushFront(4);
  list.pushFront(3);
  list.pushFront(2);
  list.pushFront(1);

  std::cout << "Original List: ";
  list.printList();

  list.reverseIterative();
  std::cout << "Reversed List (Iterative): ";
  list.printList();

  list.reverseRecursive();
  std::cout << "Reversed List (Recursive): ";
  list.printList();
}