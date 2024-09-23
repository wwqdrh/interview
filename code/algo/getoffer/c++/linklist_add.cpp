#include <vector>

struct ListNode {
  int Val;
  ListNode *Next;
  ListNode(int x) : Val(x), Next(nullptr) {}
};

ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
  std::vector<int> s1, s2;
  while (l1 != nullptr) {
    s1.push_back(l1->Val);
    l1 = l1->Next;
  }
  while (l2 != nullptr) {
    s2.push_back(l2->Val);
    l2 = l2->Next;
  }

  int carry = 0;
  ListNode *head = nullptr;
  while (!s1.empty() || !s2.empty() || carry != 0) {
    int sum = 0;
    if (!s1.empty()) {
      sum += s1.back();
      s1.pop_back();
    }
    if (!s2.empty()) {
      sum += s2.back();
      s2.pop_back();
    }
    sum += carry;
    ListNode *node = new ListNode(sum % 10);
    node->Next = head;
    head = node;
    carry = sum / 10;
  }

  return head;
}
