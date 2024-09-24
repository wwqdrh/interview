#include <algorithm>
#include <climits>
#include <string>
#include <vector>

int getMinutes(const std::string &t) {
  return (t[0] - '0') * 10 * 60 + (t[1] - '0') * 60 + (t[3] - '0') * 10 +
         (t[4] - '0');
}

int findMinDifference(std::vector<std::string> &timePoints) {
  if (timePoints.size() > 1440) {
    return 0;
  }
  std::sort(timePoints.begin(), timePoints.end());
  int ans = INT_MAX;
  int t0Minutes = getMinutes(timePoints[0]);
  int preMinutes = t0Minutes;
  for (int i = 1; i < timePoints.size(); ++i) {
    int minutes = getMinutes(timePoints[i]);
    ans = std::min(ans,
                   minutes - preMinutes); // Difference between adjacent times
    preMinutes = minutes;
  }
  ans = std::min(ans,
                 t0Minutes + 1440 -
                     preMinutes); // Difference between the first and last time
  return ans;
}

int min(int a, int b) { return a > b ? b : a; }
