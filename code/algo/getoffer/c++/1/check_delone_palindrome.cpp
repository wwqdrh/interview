#include <string>

bool validPalindrome(const std::string &s) {
  int low = 0, high = s.length() - 1;
  while (low < high) {
    if (s[low] == s[high]) {
      ++low;
      --high;
    } else {
      bool flag1 = true, flag2 = true;
      for (int i = low, j = high - 1; i < j; ++i, --j) {
        if (s[i] != s[j]) {
          flag1 = false;
          break;
        }
      }
      for (int i = low + 1, j = high; i < j; ++i, --j) {
        if (s[i] != s[j]) {
          flag2 = false;
          break;
        }
      }
      return flag1 || flag2;
    }
  }
  return true;
}
