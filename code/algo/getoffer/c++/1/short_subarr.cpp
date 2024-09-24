#include <algorithm>
#include <climits>
#include <vector>

int minSubArrayLen(int s, const std::vector<int> &nums) {
  int n = nums.size();
  if (n == 0) {
    return 0;
  }
  int ans = INT_MAX;
  int start = 0, end = 0, sum = 0;
  while (end < n) {
    sum += nums[end];
    while (sum >= s) {
      ans = std::min(ans, end - start + 1);
      sum -= nums[start];
      ++start;
    }
    ++end;
  }
  return (ans == INT_MAX) ? 0 : ans;
}
