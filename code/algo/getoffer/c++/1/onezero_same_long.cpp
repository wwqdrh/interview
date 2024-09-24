#include <algorithm>
#include <unordered_map>
#include <vector>

int FindMaxLength(const std::vector<int> &nums) {
  std::unordered_map<int, int> mp = {{0, -1}};
  int maxLength = 0, counter = 0;
  for (int i = 0; i < nums.size(); ++i) {
    counter += (nums[i] == 1) ? 1 : -1;
    if (mp.find(counter) != mp.end()) {
      maxLength = std::max(maxLength, i - mp[counter]);
    } else {
      mp[counter] = i;
    }
  }
  return maxLength;
}
