#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// 二进制字符串相加
string addBinary(string a, string b) {
  string ans = "";
  int carry = 0;
  int lenA = a.size(), lenB = b.size();
  int n = max(lenA, lenB);

  // 从后往前逐位相加
  for (int i = 0; i < n; i++) {
    if (i < lenA) {
      carry += a[lenA - i - 1] - '0';
    }
    if (i < lenB) {
      carry += b[lenB - i - 1] - '0';
    }
    ans = char(carry % 2 + '0') + ans;
    carry /= 2;
  }

  // 如果最后有进位，补上一个1
  if (carry > 0) {
    ans = '1' + ans;
  }

  return ans;
}

int main() {
  std::cout << addBinary("11", "1") << std::endl;
  std::cout << addBinary("11", "1001") << std::endl;
  return 0;
}