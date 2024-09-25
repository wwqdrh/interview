#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Trie {
public:
  unordered_map<char, Trie *> children;
  bool isEnd = false;

  void insert(const string &word) {
    Trie *node = this;
    for (char c : word) {
      if (node->children.find(c) == node->children.end()) {
        node->children[c] = new Trie();
      }
      node = node->children[c];
    }
    node->isEnd = true;
  }

  string searchRoot(const string &word) {
    Trie *node = this;
    for (int i = 0; i < word.size(); ++i) {
      char c = word[i];
      if (node->isEnd) {
        return word.substr(0, i);
      }
      if (node->children.find(c) == node->children.end()) {
        break;
      }
      node = node->children[c];
    }
    return word;
  }
};

string replaceWords(vector<string> &dictionary, const string &sentence) {
  Trie root;
  for (const string &word : dictionary) {
    root.insert(word);
  }

  istringstream iss(sentence);
  string word;
  string result;
  while (iss >> word) {
    if (!result.empty()) {
      result += " ";
    }
    result += root.searchRoot(word);
  }

  return result;
}
