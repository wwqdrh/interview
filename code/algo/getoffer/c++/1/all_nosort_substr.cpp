#include <string>
#include <vector>

std::vector<int> findAnagrams(const std::string &s, const std::string &p) {
  std::vector<int> ans;
  int sLen = s.size(), pLen = p.size();
  if (sLen < pLen)
    return ans;

  std::vector<int> sCount(26, 0), pCount(26, 0);
  for (int i = 0; i < pLen; ++i) {
    sCount[s[i] - 'a']++;
    pCount[p[i] - 'a']++;
  }
  if (sCount == pCount) {
    ans.push_back(0);
  }

  for (int i = 0; i < sLen - pLen; ++i) {
    sCount[s[i] - 'a']--;
    sCount[s[i + pLen] - 'a']++;
    if (sCount == pCount) {
      ans.push_back(i + 1);
    }
  }
  return ans;
}
