#include <algorithm>
#include <vector>

using namespace std;

void dfs(int pos, int rest, const vector<pair<int, int>> &freq,
         vector<int> &sequence, vector<vector<int>> &ans) {
  if (rest == 0) {
    ans.push_back(sequence);
    return;
  }
  if (pos == freq.size() || rest < freq[pos].first) {
    return;
  }

  dfs(pos + 1, rest, freq, sequence, ans);

  int most = min(rest / freq[pos].first, freq[pos].second);
  for (int i = 1; i <= most; ++i) {
    sequence.push_back(freq[pos].first);
    dfs(pos + 1, rest - i * freq[pos].first, freq, sequence, ans);
  }
  sequence.resize(sequence.size() - most);
}

vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
  sort(candidates.begin(), candidates.end());
  vector<pair<int, int>> freq;
  for (int num : candidates) {
    if (freq.empty() || num != freq.back().first) {
      freq.emplace_back(num, 1);
    } else {
      ++freq.back().second;
    }
  }

  vector<vector<int>> ans;
  vector<int> sequence;
  dfs(0, target, freq, sequence, ans);
  return ans;
}

int min(int a, int b) { return (a < b) ? a : b; }
