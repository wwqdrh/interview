#include <functional>
#include <queue>
#include <vector>

class KthLargest {
public:
  KthLargest(int k, std::vector<int> &nums) : k(k) {
    for (int val : nums) {
      add(val);
    }
  }

  int add(int val) {
    if (minHeap.size() < k) {
      minHeap.push(val);
    } else if (val > minHeap.top()) {
      minHeap.push(val);
      if (minHeap.size() > k) {
        minHeap.pop();
      }
    }
    return minHeap.top();
  }

private:
  int k;
  std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
};
