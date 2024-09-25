#include <string>
#include <vector>

class Trie {
public:
  Trie *children[26] = {nullptr};
  bool isEnd = false;
};

class MagicDictionary {
public:
  MagicDictionary() { root = new Trie(); }

  void BuildDict(const std::vector<std::string> &dictionary) {
    for (const std::string &word : dictionary) {
      Trie *node = root;
      for (char ch : word) {
        int idx = ch - 'a';
        if (node->children[idx] == nullptr) {
          node->children[idx] = new Trie();
        }
        node = node->children[idx];
      }
      node->isEnd = true;
    }
  }

  bool Search(const std::string &searchWord) {
    return dfs(root, searchWord, 0, false);
  }

private:
  Trie *root;

  bool dfs(Trie *node, const std::string &word, int index, bool modified) {
    if (index == word.size()) {
      return modified && node->isEnd;
    }
    int c = word[index] - 'a';
    if (node->children[c] != nullptr &&
        dfs(node->children[c], word, index + 1, modified)) {
      return true;
    }
    if (!modified) {
      for (int i = 0; i < 26; ++i) {
        if (i != c && node->children[i] != nullptr &&
            dfs(node->children[i], word, index + 1, true)) {
          return true;
        }
      }
    }
    return false;
  }
};
