#include <string>
#include <unordered_map>
#include <vector>

bool isAlienSorted(const std::vector<std::string> &words,
                   const std::string &order) {
  std::vector<int> index(26, 0);
  for (int i = 0; i < order.size(); ++i) {
    index[order[i] - 'a'] = i;
  }

  for (int i = 1; i < words.size(); ++i) {
    const std::string &prev = words[i - 1];
    const std::string &curr = words[i];
    for (int j = 0; j < std::min(prev.size(), curr.size()); ++j) {
      int pre = index[prev[j] - 'a'];
      int cur = index[curr[j] - 'a'];
      if (pre > cur) {
        return false;
      }
      if (pre < cur) {
        goto next_word;
      }
    }
    if (prev.size() > curr.size()) {
      return false;
    }
  next_word:;
  }
  return true;
}
