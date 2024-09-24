#include <queue>
#include <vector>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class CBTInserter {
public:
  CBTInserter(TreeNode *root) : root(root) {
    std::queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
      TreeNode *node = q.front();
      q.pop();
      if (node->left) {
        q.push(node->left);
      }
      if (node->right) {
        q.push(node->right);
      }
      if (!node->left || !node->right) {
        candidate.push_back(node);
      }
    }
  }

  int insert(int val) {
    TreeNode *child = new TreeNode(val);
    TreeNode *node = candidate.front();
    if (!node->left) {
      node->left = child;
    } else {
      node->right = child;
      candidate.erase(candidate.begin());
    }
    candidate.push_back(child);
    return node->val;
  }

  TreeNode *get_root() { return root; }

private:
  TreeNode *root;
  std::vector<TreeNode *> candidate;
};
