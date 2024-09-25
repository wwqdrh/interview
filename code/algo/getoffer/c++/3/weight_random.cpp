#include <algorithm>
#include <cstdlib>
#include <vector>

class Solution {
public:
  Solution(std::vector<int> &w) {
    for (int i = 1; i < w.size(); ++i) {
      w[i] += w[i - 1];
    }
    pre = w;
  }

  int PickIndex() {
    int x = rand() % pre.back() + 1;
    return std::lower_bound(pre.begin(), pre.end(), x) - pre.begin();
  }

private:
  std::vector<int> pre;
};
