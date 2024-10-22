
#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <utility>
#include <vector>

struct SkipNode {
  int playerId;
  int64_t score;
  std::vector<std::shared_ptr<SkipNode>> forward;

  SkipNode(int pid, int64_t s, int level)
      : playerId(pid), score(s), forward(level, nullptr) {}
};

class SkipList {
private:
  static inline const int MAX_LEVEL = 16; // 最大层数
  static inline constexpr float P = 0.5f; // 层数增加的概率

  std::shared_ptr<SkipNode> header;
  int level;
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_real_distribution<> dis;

  // 生成随机层数
  int randomLevel() {
    int lvl = 1;
    while (dis(gen) < P && lvl < MAX_LEVEL) {
      lvl++;
    }
    return lvl;
  }

public:
  SkipList() : level(1), gen(rd()), dis(0, 1) {
    header = std::make_shared<SkipNode>(0, INT64_MAX, MAX_LEVEL);
  }

  void insert(int playerId, int64_t score) {
    std::vector<std::shared_ptr<SkipNode>> update(MAX_LEVEL);
    std::shared_ptr<SkipNode> current = header;
    // 从最高层开始查找，加快查找速度
    for (int i = level - 1; i >= 0; i--) {
      while (current->forward[i] != nullptr &&
             (current->forward[i]->score > score ||
              (current->forward[i]->score == score &&
               current->forward[i]->playerId < playerId))) {
        current = current->forward[i];
      }
      update[i] = current;
    }
    current = current->forward[0];

    // 如果玩家已经存在则更新分数
    if (current != nullptr && current->playerId == playerId) {
      if (current->score == score)
        return;
      // 删除旧节点
      for (int i = 0; i < level; i++) {
        if (update[i]->forward[i] != current)
          break;
        update[i]->forward[i] = current->forward[i];
      }
      current.reset();
    }

    // 创建新节点
    int newLevel = randomLevel();
    if (newLevel > level) {
      for (int i = level; i < newLevel; i++) {
        update[i] = header;
      }
      level = newLevel;
    }

    current = std::make_shared<SkipNode>(playerId, score, newLevel);
    for (int i = 0; i < newLevel; i++) {
      current->forward[i] = update[i]->forward[i];
      update[i]->forward[i] = current;
    }
  }

  std::vector<std::pair<int, int64_t>> getRangeByRank(int start, int end) {
    std::vector<std::pair<int, int64_t>> result;
    std::shared_ptr<SkipNode> current = header->forward[0];
    int rank = 0;

    while (current != nullptr && rank < end) {
      rank++;
      if (rank >= start) {
        result.emplace_back(current->playerId, current->score);
      }
      current = current->forward[0];
    }

    return result;
  }

  int64_t getPlayerScore(int playerId) {
    std::shared_ptr<SkipNode> current = header;
    for (int i = level - 1; i >= 0; i--) {
      while (current->forward[i] != nullptr &&
             current->forward[i]->playerId < playerId) {
        current = current->forward[i];
      }
    }
    current = current->forward[0];
    return (current != nullptr && current->playerId == playerId)
               ? current->score
               : -1;
  }

  int getPlayerRank(int playerId) {
    int rank = 0;
    std::shared_ptr<SkipNode> current = header->forward[0];
    while (current != nullptr) {
      if (current->playerId == playerId) {
        return rank + 1;
      }
      rank++;
      current = current->forward[0];
    }
    return -1;
  }
};

// 排行榜类
class Leaderboard {
private:
  SkipList rankings;
  std::unordered_map<int, std::string> playerNames; // 玩家ID到名字的映射

public:
  // 更新玩家分数
  void updateScore(int playerId, const std::string &name, int64_t score) {
    playerNames[playerId] = name;
    rankings.insert(playerId, score);
  }

  // 获取前N名玩家
  std::vector<std::pair<std::string, int64_t>> getTopN(int n) {
    auto topPlayers = rankings.getRangeByRank(1, n);
    std::vector<std::pair<std::string, int64_t>> result;
    for (const auto &player : topPlayers) {
      result.emplace_back(playerNames[player.first], player.second);
    }
    return result;
  }

  // 获取某个玩家前后N名玩家
  std::vector<std::pair<std::string, int64_t>> getPlayerNeighbors(int playerId,
                                                                  int n) {
    int rank = rankings.getPlayerRank(playerId);
    if (rank == -1)
      return {};

    int start = std::max(1, rank - n);
    int end = rank + n;
    auto neighbors = rankings.getRangeByRank(start, end);

    std::vector<std::pair<std::string, int64_t>> result;
    for (const auto &player : neighbors) {
      result.emplace_back(playerNames[player.first], player.second);
    }
    return result;
  }

  // 获取玩家排名
  int getPlayerRank(int playerId) { return rankings.getPlayerRank(playerId); }
};

int main() {
  Leaderboard leaderboard;

  // 添加一些玩家数据
  leaderboard.updateScore(1, "Player1", 1000);
  leaderboard.updateScore(2, "Player2", 2000);
  leaderboard.updateScore(3, "Player3", 1500);
  leaderboard.updateScore(4, "Player4", 3000);

  // 获取前3名玩家
  auto top3 = leaderboard.getTopN(3);
  std::cout << "Top 3 players:" << std::endl;
  for (const auto &player : top3) {
    std::cout << player.first << ": " << player.second << std::endl;
  }

  // 获取Player2前后2名的玩家
  auto neighbors = leaderboard.getPlayerNeighbors(2, 2);
  std::cout << "\nNeighbors of Player2:" << std::endl;
  for (const auto &player : neighbors) {
    std::cout << player.first << ": " << player.second << std::endl;
  }

  // 获取Player2的排名
  int rank = leaderboard.getPlayerRank(2);
  std::cout << "\nRank of Player2: " << rank << std::endl;
}