struct ListNode {
  int Val;
  ListNode *Next;
  ListNode(int x) : Val(x), Next(nullptr) {}
};

ListNode *reverseList(ListNode *head) {
  if (head == nullptr || head->Next == nullptr) {
    return head;
  }
  ListNode *newHead = reverseList(head->Next);
  head->Next->Next = head;
  head->Next = nullptr;
  return newHead;
}
