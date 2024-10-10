#include <algorithm>
#include <functional>
#include <string>
#include <vector>

class Trie {
public:
  Trie *child[26] = {nullptr};
  int depth = 1;

  Trie() = default;

  void Insert(const std::string &word) {
    Trie *curr = this;
    int n = word.size();
    for (int i = n - 1; i >= 0; --i) {
      int c = word[i] - 'a';
      if (curr->child[c] == nullptr) {
        curr->child[c] = new Trie();
      }
      curr->child[c]->depth = curr->depth + 1;
      curr = curr->child[c];
    }
  }
};

int minimumLengthEncoding(std::vector<std::string> &words) {
  Trie *root = new Trie();
  for (const std::string &word : words) {
    root->Insert(word);
  }

  int res = 0;
  std::function<void(Trie *)> dfs = [&](Trie *node) -> void {
    bool hasChild = false;
    for (int i = 0; i < 26; ++i) {
      if (node->child[i] != nullptr) {
        hasChild = true;
        dfs(node->child[i]);
      }
    }
    if (!hasChild) {
      res += node->depth;
    }
  };
  dfs(root);
  return res;
}
