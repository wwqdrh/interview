#include <cassert>
#include <cstring>
#include <iostream>

class MemoryManager {
private:
  struct MemoryBlock {
    size_t size;       // 块大小
    bool is_free;      // 是否空闲
    MemoryBlock *next; // 指向下一个块

    MemoryBlock(size_t s) : size(s), is_free(true), next(nullptr) {}
  };

  void *memory_pool; // 内存池起始地址
  size_t pool_size;  // 内存池大小
  MemoryBlock *head; // 内存块链表头部

  // 获取块的数据区域起始地址
  void *GetDataPtr(MemoryBlock *block) {
    return reinterpret_cast<char *>(block) + sizeof(MemoryBlock);
  }

  // 从数据区域指针获取对应的块
  MemoryBlock *GetBlock(void *data) {
    return reinterpret_cast<MemoryBlock *>(static_cast<char *>(data) -
                                           sizeof(MemoryBlock));
  }

  // 合并相邻的空闲块
  void MergeFreeBlocks() {
    MemoryBlock *current = head;
    while (current && current->next) {
      if (current->is_free && current->next->is_free) {
        current->size += current->next->size + sizeof(MemoryBlock);
        current->next = current->next->next;
      } else {
        current = current->next;
      }
    }
  }

public:
  MemoryManager(size_t size) : pool_size(size) {
    // 分配内存池
    memory_pool = malloc(pool_size);
    if (!memory_pool) {
      throw std::bad_alloc();
    }

    // 初始化第一个块
    head = new (memory_pool) MemoryBlock(size - sizeof(MemoryBlock));
  }

  ~MemoryManager() {
    if (memory_pool) {
      free(memory_pool);
    }
  }

  // 分配内存
  void *Allocate(size_t size) {
    // 对齐到8字节边界
    size = (size + 7) & ~7;

    MemoryBlock *current = head;
    MemoryBlock *best_fit = nullptr;
    size_t min_size_diff = SIZE_MAX;

    // 使用最佳适配算法查找合适的块
    while (current) {
      if (current->is_free && current->size >= size) {
        size_t size_diff = current->size - size;
        if (size_diff < min_size_diff) {
          best_fit = current;
          min_size_diff = size_diff;
        }
      }
      current = current->next;
    }

    if (!best_fit) {
      return nullptr; // 内存不足
    }

    // 如果剩余空间足够大，进行分裂
    if (min_size_diff >= sizeof(MemoryBlock) + 8) {
      MemoryBlock *new_block = reinterpret_cast<MemoryBlock *>(
          reinterpret_cast<char *>(GetDataPtr(best_fit)) + size);
      new_block = new (new_block)
          MemoryBlock(best_fit->size - size - sizeof(MemoryBlock));
      new_block->next = best_fit->next;
      best_fit->next = new_block;
      best_fit->size = size;
    }

    best_fit->is_free = false;
    return GetDataPtr(best_fit);
  }

  // 释放内存
  void Free(void *ptr) {
    if (!ptr)
      return;

    MemoryBlock *block = GetBlock(ptr);
    block->is_free = true;
    MergeFreeBlocks();
  }

  // 打印内存使用情况
  void PrintMemoryMap() const {
    MemoryBlock *current = head;
    int block_count = 0;

    std::cout << "\nMemory Map:\n";
    while (current) {
      std::cout << "Block " << block_count++ << " [Size: " << current->size
                << ", Status: " << (current->is_free ? "Free" : "Used")
                << "]\n";
      current = current->next;
    }
    std::cout << std::endl;
  }
};

int main() {
  try {
    MemoryManager mm(1024); // 创建1KB的内存池

    // 分配一些内存
    void *p1 = mm.Allocate(128);
    void *p2 = mm.Allocate(256);
    void *p3 = mm.Allocate(64);

    mm.PrintMemoryMap();

    // 释放一些内存
    mm.Free(p2);
    mm.PrintMemoryMap();

    // 再次分配
    void *p4 = mm.Allocate(192);
    mm.PrintMemoryMap();

    // 清理其他内存
    mm.Free(p1);
    mm.Free(p3);
    mm.Free(p4);

    mm.PrintMemoryMap();

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}