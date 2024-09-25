#include <algorithm>
#include <vector>

using namespace std;

void backtrack(vector<int> &nums, vector<bool> &vis, vector<int> &perm,
               vector<vector<int>> &ans, int idx) {
  if (idx == nums.size()) {
    ans.push_back(perm);
    return;
  }
  for (int i = 0; i < nums.size(); ++i) {
    if (vis[i] || (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1])) {
      continue;
    }
    perm.push_back(nums[i]);
    vis[i] = true;
    backtrack(nums, vis, perm, ans, idx + 1);
    vis[i] = false;
    perm.pop_back();
  }
}

vector<vector<int>> permuteUnique(vector<int> &nums) {
  sort(nums.begin(), nums.end());
  vector<vector<int>> ans;
  vector<int> perm;
  vector<bool> vis(nums.size(), false);
  backtrack(nums, vis, perm, ans, 0);
  return ans;
}
