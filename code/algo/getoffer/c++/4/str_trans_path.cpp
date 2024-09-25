#include <climits>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

int ladderLength(const std::string &beginWord, const std::string &endWord,
                 std::vector<std::string> &wordList) {
  std::unordered_map<std::string, int> wordId;
  std::vector<std::vector<int>> graph;
  int idCounter = 0;

  auto addWord = [&](std::string word) -> int {
    if (wordId.find(word) == wordId.end()) {
      wordId[word] = idCounter++;
      graph.push_back({});
    }
    return wordId[word];
  };

  auto addEdge = [&](std::string word) -> int {
    int id1 = addWord(word);
    std::string s = word;
    for (size_t i = 0; i < s.size(); ++i) {
      char originalChar = s[i];
      s[i] = '*';
      int id2 = addWord(s);
      graph[id1].push_back(id2);
      graph[id2].push_back(id1);
      s[i] = originalChar;
    }
    return id1;
  };

  for (const auto &word : wordList) {
    addEdge(word);
  }
  int beginId = addEdge(beginWord);
  if (wordId.find(endWord) == wordId.end()) {
    return 0;
  }
  int endId = wordId[endWord];

  const int inf = INT_MAX;
  std::vector<int> dist(wordId.size(), inf);
  dist[beginId] = 0;
  std::queue<int> queue;
  queue.push(beginId);

  while (!queue.empty()) {
    int v = queue.front();
    queue.pop();
    if (v == endId) {
      return dist[endId] / 2 + 1;
    }
    for (int w : graph[v]) {
      if (dist[w] == inf) {
        dist[w] = dist[v] + 1;
        queue.push(w);
      }
    }
  }
  return 0;
}

int main() {
  std::vector<std::string> wordList = {"hot", "dot", "dog",
                                       "lot", "log", "cog"};
  std::string beginWord = "hit";
  std::string endWord = "cog";
  std::cout << "Ladder length: " << ladderLength(beginWord, endWord, wordList)
            << std::endl;
  return 0;
}
