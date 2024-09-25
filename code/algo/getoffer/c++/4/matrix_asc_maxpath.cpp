#include <iostream>
#include <queue>
#include <vector>

std::vector<std::pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int rows, columns;

int longestIncreasingPath(std::vector<std::vector<int>> &matrix) {
  if (matrix.empty() || matrix[0].empty()) {
    return 0;
  }
  rows = matrix.size();
  columns = matrix[0].size();
  std::vector<std::vector<int>> outdegrees(rows, std::vector<int>(columns, 0));

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      for (const auto &dir : dirs) {
        int newRow = i + dir.first;
        int newColumn = j + dir.second;
        if (newRow >= 0 && newRow < rows && newColumn >= 0 &&
            newColumn < columns && matrix[newRow][newColumn] > matrix[i][j]) {
          outdegrees[i][j]++;
        }
      }
    }
  }

  std::queue<std::pair<int, int>> queue;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      if (outdegrees[i][j] == 0) {
        queue.push({i, j});
      }
    }
  }

  int ans = 0;
  while (!queue.empty()) {
    ans++;
    int size = queue.size();
    for (int i = 0; i < size; ++i) {
      auto cell = queue.front();
      queue.pop();
      int row = cell.first;
      int column = cell.second;
      for (const auto &dir : dirs) {
        int newRow = row + dir.first;
        int newColumn = column + dir.second;
        if (newRow >= 0 && newRow < rows && newColumn >= 0 &&
            newColumn < columns &&
            matrix[newRow][newColumn] < matrix[row][column]) {
          outdegrees[newRow][newColumn]--;
          if (outdegrees[newRow][newColumn] == 0) {
            queue.push({newRow, newColumn});
          }
        }
      }
    }
  }
  return ans;
}

int main() {
  std::vector<std::vector<int>> matrix = {{9, 9, 4}, {6, 6, 8}, {2, 1, 1}};
  std::cout << "Longest increasing path: " << longestIncreasingPath(matrix)
            << std::endl;
  return 0;
}
