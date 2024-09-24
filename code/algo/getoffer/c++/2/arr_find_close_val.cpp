#include <stack>
#include <vector>

std::vector<int> dailyTemperatures(const std::vector<int> &temperatures) {
  int length = temperatures.size();
  std::vector<int> ans(length, 0);
  std::stack<int> stack;

  for (int i = 0; i < length; ++i) {
    int temperature = temperatures[i];
    while (!stack.empty() && temperature > temperatures[stack.top()]) {
      int prevIndex = stack.top();
      stack.pop();
      ans[prevIndex] = i - prevIndex;
    }
    stack.push(i);
  }

  return ans;
}
