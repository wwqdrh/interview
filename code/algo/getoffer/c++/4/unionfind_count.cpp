#include <iostream>
#include <vector>

int find(std::vector<int> &parent, int x) {
  if (parent[x] != x) {
    parent[x] = find(parent, parent[x]);
  }
  return parent[x];
}

void unionSets(std::vector<int> &parent, int from, int to) {
  parent[find(parent, from)] = find(parent, to);
}

int findCircleNum(const std::vector<std::vector<int>> &isConnected) {
  int n = isConnected.size();
  std::vector<int> parent(n);
  for (int i = 0; i < n; ++i) {
    parent[i] = i;
  }

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (isConnected[i][j] == 1) {
        unionSets(parent, i, j);
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (parent[i] == i) {
      ++ans;
    }
  }
  return ans;
}

int main() {
  std::vector<std::vector<int>> isConnected = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
  std::cout << "Number of provinces: " << findCircleNum(isConnected)
            << std::endl;
  return 0;
}
