#include <functional>
#include <string>
#include <vector>

using namespace std;

vector<vector<string>> partition(string s) {
  int n = s.size();
  vector<vector<bool>> f(n, vector<bool>(n, true));
  for (int i = n - 1; i >= 0; --i) {
    for (int j = i + 1; j < n; ++j) {
      f[i][j] = (s[i] == s[j]) && f[i + 1][j - 1];
    }
  }

  vector<vector<string>> ans;
  vector<string> splits;
  function<void(int)> dfs = [&](int i) {
    if (i == n) {
      ans.push_back(splits);
      return;
    }
    for (int j = i; j < n; ++j) {
      if (f[i][j]) {
        splits.push_back(s.substr(i, j - i + 1));
        dfs(j + 1);
        splits.pop_back();
      }
    };
  };
  dfs(0);
  return ans;
}
