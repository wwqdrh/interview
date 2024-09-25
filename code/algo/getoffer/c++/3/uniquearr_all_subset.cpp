#include <vector>

using namespace std;

void dfs(vector<int> &nums, vector<bool> &vis, vector<int> &path,
         vector<vector<int>> &ans) {
  if (path.size() == nums.size()) {
    ans.push_back(path);
    return;
  }
  for (int i = 0; i < nums.size(); ++i) {
    if (!vis[i]) {
      vis[i] = true;
      path.push_back(nums[i]);
      dfs(nums, vis, path, ans);
      vis[i] = false;
      path.pop_back();
    }
  }
}

vector<vector<int>> permute(vector<int> &nums) {
  vector<vector<int>> ans;
  vector<int> path;
  vector<bool> vis(nums.size(), false);
  dfs(nums, vis, path, ans);
  return ans;
}
