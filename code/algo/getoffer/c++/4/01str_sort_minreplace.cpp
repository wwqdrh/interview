#include <algorithm>
#include <iostream>
#include <string>

int min(int a, int b) { return (a < b) ? a : b; }

int minFlipsMonoIncr(const std::string &s) {
  int dp0 = 0, dp1 = 0;
  for (char c : s) {
    int dp0New = dp0, dp1New = std::min(dp0, dp1);
    if (c == '1') {
      dp0New++;
    } else {
      dp1New++;
    }
    dp0 = dp0New;
    dp1 = dp1New;
  }
  return std::min(dp0, dp1);
}

int main() {
  std::string s = "00110";
  std::cout << "Minimum flips: " << minFlipsMonoIncr(s) << std::endl;
  return 0;
}
