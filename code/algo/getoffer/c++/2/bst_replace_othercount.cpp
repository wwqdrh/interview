struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  TreeNode *convertBST(TreeNode *root) {
    int sum = 0;
    dfs(root, sum);
    return root;
  }

private:
  void dfs(TreeNode *node, int &sum) {
    if (node != nullptr) {
      dfs(node->right, sum);
      sum += node->val;
      node->val = sum;
      dfs(node->left, sum);
    }
  }
};
