#include <iostream>
#include <vector>

int find(std::vector<int> &parent, int x) {
  if (parent[x] != x) {
    parent[x] = find(parent, parent[x]);
  }
  return parent[x];
}

bool unionSets(std::vector<int> &parent, int from, int to) {
  int x = find(parent, from);
  int y = find(parent, to);
  if (x == y) {
    return false;
  }
  parent[x] = y;
  return true;
}

std::vector<int>
findRedundantConnection(const std::vector<std::vector<int>> &edges) {
  std::vector<int> parent(edges.size() + 1);
  for (size_t i = 0; i < parent.size(); ++i) {
    parent[i] = i;
  }

  for (const auto &edge : edges) {
    if (!unionSets(parent, edge[0], edge[1])) {
      return edge;
    }
  }
  return {};
}

int main() {
  std::vector<std::vector<int>> edges = {{1, 2}, {1, 3}, {2, 3}};
  std::vector<int> result = findRedundantConnection(edges);
  std::cout << "Redundant connection: [" << result[0] << ", " << result[1]
            << "]" << std::endl;
  return 0;
}
