#include <vector>

std::vector<int> TwoSum(const std::vector<int> &numbers, int target) {
  int low = 0, high = numbers.size() - 1;
  while (low < high) {
    int sum = numbers[low] + numbers[high];
    if (sum == target) {
      return {low, high};
    } else if (sum < target) {
      ++low;
    } else {
      --high;
    }
  }
  return {-1, -1};
}
