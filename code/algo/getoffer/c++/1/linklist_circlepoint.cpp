struct ListNode {
  int Val;
  ListNode *Next;
  ListNode(int x) : Val(x), Next(nullptr) {}
};

ListNode *detectCycle(ListNode *head) {
  if (!head)
    return nullptr;

  ListNode *slow = head;
  ListNode *fast = head;

  while (fast != nullptr && fast->Next != nullptr) {
    slow = slow->Next;
    fast = fast->Next->Next;

    if (slow == fast) {
      ListNode *p = head;
      while (p != slow) {
        p = p->Next;
        slow = slow->Next;
      }
      return p;
    }
  }

  return nullptr;
}
