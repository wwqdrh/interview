#include <algorithm>
#include <vector>

using namespace std;

int minCostClimbingStairs(vector<int> &cost) {
  int n = cost.size();
  int pre = 0, cur = 0;
  for (int i = 2; i <= n; ++i) {
    int newCur = min(cur + cost[i - 1], pre + cost[i - 2]);
    pre = cur;
    cur = newCur;
  }
  return cur;
}
