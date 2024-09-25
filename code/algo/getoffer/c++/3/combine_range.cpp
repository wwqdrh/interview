#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> merge(vector<vector<int>> &intervals) {
  sort(intervals.begin(), intervals.end(),
       [](const vector<int> &a, const vector<int> &b) {
         return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
       });

  vector<vector<int>> res;
  for (const auto &interval : intervals) {
    if (res.empty() || res.back()[1] < interval[0]) {
      res.push_back(interval);
    } else {
      res.back()[1] = max(res.back()[1], interval[1]);
    }
  }
  return res;
}

int max(int a, int b) { return (a > b) ? a : b; }
