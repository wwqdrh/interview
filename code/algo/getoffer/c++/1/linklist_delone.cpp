struct ListNode {
  int Val;
  ListNode *Next;
  ListNode(int x) : Val(x), Next(nullptr) {}
};

ListNode *removeNthFromEnd(ListNode *head, int n) {
  ListNode *dummy = new ListNode(0);
  dummy->Next = head;
  ListNode *first = head;
  ListNode *second = dummy;

  for (int i = 0; i < n; ++i) {
    first = first->Next;
  }

  while (first != nullptr) {
    first = first->Next;
    second = second->Next;
  }

  second->Next = second->Next->Next;
  ListNode *newHead = dummy->Next;
  delete dummy; // Free the allocated memory for dummy node
  return newHead;
}
