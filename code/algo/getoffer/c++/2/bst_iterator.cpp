#include <stack>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BSTIterator {
public:
  BSTIterator(TreeNode *root) : cur(root) {}

  int next() {
    while (cur) {
      stack.push(cur);
      cur = cur->left;
    }
    cur = stack.top();
    stack.pop();
    int val = cur->val;
    cur = cur->right;
    return val;
  }

  bool hasNext() { return cur != nullptr || !stack.empty(); }

private:
  std::stack<TreeNode *> stack;
  TreeNode *cur;
};
