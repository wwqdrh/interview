#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

int min(int a, int b) { return (a < b) ? a : b; }

int coinChange(const std::vector<int> &nums, int target) {
  std::vector<int> dp(target + 1, INT_MAX);
  dp[0] = 0;
  for (int num : nums) {
    for (int i = 0; i <= target - num; ++i) {
      if (dp[i] == INT_MAX) {
        continue;
      }
      dp[i + num] = min(dp[i + num], dp[i] + 1);
    }
  }
  return dp[target] == INT_MAX ? -1 : dp[target];
}

int main() {
  std::vector<int> nums = {1, 2, 5};
  int target = 11;
  std::cout << "Minimum coins needed: " << coinChange(nums, target)
            << std::endl;
  return 0;
}
