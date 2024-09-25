#include <iostream>
#include <queue>
#include <vector>

std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>> &mat) {
  int m = mat.size();
  int n = mat[0].size();
  std::vector<std::vector<int>> res(m, std::vector<int>(n, 0));
  std::vector<int> dx = {1, 0, -1, 0};
  std::vector<int> dy = {0, -1, 0, 1};
  std::queue<std::pair<int, int>> queue;

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (mat[i][j] == 0) {
        queue.push({i, j});
      }
    }
  }

  while (!queue.empty()) {
    int x = queue.front().first;
    int y = queue.front().second;
    queue.pop();
    for (int k = 0; k < 4; ++k) {
      int nx = x + dx[k];
      int ny = y + dy[k];
      if (nx >= 0 && ny >= 0 && nx < m && ny < n && mat[nx][ny] == 1) {
        if (res[nx][ny] == 0 || res[x][y] + 1 < res[nx][ny]) {
          res[nx][ny] = res[x][y] + 1;
          queue.push({nx, ny});
        }
      }
    }
  }

  return res;
}

int main() {
  std::vector<std::vector<int>> mat = {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};
  std::vector<std::vector<int>> result = updateMatrix(mat);
  for (const auto &row : result) {
    for (int val : row) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
