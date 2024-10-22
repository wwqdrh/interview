#include <cstdint>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class ConsistentHash {
private:
  // 虚拟节点倍数
  int virtual_node_count;
  // 哈希环，key是哈希值，value是节点名称
  std::map<uint32_t, std::string> hash_ring;
  // MurmurHash3算法的实现
  uint32_t murmur3_32(const std::string &key, uint32_t seed = 0) {
    const uint8_t *data = (const uint8_t *)key.c_str();
    const int len = key.length();
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;

    uint32_t h1 = seed;
    const int nblocks = len / 4;

    const uint32_t *blocks = (const uint32_t *)(data);

    for (int i = 0; i < nblocks; i++) {
      uint32_t k1 = blocks[i];

      k1 *= c1;
      k1 = (k1 << 15) | (k1 >> 17);
      k1 *= c2;

      h1 ^= k1;
      h1 = (h1 << 13) | (h1 >> 19);
      h1 = h1 * 5 + 0xe6546b64;
    }

    const uint8_t *tail = data + nblocks * 4;
    uint32_t k1 = 0;

    switch (len & 3) {
    case 3:
      k1 ^= tail[2] << 16;
    case 2:
      k1 ^= tail[1] << 8;
    case 1:
      k1 ^= tail[0];
      k1 *= c1;
      k1 = (k1 << 15) | (k1 >> 17);
      k1 *= c2;
      h1 ^= k1;
    }

    h1 ^= len;
    h1 ^= h1 >> 16;
    h1 *= 0x85ebca6b;
    h1 ^= h1 >> 13;
    h1 *= 0xc2b2ae35;
    h1 ^= h1 >> 16;

    return h1;
  }

public:
  ConsistentHash(int virtual_nodes = 100) : virtual_node_count(virtual_nodes) {}

  // 添加节点
  void addNode(const std::string &node) {
    for (int i = 0; i < virtual_node_count; i++) {
      std::string virtual_node = node + "#" + std::to_string(i);
      uint32_t hash = murmur3_32(virtual_node);
      hash_ring[hash] = node;
    }
  }

  // 删除节点
  void removeNode(const std::string &node) {
    for (int i = 0; i < virtual_node_count; i++) {
      std::string virtual_node = node + "#" + std::to_string(i);
      uint32_t hash = murmur3_32(virtual_node);
      hash_ring.erase(hash);
    }
  }

  // 获取键所在的节点
  std::string getNode(const std::string &key) {
    if (hash_ring.empty()) {
      return "";
    }

    uint32_t hash = murmur3_32(key);
    auto it = hash_ring.lower_bound(hash);

    if (it == hash_ring.end()) {
      return hash_ring.begin()->second;
    }
    return it->second;
  }

  // 获取当前节点数量
  size_t getNodeCount() const {
    std::vector<std::string> unique_nodes;
    for (const auto &pair : hash_ring) {
      if (std::find(unique_nodes.begin(), unique_nodes.end(), pair.second) ==
          unique_nodes.end()) {
        unique_nodes.push_back(pair.second);
      }
    }
    return unique_nodes.size();
  }
};

int main() {
  ConsistentHash ch(100); // 创建实例，每个节点创建100个虚拟节点

  // 添加几个节点
  ch.addNode("server1");
  ch.addNode("server2");
  ch.addNode("server3");

  // 获取某个键所在的节点
  std::string node = ch.getNode("user123");
  std::cout << "user123 is mapped to: " << node << std::endl;

  // 删除一个节点
  ch.removeNode("server2");

  // 再次获取键所在的节点
  node = ch.getNode("user123");
  std::cout << "After removal, user123 is mapped to: " << node << std::endl;
}