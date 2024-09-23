#include <string>
#include <vector>

bool checkInclusion(const std::string &s1, const std::string &s2) {
  int n = s1.size(), m = s2.size();
  if (n > m)
    return false;

  std::vector<int> cnt(26, 0);
  for (char ch : s1) {
    cnt[ch - 'a']--;
  }

  int left = 0;
  for (int right = 0; right < m; ++right) {
    int x = s2[right] - 'a';
    cnt[x]++;
    while (cnt[x] > 0) {
      cnt[s2[left] - 'a']--;
      left++;
    }
    if (right - left + 1 == n) {
      return true;
    }
  }
  return false;
}
