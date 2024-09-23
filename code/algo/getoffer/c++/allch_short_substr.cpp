#include <climits>
#include <string>
#include <unordered_map>

std::string minWindow(const std::string &s, const std::string &t) {
  std::unordered_map<char, int> ori, cnt;
  for (char c : t) {
    ori[c]++;
  }

  int sLen = s.length();
  int minLen = INT_MAX;
  int ansL = -1, ansR = -1;

  auto check = [&]() -> bool {
    for (const auto &[k, v] : ori) {
      if (cnt[k] < v) {
        return false;
      }
    }
    return true;
  };

  for (int l = 0, r = 0; r < sLen; ++r) {
    if (ori.find(s[r]) != ori.end()) {
      cnt[s[r]]++;
    }
    while (check() && l <= r) {
      if (r - l + 1 < minLen) {
        minLen = r - l + 1;
        ansL = l;
        ansR = l + minLen;
      }
      if (ori.find(s[l]) != ori.end()) {
        cnt[s[l]]--;
      }
      ++l;
    }
  }

  if (ansL == -1) {
    return "";
  }
  return s.substr(ansL, ansR - ansL);
}
