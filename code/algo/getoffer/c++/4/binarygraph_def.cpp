#include <functional>
#include <iostream>
#include <vector>

const int UNCOLOR = 0, RED = 1, GREEN = 2;

bool isBipartite(const std::vector<std::vector<int>> &graph) {
  int n = graph.size();
  std::vector<int> state(n, UNCOLOR);
  bool valid = true;

  std::function<void(int, int)> dfs = [&](int idx, int color) -> void {
    int necolor = (color == RED) ? GREEN : RED;
    state[idx] = color;

    for (int ne : graph[idx]) {
      if (state[ne] == UNCOLOR) {
        dfs(ne, necolor);
      } else {
        valid = (necolor == state[ne]);
      }

      if (!valid) {
        return;
      }
    }
  };

  for (int i = 0; i < n && valid; ++i) {
    if (state[i] == UNCOLOR) {
      dfs(i, RED);
    }
  }
  return valid;
}

int main() {
  std::vector<std::vector<int>> graph = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
  std::cout << "Is bipartite: " << (isBipartite(graph) ? "true" : "false")
            << std::endl;
  return 0;
}
