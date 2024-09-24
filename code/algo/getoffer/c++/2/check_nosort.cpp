#include <string>
#include <vector>

bool isAnagram(const std::string &s, const std::string &t) {
  if (s == t) {
    return false;
  }
  std::vector<int> c1(26, 0), c2(26, 0);
  for (char ch : s) {
    c1[ch - 'a']++;
  }
  for (char ch : t) {
    c2[ch - 'a']++;
  }
  return c1 == c2;
}
