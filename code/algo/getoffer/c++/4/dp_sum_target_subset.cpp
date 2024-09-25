#include <iostream>
#include <vector>

int combinationSum4(const std::vector<int> &nums, int target) {
  std::vector<int> dp(target + 1, 0);
  dp[0] = 1;
  for (int i = 1; i <= target; ++i) {
    for (int num : nums) {
      if (num <= i) {
        dp[i] += dp[i - num];
      }
    }
  }
  return dp[target];
}

int main() {
  std::vector<int> nums = {1, 2, 3};
  int target = 4;
  std::cout << "Number of combinations: " << combinationSum4(nums, target)
            << std::endl;
  return 0;
}
