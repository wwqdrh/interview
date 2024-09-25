#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

class ZSet {
public:
  void insert(int key) { data[key]++; }

  void erase(int key) { data.erase(key); }

  vector<int> keys() const {
    vector<int> res;
    for (const auto &[key, _] : data) {
      res.push_back(key);
    }
    sort(res.begin(), res.end());
    return res;
  }

  int count(int key) const {
    auto it = data.find(key);
    return it != data.end() ? it->second : 0;
  }

private:
  unordered_map<int, int> data;
};

vector<int> relativeSortArray(vector<int> &arr1, const vector<int> &arr2) {
  ZSet zs;
  for (int val : arr1) {
    zs.insert(val);
  }

  vector<int> res;
  for (int val : arr2) {
    int count = zs.count(val);
    res.insert(res.end(), count, val);
    zs.erase(val);
  }

  vector<int> remainingKeys = zs.keys();
  for (int key : remainingKeys) {
    int count = zs.count(key);
    res.insert(res.end(), count, key);
  }

  return res;
}
