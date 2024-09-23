#include <vector>

struct ListNode {
  int Val;
  ListNode *Next;
  ListNode(int x) : Val(x), Next(nullptr) {}
};

bool isLinkListPalindrome(ListNode *head) {
  std::vector<int> vals;
  for (ListNode *node = head; node != nullptr; node = node->Next) {
    vals.push_back(node->Val);
  }

  int n = vals.size();
  for (int i = 0; i < n / 2; ++i) {
    if (vals[i] != vals[n - 1 - i]) {
      return false;
    }
  }
  return true;
}
