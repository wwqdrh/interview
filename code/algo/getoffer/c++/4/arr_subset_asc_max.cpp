#include <iostream>
#include <unordered_set>
#include <vector>

int longestConsecutive(const std::vector<int> &nums) {
  std::unordered_set<int> numSet(nums.begin(), nums.end());
  int longestStreak = 0;

  for (int num : numSet) {
    if (numSet.find(num - 1) == numSet.end()) {
      int currentNum = num;
      int currentStreak = 1;

      while (numSet.find(currentNum + 1) != numSet.end()) {
        currentNum++;
        currentStreak++;
      }

      longestStreak = std::max(longestStreak, currentStreak);
    }
  }

  return longestStreak;
}

int main() {
  std::vector<int> nums = {100, 4, 200, 1, 3, 2};
  std::cout << "Longest consecutive sequence length: "
            << longestConsecutive(nums) << std::endl;
  return 0;
}
