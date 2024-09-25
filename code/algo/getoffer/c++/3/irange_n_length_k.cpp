#include <vector>

using namespace std;

void dfs(int cur, int n, int k, vector<int> &temp, vector<vector<int>> &ans) {
  // Pruning: if the remaining elements plus the current temp size is less than
  // k, return
  if (temp.size() + (n - cur + 1) < k) {
    return;
  }
  // Record valid answers
  if (temp.size() == k) {
    ans.push_back(temp);
    return;
  }
  // Consider the current position
  temp.push_back(cur);
  dfs(cur + 1, n, k, temp, ans);
  temp.pop_back();
  // Consider not choosing the current position
  dfs(cur + 1, n, k, temp, ans);
}

vector<vector<int>> combine(int n, int k) {
  vector<vector<int>> ans;
  vector<int> temp;
  dfs(1, n, k, temp, ans);
  return ans;
}
