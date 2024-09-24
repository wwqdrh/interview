struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  int sumNumbers(TreeNode *root) { return dfs(root, 0); }

private:
  int dfs(TreeNode *node, int prevSum) {
    if (!node) {
      return 0;
    }
    int sum = prevSum * 10 + node->val;
    if (!node->left && !node->right) {
      return sum;
    }
    return dfs(node->left, sum) + dfs(node->right, sum);
  }
};
