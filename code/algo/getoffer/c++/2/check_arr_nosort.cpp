#include <array>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::vector<std::string>>
groupAnagrams(std::vector<std::string> &strs) {
  std::unordered_map<std::array<int, 26>, std::vector<std::string>> mp;
  for (const auto &str : strs) {
    std::array<int, 26> cnt = {0};
    for (char ch : str) {
      cnt[ch - 'a']++;
    }
    mp[cnt].push_back(str);
  }
  std::vector<std::vector<std::string>> ans;
  for (auto &[key, group] : mp) {
    ans.push_back(std::move(group));
  }
  return ans;
}
