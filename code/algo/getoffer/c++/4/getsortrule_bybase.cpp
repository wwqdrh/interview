#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

std::string alienOrder(const std::vector<std::string> &words) {
  std::unordered_map<char, std::vector<char>> g;
  std::unordered_map<char, int> inDeg;
  for (char c : words[0]) {
    inDeg[c] = 0;
  }

  for (size_t i = 1; i < words.size(); ++i) {
    const std::string &s = words[i - 1];
    const std::string &t = words[i];
    for (char c : t) {
      inDeg[c] += 0;
    }
    for (size_t j = 0; j < s.size() && j < t.size(); ++j) {
      if (s[j] != t[j]) {
        g[s[j]].push_back(t[j]);
        inDeg[t[j]]++;
        break;
      }
    }
    if (s.size() > t.size() && s.substr(0, t.size()) == t) {
      return "";
    }
  }

  std::string order;
  std::queue<char> q;
  for (const auto &[u, d] : inDeg) {
    if (d == 0) {
      q.push(u);
    }
  }

  while (!q.empty()) {
    char u = q.front();
    q.pop();
    order.push_back(u);
    for (char v : g[u]) {
      if (--inDeg[v] == 0) {
        q.push(v);
      }
    }
  }

  if (order.size() != inDeg.size()) {
    return "";
  }
  return order;
}

int main() {
  std::vector<std::string> words = {"wrt", "wrf", "er", "ett", "rftt"};
  std::string result = alienOrder(words);
  std::cout << "Alien dictionary order: " << result << std::endl;
  return 0;
}
