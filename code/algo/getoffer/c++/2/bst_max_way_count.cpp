#include <algorithm>
#include <climits>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  int maxPathSum(TreeNode *root) {
    maxSum = INT_MIN;
    maxGain(root);
    return maxSum;
  }

private:
  int maxSum;

  int maxGain(TreeNode *node) {
    if (!node) {
      return 0;
    }

    // Recursively calculate the maximum contribution of the left and right
    // subtrees Only consider positive contributions
    int leftGain = std::max(maxGain(node->left), 0);
    int rightGain = std::max(maxGain(node->right), 0);

    // The price to start a new path where `node` is the highest node
    int priceNewPath = node->val + leftGain + rightGain;

    // Update the maximum sum if the new path is better
    maxSum = std::max(maxSum, priceNewPath);

    // Return the maximum gain if continuing the same path
    return node->val + std::max(leftGain, rightGain);
  }
};
