#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

int min(int x, int y) { return (x < y) ? x : y; }

int minimumTotal(const std::vector<std::vector<int>> &triangle) {
  int n = triangle.size();
  std::vector<std::vector<int>> f(n, std::vector<int>(n, 0));
  f[0][0] = triangle[0][0];
  for (int i = 1; i < n; ++i) {
    f[i][0] = f[i - 1][0] + triangle[i][0];
    for (int j = 1; j < i; ++j) {
      f[i][j] = min(f[i - 1][j - 1], f[i - 1][j]) + triangle[i][j];
    }
    f[i][i] = f[i - 1][i - 1] + triangle[i][i];
  }
  int ans = INT_MAX;
  for (int i = 0; i < n; ++i) {
    ans = min(ans, f[n - 1][i]);
  }
  return ans;
}

int main() {
  std::vector<std::vector<int>> triangle = {
      {2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
  std::cout << "Minimum total path sum: " << minimumTotal(triangle)
            << std::endl;
  return 0;
}
