#include <algorithm>
#include <vector>

const int highBit = 30;

class Trie {
public:
  Trie *left = nullptr;
  Trie *right = nullptr;

  void add(int num) {
    Trie *cur = this;
    for (int i = highBit; i >= 0; --i) {
      int bit = (num >> i) & 1;
      if (bit == 0) {
        if (cur->left == nullptr) {
          cur->left = new Trie();
        }
        cur = cur->left;
      } else {
        if (cur->right == nullptr) {
          cur->right = new Trie();
        }
        cur = cur->right;
      }
    }
  }

  int check(int num) {
    Trie *cur = this;
    int x = 0;
    for (int i = highBit; i >= 0; --i) {
      int bit = (num >> i) & 1;
      if (bit == 0) {
        if (cur->right != nullptr) {
          cur = cur->right;
          x = x * 2 + 1;
        } else {
          cur = cur->left;
          x = x * 2;
        }
      } else {
        if (cur->left != nullptr) {
          cur = cur->left;
          x = x * 2 + 1;
        } else {
          cur = cur->right;
          x = x * 2;
        }
      }
    }
    return x;
  }
};

int findMaximumXOR(const std::vector<int> &nums) {
  Trie *root = new Trie();
  int x = 0;
  for (int i = 1; i < nums.size(); ++i) {
    root->add(nums[i - 1]);
    x = std::max(x, root->check(nums[i]));
  }
  return x;
}
