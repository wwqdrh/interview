#include <algorithm>
#include <stack>
#include <vector>

int largestRectangleArea(const std::vector<int> &heights) {
  int n = heights.size();
  std::vector<int> left(n), right(n);
  std::stack<int> mono_stack;

  for (int i = 0; i < n; ++i) {
    while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
      mono_stack.pop();
    }
    left[i] = mono_stack.empty() ? -1 : mono_stack.top();
    mono_stack.push(i);
  }

  while (!mono_stack.empty())
    mono_stack.pop();

  for (int i = n - 1; i >= 0; --i) {
    while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
      mono_stack.pop();
    }
    right[i] = mono_stack.empty() ? n : mono_stack.top();
    mono_stack.push(i);
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    ans = std::max(ans, (right[i] - left[i] - 1) * heights[i]);
  }

  return ans;
}

int max(int x, int y) { return x > y ? x : y; }
