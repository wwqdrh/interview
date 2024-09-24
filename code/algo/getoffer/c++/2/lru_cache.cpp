#include <list>
#include <unordered_map>

class LRUCache {
public:
  LRUCache(int capacity) : capacity(capacity) {}

  int get(int key) {
    auto it = cache.find(key);
    if (it == cache.end()) {
      return -1;
    }
    // Move the accessed element to the front of the list
    list.splice(list.begin(), list, it->second);
    return it->second->second;
  }

  void put(int key, int value) {
    auto it = cache.find(key);
    if (it != cache.end()) {
      // Update the value and move the element to the front of the list
      it->second->second = value;
      list.splice(list.begin(), list, it->second);
      return;
    }
    if (list.size() == capacity) {
      // Remove the least recently used element
      int lruKey = list.back().first;
      list.pop_back();
      cache.erase(lruKey);
    }
    // Insert the new element at the front of the list
    list.emplace_front(key, value);
    cache[key] = list.begin();
  }

private:
  int capacity;
  std::list<std::pair<int, int>> list;
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> cache;
};
