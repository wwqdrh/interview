#include <cassert>
#include <iostream>
#include <list>
#include <mutex>
#include <optional>
#include <unordered_map>
#include <utility>

template <typename Key, typename Value> class LRUCache {
private:
  size_t _capacity;
  std::list<Key> _lru;
  std::unordered_map<Key, std::pair<Value, typename std::list<Key>::iterator>>
      _cache;
  std::mutex _mutex;

public:
  LRUCache(size_t capacity) : _capacity(capacity) {}

  std::optional<Value> get(const Key &key) {
    std::lock_guard<std::mutex> lock(_mutex);
    auto it = _cache.find(key);
    if (it == _cache.end()) {
      return std::nullopt; // 返回一个空的std::optional对象
    } else {
      _lru.splice(_lru.begin(), _lru, it->second.second);
      return it->second.first; // 返回找到的值
    }
  }

  void put(const Key &key, const Value &value) {
    std::lock_guard<std::mutex> lock(_mutex);
    auto it = _cache.find(key);
    if (it != _cache.end()) {
      it->second.first = value;
      _lru.splice(_lru.begin(), _lru, it->second.second);
    } else {
      if (_cache.size() == _capacity) {
        auto last = _lru.end();
        --last;
        _cache.erase(*last);
        _lru.pop_back();
      }
      _lru.push_front(key);
      _cache[key] = {value, _lru.begin()};
    }
  }
};

void exampleLRUCache() {
  LRUCache<int, char> cache(2);

  // 添加元素并检查是否正确返回
  cache.put(1, 'A');
  assert(cache.get(1).value_or(' ') == 'A'); // 应该返回'A'

  cache.put(2, 'B');
  assert(cache.get(2).value_or(' ') == 'B'); // 应该返回'B'

  // 添加第三个元素，应该淘汰键为1的元素
  cache.put(3, 'C');
  assert(!cache.get(1).has_value()); // 应该返回false，因为键为1的元素已被淘汰
  assert(cache.get(3).value_or(' ') == 'C'); // 应该返回'C'

  // 添加第四个元素，应该淘汰键为2的元素
  cache.put(4, 'D');
  assert(!cache.get(2).has_value()); // 应该返回false，因为键为2的元素已被淘汰
  assert(cache.get(4).value_or(' ') == 'D'); // 应该返回'D'

  std::cout << "所有测试通过！" << std::endl;
}
