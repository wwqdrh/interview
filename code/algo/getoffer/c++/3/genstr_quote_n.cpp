#include <string>
#include <vector>

using namespace std;

vector<string> generateParenthesis(int n) {
  vector<vector<string>> dp(n + 1);
  dp[0] = {""};
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < i; ++j) {
      for (const string &left : dp[j]) {
        for (const string &right : dp[i - j - 1]) {
          dp[i].push_back("(" + left + ")" + right);
        }
      }
    }
  }
  return dp[n];
}

void dfs(int n, int leftCnt, int rightCnt, string &tmp, vector<string> &res) {
  if (tmp.size() == n * 2) {
    res.push_back(tmp);
    return;
  }
  if (leftCnt < n) {
    tmp.push_back('(');
    dfs(n, leftCnt + 1, rightCnt, tmp, res);
    tmp.pop_back();
  }
  if (leftCnt > rightCnt) {
    tmp.push_back(')');
    dfs(n, leftCnt, rightCnt + 1, tmp, res);
    tmp.pop_back();
  }
}

vector<string> generateParenthesisDFS(int n) {
  vector<string> res;
  string tmp;
  dfs(n, 0, 0, tmp, res);
  return res;
}