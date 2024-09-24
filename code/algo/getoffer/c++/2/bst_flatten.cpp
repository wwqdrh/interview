struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  TreeNode *increasingBST(TreeNode *root) {
    TreeNode *dummyNode = new TreeNode(0);
    TreeNode *resNode = dummyNode;

    inorder(root, resNode);

    return dummyNode->right;
  }

private:
  void inorder(TreeNode *node, TreeNode *&resNode) {
    if (!node) {
      return;
    }
    inorder(node->left, resNode);

    // Modify the node pointers during in-order traversal
    resNode->right = node;
    node->left = nullptr;
    resNode = node;

    inorder(node->right, resNode);
  }
};
