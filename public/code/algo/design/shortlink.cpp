#include <iostream>
#include <map>
#include <mutex>
#include <random>
#include <set>
#include <string>
#include <vector>

class LinkMap {
private:
  LinkMap() {} // 构造函数，私有化，防止外部创建实例

  std::set<std::string> shortlinks;
  std::map<std::string, std::string> links;
  std::mutex mtx;
  std::mt19937 rng; // 随机数生成器，用于生成随机的短链接
  const std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuv"
                              "wxyz0123456789"; // 可用字符集
  const int length = 6;                         // 短链接长度

public:
  // 获取单例的静态方法
  static LinkMap &getInstance() {
    static LinkMap instance; // 使用局部静态变量，保证只有一个实例
    return instance;
  }
  LinkMap(const LinkMap &) = delete;            // 禁止拷贝构造
  LinkMap &operator=(const LinkMap &) = delete; // 禁止赋值构造

  std::string registerLink(std::string link) {
    std::lock_guard<std::mutex> lock(mtx);
    if (links.count(link) > 0) {
      return links[link];
    }
    std::string shortlink;
    do {
      shortlink.clear();
      for (int i = 0; i < length; i++) {
        int index = rng() % charset.size();
        shortlink.push_back(charset[index]);
      }
    } while (shortlinks.count(shortlink) > 0);
    shortlinks.insert(shortlink);
    links[link] = shortlink;
    return shortlink;
  }

  std::string visitLink(std::string link) {
    std::lock_guard<std::mutex> lock(mtx);
    if (shortlinks.count(link) > 0) {
      // 短链接
      for (auto &pair : links) {
        if (pair.second == link) {
          return pair.first;
        }
      }
    }
    return link;
  }
};

class User {
private:
  int id;

public:
  User(int id) : id(id) {}
  std::string registerLink(std::string link) {
    LinkMap &linkMap = LinkMap::getInstance();
    std::string shortlink = linkMap.registerLink(link);
    return shortlink;
  }

  std::string visitLink(std::string link) {
    LinkMap &linkMap = LinkMap::getInstance();
    return linkMap.visitLink(link);
  }
};

int main() {
  User user1(1);
  User user2(2);

  std::string link1 = user1.registerLink("https://link/thisisalongurl1");
  std::string link2 = user1.registerLink("https://link/thisisalongurl2");
  // 打印两个短链接
  std::cout << "User 1's short link: " << link1 << std::endl;
  std::cout << "User 2's short link: " << link2 << std::endl;
  // 用户1访问自己的短链接，返回长链接
  std::cout << "User 1 visits own link: " << user1.visitLink(link1)
            << std::endl;
  // 用户1访问用户2的短链接，返回长链接
  std::cout << "User 1 visits user 2's link: " << user1.visitLink(link2)
            << std::endl;
  // 用户2访问自己的短链接，返回长链接
  std::cout << "User 2 visits own link: " << user2.visitLink(link2)
            << std::endl;
  // 用户2访问用户1的短链接，返回长链接
  std::cout << "User 2 visits user 1's link: " << user2.visitLink(link1)
            << std::endl;
  // 用户1访问一个不存在的短链接，返回原始链接
  std::cout << "User 1 visits invalid link: "
            << user1.visitLink("http://link/validurl") << std::endl;
  // 用户2访问一个长链接，返回原始链接
  std::cout << "User 2 visits long link: "
            << user2.visitLink("https://link/validurl") << std::endl;
}