#include <algorithm>
#include <vector>

using namespace std;

int _rob(const vector<int> &nums) {
  int first = nums[0], second = max(nums[0], nums[1]);
  for (int i = 2; i < nums.size(); ++i) {
    int v = nums[i];
    int newSecond = max(first + v, second);
    first = second;
    second = newSecond;
  }
  return second;
}

int rob(vector<int> &nums) {
  int n = nums.size();
  if (n == 1) {
    return nums[0];
  }
  if (n == 2) {
    return max(nums[0], nums[1]);
  }
  vector<int> nums1(nums.begin(), nums.end() - 1);
  vector<int> nums2(nums.begin() + 1, nums.end());
  return max(_rob(nums1), _rob(nums2));
}

int max(int a, int b) { return (a > b) ? a : b; }
