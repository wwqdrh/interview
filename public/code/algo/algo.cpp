#include "algo.h"
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void Menu::addItem(int number, std::string description,
                   std::vector<std::string> tags, std::string functionName) {
  items.push_back(Item(number, description, tags, functionName));
  // 注意：这里需要将函数名映射到具体的函数实现
}

void Menu::displayItems() {
  for (const auto &item : items) {
    std::cout << item.number << ": " << item.description << std::endl;
  }
}

void Menu::selectItem(int number) {
  for (const auto &item : items) {
    if (item.number == number) {
      std::cout << "您选择的编号 " << number << std::endl;
      // 查找并执行函数
      auto it = functionMap.find(item.functionName);
      if (it != functionMap.end()) {
        it->second();
      } else {
        std::cout << "未找到函数名: " << item.functionName << std::endl;
      }
      return;
    }
  }
  std::cout << "未找到编号: " << number << std::endl;
}

void Menu::addFunction(std::string name, std::function<void()> func) {
  functionMap[name] = func;
}

int main() {
  Menu menu;
  // 添加项目和函数
  menu.addItem(1, "链表翻转", {"双指针", "链表"}, "reverseLinkedList");
  menu.addItem(2, "单调队列", {"队列"}, "monoQueue");
  menu.addItem(3, "lfu缓存", {"缓存"}, "lrucache");

  // 映射函数名到函数实现
  menu.addFunction("reverseLinkedList", reverseLinkedList);
  menu.addFunction("monoQueue", ExampleMonoQueue);
  menu.addFunction("lrucache", exampleLRUCache);

  std::cout << "可用选项：" << std::endl;
  menu.displayItems();

  std::cout << "请输入编号以执行函数: ";
  int number;
  std::cin >> number;

  menu.selectItem(number);

  return 0;
}
