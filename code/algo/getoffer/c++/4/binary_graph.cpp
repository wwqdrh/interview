#include <algorithm>
#include <iostream>
#include <vector>

int minCost(std::vector<std::vector<int>> &costs) {
  std::vector<int> dp = costs[0];
  for (size_t i = 1; i < costs.size(); ++i) {
    std::vector<int> dpNew(3);
    for (int j = 0; j < 3; ++j) {
      dpNew[j] = std::min(dp[(j + 1) % 3], dp[(j + 2) % 3]) + costs[i][j];
    }
    dp = dpNew;
  }
  return std::min({dp[0], dp[1], dp[2]});
}

int main() {
  std::vector<std::vector<int>> costs = {{17, 2, 17}, {16, 16, 5}, {14, 3, 19}};
  std::cout << "Minimum cost: " << minCost(costs) << std::endl;
  return 0;
}
