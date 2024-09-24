struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p) {
    TreeNode *successor = nullptr;
    if (p->right) {
      successor = p->right;
      while (successor->left) {
        successor = successor->left;
      }
      return successor;
    }
    TreeNode *node = root;
    while (node) {
      if (node->val > p->val) {
        successor = node;
        node = node->left;
      } else {
        node = node->right;
      }
    }
    return successor;
  }
};
