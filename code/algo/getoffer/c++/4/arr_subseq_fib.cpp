#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

int max(int a, int b) { return (a > b) ? a : b; }

int lenLongestFibSubseq(const std::vector<int> &arr) {
  int n = arr.size();
  std::unordered_map<int, int> indices;
  for (int i = 0; i < n; ++i) {
    indices[arr[i]] = i;
  }
  std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = n - 1; j >= 0 && arr[j] * 2 > arr[i]; --j) {
      auto it = indices.find(arr[i] - arr[j]);
      if (it != indices.end()) {
        int k = it->second;
        dp[j][i] = max(dp[k][j] + 1, 3);
        ans = max(ans, dp[j][i]);
      }
    }
  }
  return ans;
}

int main() {
  std::vector<int> arr = {1, 3, 7, 11, 12, 14, 18};
  std::cout << "Length of longest Fibonacci-like subsequence: "
            << lenLongestFibSubseq(arr) << std::endl;
  return 0;
}
