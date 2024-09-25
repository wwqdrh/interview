#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>

int minCut(const std::string &s) {
  int n = s.size();
  std::vector<std::vector<bool>> g(n, std::vector<bool>(n, true));
  for (int i = n - 1; i >= 0; --i) {
    for (int j = i + 1; j < n; ++j) {
      g[i][j] = (s[i] == s[j]) && g[i + 1][j - 1];
    }
  }

  std::vector<int> f(n, INT_MAX);
  for (int i = 0; i < n; ++i) {
    if (g[0][i]) {
      f[i] = 0;
    } else {
      for (int j = 0; j < i; ++j) {
        if (g[j + 1][i]) {
          f[i] = std::min(f[i], f[j] + 1);
        }
      }
    }
  }
  return f[n - 1];
}

int main() {
  std::string s = "aab";
  std::cout << "Minimum cuts needed for a palindrome partitioning: "
            << minCut(s) << std::endl;
  return 0;
}
