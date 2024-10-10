#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int maximalRectangle(vector<string> &matrix) {
  if (matrix.empty()) {
    return 0;
  }
  int m = matrix.size(), n = matrix[0].size();
  vector<vector<int>> left(m, vector<int>(n, 0));
  int ans = 0;

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (matrix[i][j] == '0') {
        continue;
      }
      if (j == 0) {
        left[i][j] = 1;
      } else {
        left[i][j] = left[i][j - 1] + 1;
      }
    }
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (matrix[i][j] == '0') {
        continue;
      }
      int width = left[i][j];
      int area = width;
      for (int k = i - 1; k >= 0; --k) {
        width = min(width, left[k][j]);
        if (width == 0) {
          break;
        }
        area = max(area, (i - k + 1) * width);
      }
      ans = max(ans, area);
    }
  }

  return ans;
}
