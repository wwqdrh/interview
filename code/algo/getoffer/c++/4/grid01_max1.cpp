#include <iostream>
#include <vector>

int getArea(std::vector<std::vector<int>> &grid,
            std::vector<std::vector<bool>> &visited, int i, int j) {
  int m = grid.size(), n = grid[0].size();
  if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0 || visited[i][j]) {
    return 0;
  }
  visited[i][j] = true;
  return getArea(grid, visited, i - 1, j) + getArea(grid, visited, i + 1, j) +
         getArea(grid, visited, i, j - 1) + getArea(grid, visited, i, j + 1) +
         1;
}

int maxAreaOfIsland(std::vector<std::vector<int>> &grid) {
  int m = grid.size(), n = grid[0].size();
  std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
  int ans = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      int area = getArea(grid, visited, i, j);
      if (area > ans) {
        ans = area;
      }
    }
  }
  return ans;
}

int main() {
  std::vector<std::vector<int>> grid = {
      {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
      {0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};
  std::cout << "Maximum area of island: " << maxAreaOfIsland(grid) << std::endl;
  return 0;
}
