#include <algorithm>
#include <cctype>
#include <string>

bool isalnum(char ch) {
  return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||
         (ch >= '0' && ch <= '9');
}

bool isPalindrome(const std::string &s) {
  std::string sgood;
  for (char ch : s) {
    if (isalnum(ch)) {
      sgood += std::tolower(ch);
    }
  }

  int n = sgood.length();
  for (int i = 0; i < n / 2; ++i) {
    if (sgood[i] != sgood[n - 1 - i]) {
      return false;
    }
  }
  return true;
}
