#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

std::string clean_word(const std::string &word) {
  std::string cleaned;
  for (char ch : word) {
    if (std::isalnum(ch)) {
      cleaned += std::tolower(ch);
    }
  }
  return cleaned;
}

int main() {
  std::string filename;
  std::cout << "Enter filename: ";
  std::cin >> filename;

  std::ifstream file(filename);
  if (!file) {
    std::cerr << "无法打开文件." << std::endl;
    return 1;
  }

  std::unordered_map<std::string, int> word_count;
  std::string word;

  while (file >> word) {
    word = clean_word(word);
    if (!word.empty()) {
      ++word_count[word];
    }
  }

  file.close();

  std::cout << "单词出现次数统计:" << std::endl;
  for (const auto &entry : word_count) {
    std::cout << entry.first << ": " << entry.second << std::endl;
  }
  return 0;
}