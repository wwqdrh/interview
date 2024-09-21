#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "array.h"
#include "linkedlist.h"
#include "queue.h"
#include "cache.h"

class Item {
public:
  int number;
  std::string description;
  std::vector<std::string> tags;
  std::string functionName;

  Item(int num, std::string desc, std::vector<std::string> tg,
       std::string funcName)
      : number(num), description(desc), tags(tg), functionName(funcName) {}
};

class Menu {
private:
  std::vector<Item> items;
  std::unordered_map<std::string, std::function<void()>> functionMap;

public:
  void addItem(int number, std::string description,
               std::vector<std::string> tags, std::string functionName);

  void displayItems();

  void selectItem(int number);

  // 添加函数映射
  void addFunction(std::string name, std::function<void()> func);
};
