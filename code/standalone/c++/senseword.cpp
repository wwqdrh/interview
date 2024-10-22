#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class TrieNode {
public:
  bool isEndOfWord;
  std::unordered_map<std::string, std::unique_ptr<TrieNode>> children;

  TrieNode() : isEndOfWord(false) {}
};

class SensitiveWordFilter {
private:
  std::unique_ptr<TrieNode> root;

  // 获取UTF-8字符的字节数
  static size_t getUtf8CharLen(unsigned char c) {
    if ((c & 0x80) == 0)
      return 1;
    if ((c & 0xE0) == 0xC0)
      return 2;
    if ((c & 0xF0) == 0xE0)
      return 3;
    if ((c & 0xF8) == 0xF0)
      return 4;
    return 1; // 对于无效的UTF-8字符，当作1字节处理
  }

  // 从字符串指定位置获取一个UTF-8字符
  static std::string getUtf8Char(const std::string &str, size_t pos) {
    if (pos >= str.length())
      return "";
    size_t len = getUtf8CharLen(static_cast<unsigned char>(str[pos]));
    if (pos + len > str.length())
      return "";
    return str.substr(pos, len);
  }

public:
  SensitiveWordFilter() : root(std::make_unique<TrieNode>()) {}

  // 添加敏感词
  void addWord(const std::string &word) {
    TrieNode *current = root.get();
    size_t pos = 0;

    while (pos < word.length()) {
      std::string ch = getUtf8Char(word, pos);
      if (ch.empty())
        break;

      if (current->children.find(ch) == current->children.end()) {
        current->children[ch] = std::make_unique<TrieNode>();
      }
      current = current->children[ch].get();
      pos += ch.length();
    }
    current->isEndOfWord = true;
  }

  // 从文件加载敏感词列表
  bool loadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open())
      return false;

    std::string word;
    while (std::getline(file, word)) {
      if (!word.empty()) {
        addWord(word);
      }
    }
    return true;
  }

  // 检查文本中是否包含敏感词
  bool containsSensitiveWords(const std::string &text) {
    size_t pos = 0;
    while (pos < text.length()) {
      TrieNode *current = root.get();
      size_t checkPos = pos;

      while (checkPos < text.length()) {
        std::string ch = getUtf8Char(text, checkPos);
        if (ch.empty())
          break;

        if (current->children.find(ch) == current->children.end()) {
          break;
        }
        current = current->children[ch].get();
        if (current->isEndOfWord) {
          return true;
        }
        checkPos += ch.length();
      }

      std::string ch = getUtf8Char(text, pos);
      pos += ch.empty() ? 1 : ch.length();
    }
    return false;
  }

  // 过滤敏感词
  std::string filter(const std::string &text) {
    std::string result;
    size_t pos = 0;

    while (pos < text.length()) {
      TrieNode *current = root.get();
      size_t checkPos = pos;
      size_t matchLen = 0;
      size_t maxMatchLen = 0;
      size_t chLen = 0;

      while (checkPos < text.length()) {
        std::string ch = getUtf8Char(text, checkPos);
        if (ch.empty())
          break;

        if (current->children.find(ch) == current->children.end()) {
          break;
        }
        current = current->children[ch].get();
        matchLen += ch.length();
        chLen += 1;
        if (current->isEndOfWord) {
          maxMatchLen = matchLen;
        }
        checkPos += ch.length();
      }

      if (maxMatchLen > 0) {
        result.append(chLen, '*');
        pos += maxMatchLen;
      } else {
        std::string ch = getUtf8Char(text, pos);
        result.append(ch);
        pos += ch.empty() ? 1 : ch.length();
      }
    }

    return result;
  }
};

int main() {
  SensitiveWordFilter filter;

  // 添加敏感词
  filter.addWord("敏感词");
  filter.addWord("测试词");

  // 测试文本
  std::string text = "这是一个敏感词和测试词的例子";

  // 检查是否包含敏感词
  if (filter.containsSensitiveWords(text)) {
    std::cout << "文本包含敏感词" << std::endl;
  }

  // 过滤敏感词
  std::string filtered = filter.filter(text);
  std::cout << "过滤后: " << filtered << std::endl;
  // 输出: 这是一个***和***的例子

  return 0;
}