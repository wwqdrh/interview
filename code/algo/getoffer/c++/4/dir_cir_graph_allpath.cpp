#include <iostream>
#include <vector>

void dfs(const std::vector<std::vector<int>> &graph, std::vector<int> &stk,
         std::vector<std::vector<int>> &ans, int x) {
  if (x == graph.size() - 1) {
    ans.push_back(stk);
    return;
  }
  for (int y : graph[x]) {
    stk.push_back(y);
    dfs(graph, stk, ans, y);
    stk.pop_back();
  }
}

std::vector<std::vector<int>>
allPathsSourceTarget(const std::vector<std::vector<int>> &graph) {
  std::vector<std::vector<int>> ans;
  std::vector<int> stk = {0};
  dfs(graph, stk, ans, 0);
  return ans;
}

int main() {
  std::vector<std::vector<int>> graph = {{1, 2}, {3}, {3}, {}};
  std::vector<std::vector<int>> result = allPathsSourceTarget(graph);
  for (const auto &path : result) {
    for (int node : path) {
      std::cout << node << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
