#include <algorithm>
#include <iostream>
#include <vector>

int min(int x, int y) { return (x < y) ? x : y; }

int minPathSum(const std::vector<std::vector<int>> &grid) {
  if (grid.empty() || grid[0].empty()) {
    return 0;
  }
  int rows = grid.size(), columns = grid[0].size();
  std::vector<std::vector<int>> dp(rows, std::vector<int>(columns, 0));
  dp[0][0] = grid[0][0];
  for (int i = 1; i < rows; ++i) {
    dp[i][0] = dp[i - 1][0] + grid[i][0];
  }
  for (int j = 1; j < columns; ++j) {
    dp[0][j] = dp[0][j - 1] + grid[0][j];
  }
  for (int i = 1; i < rows; ++i) {
    for (int j = 1; j < columns; ++j) {
      dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
    }
  }
  return dp[rows - 1][columns - 1];
}

int main() {
  std::vector<std::vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
  std::cout << "Minimum path sum: " << minPathSum(grid) << std::endl;
  return 0;
}
