#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int openLock(std::vector<std::string> &deadends, std::string target) {
  if (target == "0000") {
    return 0;
  }

  std::unordered_set<std::string> deadendsSet(deadends.begin(), deadends.end());
  if (deadendsSet.count(target) || deadendsSet.count("0000")) {
    return -1;
  }

  std::unordered_set<std::string> visit;

  auto getnei = [](std::string state) -> std::vector<std::string> {
    std::vector<std::string> res;
    std::string s = state;
    for (int i = 0; i < 4; ++i) {
      char ch = s[i];
      s[i] = ch + 1;
      if (s[i] > '9') {
        s[i] = '0';
      }
      res.push_back(s);

      s[i] = ch - 1;
      if (s[i] < '0') {
        s[i] = '9';
      }
      res.push_back(s);

      s[i] = ch;
    }
    return res;
  };

  std::queue<std::string> queue;
  queue.push("0000");
  int step = 0;
  while (!queue.empty()) {
    int size = queue.size();
    for (int i = 0; i < size; ++i) {
      std::string state = queue.front();
      queue.pop();
      for (const auto &ne : getnei(state)) {
        if (!visit.count(ne) && !deadendsSet.count(ne)) {
          if (ne == target) {
            return step + 1;
          }
          visit.insert(ne);
          queue.push(ne);
        }
      }
    }
    ++step;
  }
  return -1;
}

int main() {
  std::vector<std::string> deadends = {"0201", "0101", "0102", "1212", "2002"};
  std::string target = "0202";
  std::cout << "Minimum turns to open lock: " << openLock(deadends, target)
            << std::endl;
  return 0;
}
