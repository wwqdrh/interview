#include <vector>

struct ListNode {
  int Val;
  ListNode *Next;
  ListNode(int x) : Val(x), Next(nullptr) {}
};

void reorderList(ListNode *head) {
  if (head == nullptr) {
    return;
  }

  std::vector<ListNode *> nodes;
  for (ListNode *node = head; node != nullptr; node = node->Next) {
    nodes.push_back(node);
  }

  int i = 0, j = nodes.size() - 1;
  while (i < j) {
    nodes[i]->Next = nodes[j];
    ++i;
    if (i == j) {
      break;
    }
    nodes[j]->Next = nodes[i];
    --j;
  }
  nodes[i]->Next = nullptr;
}
