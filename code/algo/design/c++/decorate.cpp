#include <functional>
#include <iostream>

class A {
public:
  void methodA() { std::cout << "Executing methodA" << std::endl; }
};

// 包装器函数，类似于装饰器
auto decorate(std::function<void()> func) {
  return [func]() {
    std::cout << "Before executing methodA" << std::endl;
    func(); // 调用原始函数
    std::cout << "After executing methodA" << std::endl;
  };
}

int main() {
  A a;

  // 使用lambda表达式将原函数包装
  auto decoratedMethodA = decorate([&a]() { a.methodA(); });

  // 调用装饰后的方法
  decoratedMethodA();

  return 0;
}
