#include <iostream>
#include <string>
#include <vector>
using namespace std;

int maxProduct(const vector<string> &words) {
  int ans = 0;
  int n = words.size();
  vector<int> masks(n, 0); // 用于存储每个单词的掩码

  // 计算每个单词的字母掩码
  for (int i = 0; i < n; ++i) {
    for (char ch : words[i]) {
      masks[i] |= (1 << (ch - 'a')); // 将字母对应的位标记为1
    }
  }

  // 两两比较掩码，找出没有公共字母的单词组合，并计算其乘积
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if ((masks[i] & masks[j]) == 0) { // 判断是否没有公共字母
        int product = words[i].size() * words[j].size();
        if (product > ans) {
          ans = product;
        }
      }
    }
  }

  return ans;
}

int main() {
  vector<string> words = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
  int ans = maxProduct(words);
  cout << ans << endl;
  return 0;
}