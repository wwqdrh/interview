#include <algorithm>
#include <vector>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  std::vector<int> largestValues(TreeNode *root) {
    std::vector<int> ans;
    dfs(root, 0, ans);
    return ans;
  }

private:
  void dfs(TreeNode *node, int curHeight, std::vector<int> &ans) {
    if (!node) {
      return;
    }
    if (curHeight == ans.size()) {
      ans.push_back(node->val);
    } else {
      ans[curHeight] = std::max(ans[curHeight], node->val);
    }
    dfs(node->left, curHeight + 1, ans);
    dfs(node->right, curHeight + 1, ans);
  }
};

int max(int a, int b) { return b > a ? b : a; }
