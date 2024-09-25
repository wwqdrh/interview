#include <iostream>
#include <string>
#include <vector>

class UnionFind {
public:
  UnionFind(int n) : parent(n), size(n, 1), setCount(n) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  void unionSets(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy)
      return;
    if (size[fx] < size[fy])
      std::swap(fx, fy);
    size[fx] += size[fy];
    parent[fy] = fx;
    --setCount;
  }

  bool inSameSet(int x, int y) { return find(x) == find(y); }

  int getSetCount() const { return setCount; }

private:
  std::vector<int> parent;
  std::vector<int> size;
  int setCount;
};

bool isSimilar(const std::string &s, const std::string &t) {
  int diff = 0;
  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] != t[i]) {
      ++diff;
      if (diff > 2) {
        return false;
      }
    }
  }
  return true;
}

int numSimilarGroups(const std::vector<std::string> &strs) {
  int n = strs.size();
  UnionFind uf(n);
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (!uf.inSameSet(i, j) && isSimilar(strs[i], strs[j])) {
        uf.unionSets(i, j);
      }
    }
  }
  return uf.getSetCount();
}

int main() {
  std::vector<std::string> strs = {"tars", "rats", "arts", "star"};
  std::cout << "Number of similar groups: " << numSimilarGroups(strs)
            << std::endl;
  return 0;
}
