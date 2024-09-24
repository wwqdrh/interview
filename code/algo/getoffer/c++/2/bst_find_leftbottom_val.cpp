#include <algorithm>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  int findBottomLeftValue(TreeNode *root) {
    int curVal = 0;
    int curHeight = 0;
    dfs(root, 0, curHeight, curVal);
    return curVal;
  }

private:
  void dfs(TreeNode *node, int height, int &curHeight, int &curVal) {
    if (!node) {
      return;
    }
    height++;
    dfs(node->left, height, curHeight, curVal);
    dfs(node->right, height, curHeight, curVal);
    if (height > curHeight) {
      curHeight = height;
      curVal = node->val;
    }
  }
};
