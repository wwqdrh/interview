#include <iostream>
#include <string>
#include <vector>

int numDistinct(const std::string &s, const std::string &t) {
  int m = s.size(), n = t.size();
  if (m < n) {
    return 0;
  }
  std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
  for (int i = 0; i <= m; ++i) {
    dp[i][n] = 1;
  }
  for (int i = m - 1; i >= 0; --i) {
    for (int j = n - 1; j >= 0; --j) {
      if (s[i] == t[j]) {
        dp[i][j] = dp[i + 1][j + 1] + dp[i + 1][j];
      } else {
        dp[i][j] = dp[i + 1][j];
      }
    }
  }
  return dp[0][0];
}

int main() {
  std::string s = "rabbbit";
  std::string t = "rabbit";
  std::cout << "Number of distinct subsequences: " << numDistinct(s, t)
            << std::endl;
  return 0;
}
