#include <cmath>
#include <unordered_map>
#include <vector>

int getID(int x, int w) {
  if (x >= 0) {
    return x / w;
  }
  return (x + 1) / w - 1;
}

bool containsNearbyAlmostDuplicate(const std::vector<int> &nums, int k, int t) {
  std::unordered_map<int, int> mp;
  for (int i = 0; i < nums.size(); ++i) {
    int x = nums[i];
    int id = getID(x, t + 1);
    if (mp.count(id)) {
      return true;
    }
    if (mp.count(id - 1) && std::abs(x - mp[id - 1]) <= t) {
      return true;
    }
    if (mp.count(id + 1) && std::abs(x - mp[id + 1]) <= t) {
      return true;
    }
    mp[id] = x;
    if (i >= k) {
      mp.erase(getID(nums[i - k], t + 1));
    }
  }
  return false;
}

int abs(int x) { return x < 0 ? -x : x; }
