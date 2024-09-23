#include <vector>

int pivotIndex(const std::vector<int> &nums) {
  int total = 0;
  for (int v : nums) {
    total += v;
  }
  int sum = 0;
  for (int i = 0; i < nums.size(); ++i) {
    if (2 * sum + nums[i] == total) {
      return i;
    }
    sum += nums[i];
  }
  return -1;
}
