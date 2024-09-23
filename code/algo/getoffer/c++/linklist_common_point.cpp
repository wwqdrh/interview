struct ListNode {
  int Val;
  ListNode *Next;
  ListNode(int x) : Val(x), Next(nullptr) {}
};

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
  if (headA == nullptr || headB == nullptr) {
    return nullptr;
  }

  ListNode *pa = headA;
  ListNode *pb = headB;

  while (pa != pb) {
    pa = (pa == nullptr) ? headB : pa->Next;
    pb = (pb == nullptr) ? headA : pb->Next;
  }

  return pa;
}
