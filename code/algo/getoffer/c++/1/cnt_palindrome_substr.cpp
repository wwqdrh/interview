#include <string>

int countSubstrings(const std::string &s) {
  int n = s.length();
  int ans = 0;
  for (int i = 0; i < 2 * n - 1; ++i) {
    int l = i / 2;
    int r = i / 2 + i % 2;
    while (l >= 0 && r < n && s[l] == s[r]) {
      --l;
      ++r;
      ++ans;
    }
  }
  return ans;
}
