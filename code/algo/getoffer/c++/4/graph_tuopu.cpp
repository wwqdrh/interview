#include <iostream>
#include <queue>
#include <vector>

std::vector<int> findOrder(int numCourses,
                           std::vector<std::vector<int>> &prerequisites) {
  std::vector<std::vector<int>> edges(numCourses);
  std::vector<int> indeg(numCourses, 0);
  std::vector<int> result;

  for (const auto &info : prerequisites) {
    edges[info[1]].push_back(info[0]);
    indeg[info[0]]++;
  }

  std::queue<int> q;
  for (int i = 0; i < numCourses; ++i) {
    if (indeg[i] == 0) {
      q.push(i);
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    result.push_back(u);
    for (int v : edges[u]) {
      indeg[v]--;
      if (indeg[v] == 0) {
        q.push(v);
      }
    }
  }

  if (result.size() != numCourses) {
    return {};
  }
  return result;
}

int main() {
  int numCourses = 4;
  std::vector<std::vector<int>> prerequisites = {
      {1, 0}, {2, 0}, {3, 1}, {3, 2}};
  std::vector<int> order = findOrder(numCourses, prerequisites);
  for (int course : order) {
    std::cout << course << " ";
  }
  std::cout << std::endl;
  return 0;
}
