#include <algorithm>
#include <string>
#include <unordered_map>

int lengthOfLongestSubstring(const std::string &s) {
  std::unordered_map<char, int> m;
  int n = s.length();
  int rk = -1, ans = 0;

  for (int i = 0; i < n; ++i) {
    if (i != 0) {
      m.erase(s[i - 1]);
    }
    while (rk + 1 < n && m[s[rk + 1]] == 0) {
      m[s[++rk]]++;
    }
    ans = std::max(ans, rk - i + 1);
  }

  return ans;
}
