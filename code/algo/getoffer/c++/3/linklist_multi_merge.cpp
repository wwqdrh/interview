#include <queue>
#include <vector>

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
  ListNode dummyHead(0);
  ListNode *p = &dummyHead;
  ListNode *p1 = list1;
  ListNode *p2 = list2;

  while (p1 != nullptr && p2 != nullptr) {
    if (p1->val > p2->val) {
      p->next = p2;
      p2 = p2->next;
    } else {
      p->next = p1;
      p1 = p1->next;
    }
    p = p->next;
  }

  if (p1 != nullptr) {
    p->next = p1;
  }
  if (p2 != nullptr) {
    p->next = p2;
  }

  return dummyHead.next;
}

ListNode *mergeKLists(std::vector<ListNode *> &lists) {
  ListNode *res = nullptr;
  for (ListNode *list : lists) {
    res = mergeTwoLists(res, list);
  }
  return res;
}
