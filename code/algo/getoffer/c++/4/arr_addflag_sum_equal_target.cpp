#include <iostream>
#include <vector>

void backtrack(const std::vector<int> &nums, int target, int index, int sum,
               int &count) {
  if (index == nums.size()) {
    if (sum == target) {
      count++;
    }
    return;
  }
  backtrack(nums, target, index + 1, sum + nums[index], count);
  backtrack(nums, target, index + 1, sum - nums[index], count);
}

int findTargetSumWays(const std::vector<int> &nums, int target) {
  int count = 0;
  backtrack(nums, target, 0, 0, count);
  return count;
}

int main() {
  std::vector<int> nums = {1, 1, 1, 1, 1};
  int target = 3;
  std::cout << "Number of ways to reach target sum: "
            << findTargetSumWays(nums, target) << std::endl;
  return 0;
}
