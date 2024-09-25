#include <string>
#include <vector>

class Trie {
public:
  Trie() : children(26, nullptr), isEnd(false) {}

  void Insert(const std::string &word) {
    Trie *node = this;
    for (char ch : word) {
      ch -= 'a';
      if (node->children[ch] == nullptr) {
        node->children[ch] = new Trie();
      }
      node = node->children[ch];
    }
    node->isEnd = true;
  }

  bool Search(const std::string &word) {
    Trie *node = SearchPrefix(word);
    return node != nullptr && node->isEnd;
  }

  bool StartsWith(const std::string &prefix) {
    return SearchPrefix(prefix) != nullptr;
  }

private:
  std::vector<Trie *> children;
  bool isEnd;

  Trie *SearchPrefix(const std::string &prefix) {
    Trie *node = this;
    for (char ch : prefix) {
      ch -= 'a';
      if (node->children[ch] == nullptr) {
        return nullptr;
      }
      node = node->children[ch];
    }
    return node;
  }
};
