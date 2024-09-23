#include <vector>

class NumMatrix {
public:
  NumMatrix(const std::vector<std::vector<int>> &matrix) {
    int m = matrix.size();
    if (m == 0)
      return;
    int n = matrix[0].size();
    sums.resize(m + 1, std::vector<int>(n + 1, 0));
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        sums[i + 1][j + 1] =
            sums[i + 1][j] + sums[i][j + 1] - sums[i][j] + matrix[i][j];
      }
    }
  }

  int SumRegion(int row1, int col1, int row2, int col2) {
    return sums[row2 + 1][col2 + 1] - sums[row1][col2 + 1] -
           sums[row2 + 1][col1] + sums[row1][col1];
  }

private:
  std::vector<std::vector<int>> sums;
};
