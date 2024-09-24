#include <iostream>
#include <limits>

using namespace std;

// 快速乘
// x 和 y 是负数，z 是正数
// 判断 z * y >= x 是否成立
bool quickAdd(int y, int z, int x) {
  int result = 0, add = y;
  while (z > 0) { // 不能使用除法
    if (z & 1) {
      // 需要保证 result + add >= x
      if (result < x - add) {
        return false;
      }
      result += add;
    }
    if (z != 1) {
      // 需要保证 add + add >= x
      if (add < x - add) {
        return false;
      }
      add += add;
    }
    z >>= 1;
  }
  return true;
}

int divide(int a, int b) {
  if (a == numeric_limits<int>::min()) { // 考虑被除数为最小值的情况
    if (b == 1) {
      return numeric_limits<int>::min();
    }
    if (b == -1) {
      return numeric_limits<int>::max();
    }
  }
  if (b == numeric_limits<int>::min()) { // 考虑除数为最小值的情况
    if (a == numeric_limits<int>::min()) {
      return 1;
    }
    return 0;
  }
  if (a == 0) { // 考虑被除数为 0 的情况
    return 0;
  }

  // 一般情况，使用二分查找
  // 将所有的正数取相反数，这样就只需要考虑一种情况
  bool rev = false;
  if (a > 0) {
    a = -a;
    rev = !rev;
  }
  if (b > 0) {
    b = -b;
    rev = !rev;
  }

  int ans = 0;
  int left = 1, right = numeric_limits<int>::max();
  while (left <= right) {
    int mid = left + ((right - left) >> 1); // 注意溢出，并且不能使用除法
    if (quickAdd(b, mid, a)) {
      ans = mid;
      if (mid == numeric_limits<int>::max()) { // 注意溢出
        break;
      }
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return rev ? -ans : ans;
}

int main() {
  std::cout << divide(4, 3) << std::endl;
  return 0;
}