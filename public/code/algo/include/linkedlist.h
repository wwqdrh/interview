#include <iostream>
#include <mutex>

class LinkList {
private:
  struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
  };

  ListNode *head;
  std::mutex list_mutex; // 用于保证并发安全的互斥锁

public:
  LinkList() : head(nullptr) {}

  ~LinkList() {
    // 析构函数中清理所有节点，确保内存安全
    std::lock_guard<std::mutex> lock(list_mutex);
    while (head != nullptr) {
      ListNode *temp = head;
      head = head->next;
      delete temp;
    }
  }

  // 迭代版本的链表翻转
  void reverseIterative() {
    std::lock_guard<std::mutex> lock(list_mutex);
    ListNode *prev = nullptr;
    ListNode *curr = head;
    while (curr != nullptr) {
      ListNode *nextTemp = curr->next;
      curr->next = prev;
      prev = curr;
      curr = nextTemp;
    }
    head = prev;
  }

  // 递归版本的链表翻转
  ListNode *reverseRecursiveHelper(ListNode *node) {
    if (node == nullptr || node->next == nullptr)
      return node;
    ListNode *p = reverseRecursiveHelper(node->next);
    node->next->next = node;
    node->next = nullptr;
    return p;
  }

  void reverseRecursive() {
    std::lock_guard<std::mutex> lock(list_mutex);
    head = reverseRecursiveHelper(head);
  }

  // 添加新节点到链表头部
  void pushFront(int val) {
    std::lock_guard<std::mutex> lock(list_mutex);
    ListNode *node = new ListNode(val);
    node->next = head;
    head = node;
  }

  // 打印链表
  void printList() {
    std::lock_guard<std::mutex> lock(list_mutex);
    ListNode *temp = head;
    while (temp != nullptr) {
      std::cout << temp->val << " ";
      temp = temp->next;
    }
    std::cout << std::endl;
  }
};

// 测试链表翻转
void reverseLinkedList();