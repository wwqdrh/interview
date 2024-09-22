#include <iostream>
#include <vector>
using namespace std;

// 计算一个整数的二进制表示中1的个数
int onesCount(int x) {
  int ones = 0;
  while (x > 0) {
    x &= (x - 1); // 消除最低位的1
    ones++;
  }
  return ones;
}

// 返回从0到n的每个整数的二进制表示中1的个数
vector<int> countBits(int n) {
  vector<int> bits(n + 1);
  for (int i = 0; i <= n; ++i) {
    bits[i] = onesCount(i);
  }
  return bits;
}

int main() {
  vector<int> bits = countBits(5);
  for (int i = 0; i < bits.size(); ++i) {
    cout << bits[i] << " ";
  }
  cout << endl;
  return 0;
}