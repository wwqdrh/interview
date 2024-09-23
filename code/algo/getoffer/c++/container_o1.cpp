#include <cstdlib>
#include <unordered_map>
#include <vector>

class RandomizedSet {
public:
  RandomizedSet() {}

  bool insert(int val) {
    if (indices.find(val) != indices.end()) {
      return false;
    }
    indices[val] = nums.size();
    nums.push_back(val);
    return true;
  }

  bool remove(int val) {
    auto it = indices.find(val);
    if (it == indices.end()) {
      return false;
    }
    int last = nums.back();
    nums[it->second] = last;
    indices[last] = it->second;
    nums.pop_back();
    indices.erase(val);
    return true;
  }

  int getRandom() {
    int randomIndex = rand() % nums.size();
    return nums[randomIndex];
  }

private:
  std::vector<int> nums;
  std::unordered_map<int, int> indices;
};
