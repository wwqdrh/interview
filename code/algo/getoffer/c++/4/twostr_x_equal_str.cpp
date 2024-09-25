#include <iostream>
#include <string>
#include <vector>

bool isInterleave(const std::string &s1, const std::string &s2,
                  const std::string &s3) {
  int n = s1.size(), m = s2.size(), t = s3.size();
  if (n + m != t) {
    return false;
  }
  std::vector<bool> f(m + 1, false);
  f[0] = true;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      int p = i + j - 1;
      if (i > 0) {
        f[j] = f[j] && s1[i - 1] == s3[p];
      }
      if (j > 0) {
        f[j] = f[j] || (f[j - 1] && s2[j - 1] == s3[p]);
      }
    }
  }
  return f[m];
}

int main() {
  std::string s1 = "aabcc";
  std::string s2 = "dbbca";
  std::string s3 = "aadbbcbcac";
  std::cout << "Is interleaving: "
            << (isInterleave(s1, s2, s3) ? "true" : "false") << std::endl;
  return 0;
}
