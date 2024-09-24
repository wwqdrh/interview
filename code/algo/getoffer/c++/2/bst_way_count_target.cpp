#include <unordered_map>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  int pathSum(TreeNode *root, int targetSum) {
    std::unordered_map<long long, int> preSum;
    preSum[0] = 1;
    return dfs(root, 0, targetSum, preSum);
  }

private:
  int dfs(TreeNode *node, long long curr, int targetSum,
          std::unordered_map<long long, int> &preSum) {
    if (!node) {
      return 0;
    }
    curr += node->val;
    int ans = preSum[curr - targetSum];
    preSum[curr]++;
    ans += dfs(node->left, curr, targetSum, preSum);
    ans += dfs(node->right, curr, targetSum, preSum);
    preSum[curr]--;
    return ans;
  }
};
