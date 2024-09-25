#include <vector>

int searchInsert(const std::vector<int> &nums, int target) {
  int n = nums.size();
  int left = 0, right = n - 1;
  int ans = n;
  while (left <= right) {
    int mid = (right - left) / 2 + left;
    if (target <= nums[mid]) {
      ans = mid;
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  return ans;
}
