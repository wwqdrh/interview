#include <vector>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  std::vector<int> rightSideView(TreeNode *root) {
    std::vector<int> ans;
    if (!root) {
      return ans;
    }
    dfs(root, 0, ans);
    return ans;
  }

private:
  void dfs(TreeNode *node, int depth, std::vector<int> &ans) {
    if (!node) {
      return;
    }
    if (depth == ans.size()) {
      ans.push_back(node->val);
    }
    dfs(node->right, depth + 1, ans);
    dfs(node->left, depth + 1, ans);
  }
};
