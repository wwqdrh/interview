#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

class IHeap {
public:
  bool operator()(const std::pair<int, int> &a, const std::pair<int, int> &b) {
    return a.second > b.second;
  }
};

std::vector<int> topKFrequent(std::vector<int> &nums, int k) {
  std::unordered_map<int, int> occurrences;
  for (int num : nums) {
    occurrences[num]++;
  }

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      IHeap>
      h;
  for (const auto &[key, value] : occurrences) {
    h.emplace(key, value);
    if (h.size() > k) {
      h.pop();
    }
  }

  std::vector<int> ret(k);
  for (int i = k - 1; i >= 0; --i) {
    ret[i] = h.top().first;
    h.pop();
  }

  return ret;
}
