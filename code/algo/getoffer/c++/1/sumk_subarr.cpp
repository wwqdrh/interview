#include <unordered_map>
#include <vector>

int subarraySum(const std::vector<int> &nums, int k) {
  int count = 0, pre = 0;
  std::unordered_map<int, int> m;
  m[0] = 1;
  for (int i = 0; i < nums.size(); ++i) {
    pre += nums[i];
    if (m.find(pre - k) != m.end()) {
      count += m[pre - k];
    }
    m[pre]++;
  }
  return count;
}
