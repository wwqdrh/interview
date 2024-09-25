#include <algorithm>
#include <vector>

int peakIndexInMountainArray(const std::vector<int> &arr) {
  return std::distance(arr.begin(), std::find_if(
                                        arr.begin(), arr.end() - 1,
                                        &{ return arr[i] > arr[i + 1]; }));
}
