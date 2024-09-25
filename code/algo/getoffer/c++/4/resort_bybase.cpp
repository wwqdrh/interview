#include <iostream>
#include <queue>
#include <vector>

bool sequenceReconstruction(const std::vector<int> &nums,
                            const std::vector<std::vector<int>> &sequences) {
  int n = nums.size();
  std::vector<std::vector<int>> g(n + 1);
  std::vector<int> inDeg(n + 1, 0);

  for (const auto &sequence : sequences) {
    for (size_t i = 1; i < sequence.size(); ++i) {
      int x = sequence[i - 1];
      int y = sequence[i];
      g[x].push_back(y);
      inDeg[y]++;
    }
  }

  std::queue<int> q;
  for (int i = 1; i <= n; ++i) {
    if (inDeg[i] == 0) {
      q.push(i);
    }
  }

  while (!q.empty()) {
    if (q.size() > 1) {
      return false;
    }
    int x = q.front();
    q.pop();
    for (int y : g[x]) {
      if (--inDeg[y] == 0) {
        q.push(y);
      }
    }
  }

  return true;
}

int main() {
  std::vector<int> nums = {1, 2, 3};
  std::vector<std::vector<int>> sequences = {{1, 2}, {1, 3}};
  std::cout << "Can reconstruct sequence: "
            << (sequenceReconstruction(nums, sequences) ? "true" : "false")
            << std::endl;
  return 0;
}
