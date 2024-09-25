#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

int partition(vector<int> &a, int l, int r) {
  int x = a[r];
  int i = l - 1;
  for (int j = l; j < r; ++j) {
    if (a[j] <= x) {
      ++i;
      swap(a[i], a[j]);
    }
  }
  swap(a[i + 1], a[r]);
  return i + 1;
}

int randomPartition(vector<int> &a, int l, int r) {
  int i = rand() % (r - l + 1) + l;
  swap(a[i], a[r]);
  return partition(a, l, r);
}

int quickSelect(vector<int> &a, int l, int r, int index) {
  int q = randomPartition(a, l, r);
  if (q == index) {
    return a[q];
  } else if (q < index) {
    return quickSelect(a, q + 1, r, index);
  }
  return quickSelect(a, l, q - 1, index);
}

int findKthLargest(vector<int> &nums, int k) {
  srand(time(0));
  return quickSelect(nums, 0, nums.size() - 1, nums.size() - k);
}
