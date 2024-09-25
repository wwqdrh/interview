#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

bool canPartition(std::vector<int> &nums) {
  int n = nums.size();
  if (n < 2) {
    return false;
  }

  int sum = std::accumulate(nums.begin(), nums.end(), 0);
  int maxNum = *std::max_element(nums.begin(), nums.end());
  if (sum % 2 != 0) {
    return false;
  }

  int target = sum / 2;
  if (maxNum > target) {
    return false;
  }

  std::vector<std::vector<bool>> dp(n, std::vector<bool>(target + 1, false));
  for (int i = 0; i < n; ++i) {
    dp[i][0] = true;
  }
  dp[0][nums[0]] = true;
  for (int i = 1; i < n; ++i) {
    int v = nums[i];
    for (int j = 1; j <= target; ++j) {
      if (j >= v) {
        dp[i][j] = dp[i - 1][j] || dp[i - 1][j - v];
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  return dp[n - 1][target];
}

int main() {
  std::vector<int> nums = {1, 5, 11, 5};
  std::cout << "Can partition: " << (canPartition(nums) ? "true" : "false")
            << std::endl;
  return 0;
}
