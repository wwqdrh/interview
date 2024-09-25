#include <string>
#include <unordered_map>
#include <vector>

class TrieNode {
public:
  TrieNode *children[26] = {nullptr};
  int val = 0;
};

class MapSum {
public:
  MapSum() { root = new TrieNode(); }

  void Insert(const std::string &key, int val) {
    int delta = val;
    if (cnt.find(key) != cnt.end()) {
      delta -= cnt[key];
    }
    cnt[key] = val;
    TrieNode *node = root;
    for (char ch : key) {
      ch -= 'a';
      if (node->children[ch] == nullptr) {
        node->children[ch] = new TrieNode();
      }
      node = node->children[ch];
      node->val += delta;
    }
  }

  int Sum(const std::string &prefix) {
    TrieNode *node = root;
    for (char ch : prefix) {
      ch -= 'a';
      if (node->children[ch] == nullptr) {
        return 0;
      }
      node = node->children[ch];
    }
    return node->val;
  }

private:
  TrieNode *root;
  std::unordered_map<std::string, int> cnt;
};
