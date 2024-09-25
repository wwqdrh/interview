#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

struct Edge {
  int to;
  double weight;
};

std::vector<double>
calcEquation(const std::vector<std::vector<std::string>> &equations,
             const std::vector<double> &values,
             const std::vector<std::vector<std::string>> &queries) {
  std::unordered_map<std::string, int> id;
  int idCounter = 0;

  for (const auto &eq : equations) {
    const std::string &a = eq[0];
    const std::string &b = eq[1];
    if (id.find(a) == id.end()) {
      id[a] = idCounter++;
    }
    if (id.find(b) == id.end()) {
      id[b] = idCounter++;
    }
  }

  std::vector<std::vector<Edge>> graph(idCounter);
  for (size_t i = 0; i < equations.size(); ++i) {
    int v = id[equations[i][0]];
    int w = id[equations[i][1]];
    graph[v].push_back({w, values[i]});
    graph[w].push_back({v, 1.0 / values[i]});
  }

  auto bfs = [&](int start, int end) -> double {
    std::vector<double> ratios(idCounter, 0.0);
    ratios[start] = 1.0;
    std::queue<int> queue;
    queue.push(start);

    while (!queue.empty()) {
      int v = queue.front();
      queue.pop();
      if (v == end) {
        return ratios[v];
      }
      for (const auto &e : graph[v]) {
        if (ratios[e.to] == 0.0) {
          ratios[e.to] = ratios[v] * e.weight;
          queue.push(e.to);
        }
      }
    }
    return -1.0;
  };

  std::vector<double> ans(queries.size());
  for (size_t i = 0; i < queries.size(); ++i) {
    const std::string &startStr = queries[i][0];
    const std::string &endStr = queries[i][1];
    if (id.find(startStr) == id.end() || id.find(endStr) == id.end()) {
      ans[i] = -1.0;
    } else {
      ans[i] = bfs(id[startStr], id[endStr]);
    }
  }
  return ans;
}

int main() {
  std::vector<std::vector<std::string>> equations = {{"a", "b"}, {"b", "c"}};
  std::vector<double> values = {2.0, 3.0};
  std::vector<std::vector<std::string>> queries = {
      {"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
  std::vector<double> result = calcEquation(equations, values, queries);
  for (double val : result) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
  return 0;
}
