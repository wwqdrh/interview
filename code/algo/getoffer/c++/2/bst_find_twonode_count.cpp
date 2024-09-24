#include <unordered_set>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  bool findTarget(TreeNode *root, int k) {
    std::unordered_set<int> visit;
    bool flag = false;
    inorder(root, k, visit, flag);
    return flag;
  }

private:
  void inorder(TreeNode *node, int k, std::unordered_set<int> &visit,
               bool &flag) {
    if (!node || flag) {
      return;
    }
    inorder(node->left, k, visit, flag);
    if (visit.count(k - node->val)) {
      flag = true;
      return;
    }
    visit.insert(node->val);
    inorder(node->right, k, visit, flag);
  }
};
