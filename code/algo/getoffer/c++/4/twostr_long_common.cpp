#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int max(int a, int b) { return (a > b) ? a : b; }

int longestCommonSubsequence(const std::string &text1,
                             const std::string &text2) {
  int m = text1.size(), n = text2.size();
  std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (text1[i] == text2[j]) {
        dp[i + 1][j + 1] = dp[i][j] + 1;
      } else {
        dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
      }
    }
  }
  return dp[m][n];
}

int main() {
  std::string text1 = "abcde";
  std::string text2 = "ace";
  std::cout << "Length of longest common subsequence: "
            << longestCommonSubsequence(text1, text2) << std::endl;
  return 0;
}
