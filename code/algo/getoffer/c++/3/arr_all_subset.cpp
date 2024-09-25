#include <vector>

using namespace std;

void dfs(const vector<int> &candidates, int target, int idx, vector<int> &comb,
         vector<vector<int>> &ans) {
  if (idx == candidates.size()) {
    return;
  }
  if (target == 0) {
    ans.push_back(comb);
    return;
  }
  // Skip the current number
  dfs(candidates, target, idx + 1, comb, ans);
  // Choose the current number
  if (target - candidates[idx] >= 0) {
    comb.push_back(candidates[idx]);
    dfs(candidates, target - candidates[idx], idx, comb, ans);
    comb.pop_back();
  }
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
  vector<vector<int>> ans;
  vector<int> comb;
  dfs(candidates, target, 0, comb, ans);
  return ans;
}
