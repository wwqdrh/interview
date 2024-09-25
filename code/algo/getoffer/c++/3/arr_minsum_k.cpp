#include <queue>
#include <tuple>
#include <vector>

using namespace std;

vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2,
                                   int k) {
  vector<vector<int>> ans;
  auto comp = [](const pair<int, int> &a, const pair<int, int> &b) {
    return a.first + a.second > b.first + b.second;
  };

  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)>
      minHeap(comp);

  int m = nums1.size(), n = nums2.size();
  for (int i = 0; i < k && i < m; ++i) {
    minHeap.emplace(i, 0);
  }

  while (!minHeap.empty() && ans.size() < k) {
    auto [i, j] = minHeap.top();
    minHeap.pop();
    ans.push_back({nums1[i], nums2[j]});
    if (j + 1 < n) {
      minHeap.emplace(i, j + 1);
    }
  }

  return ans;
}
