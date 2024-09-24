#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

int evalRPN(const std::vector<std::string> &tokens) {
  std::stack<int> stack;
  for (const auto &token : tokens) {
    if (isdigit(token.back())) {
      stack.push(std::stoi(token));
    } else {
      int b = stack.top();
      stack.pop();
      int a = stack.top();
      stack.pop();
      if (token == "+") {
        stack.push(a + b);
      } else if (token == "-") {
        stack.push(a - b);
      } else if (token == "*") {
        stack.push(a * b);
      } else if (token == "/") {
        stack.push(a / b);
      } else {
        throw std::invalid_argument("Invalid operator");
      }
    }
  }
  return stack.top();
}
