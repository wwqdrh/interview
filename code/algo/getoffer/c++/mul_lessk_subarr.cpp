#include <vector>

int numSubarrayProductLessThanK(const std::vector<int> &nums, int k) {
  if (k <= 1)
    return 0;
  int prod = 1, ans = 0, i = 0;
  for (int j = 0; j < nums.size(); ++j) {
    prod *= nums[j];
    while (prod >= k) {
      prod /= nums[i++];
    }
    ans += j - i + 1;
  }
  return ans;
}
