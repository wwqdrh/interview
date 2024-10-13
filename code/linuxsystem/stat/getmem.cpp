#include <fstream>
#include <iostream>
#include <string>
#include <sys/sysctl.h>
#include <sys/types.h>

#ifdef __APPLE__
#include <mach/mach.h> // macOS specific
#endif

void getMemoryUsage() {
#ifdef __linux__
  std::ifstream file("/proc/meminfo");
  std::string line;
  long total_memory = 0;
  long free_memory = 0;

  if (file.is_open()) {
    while (std::getline(file, line)) {
      if (line.find("MemTotal:") == 0) {
        sscanf(line.c_str(), "MemTotal: %ld kB", &total_memory);
      }
      if (line.find("MemFree:") == 0) {
        sscanf(line.c_str(), "MemFree: %ld kB", &free_memory);
      }
    }
    file.close();

    std::cout << "Total Memory (Linux): " << total_memory / 1024 << " MB"
              << std::endl;
    std::cout << "Free Memory (Linux): " << free_memory / 1024 << " MB"
              << std::endl;
    std::cout << "Used Memory (Linux): " << (total_memory - free_memory) / 1024
              << " MB" << std::endl;
  }
#elif __APPLE__
  int64_t total_memory = 0;
  int mib[2] = {CTL_HW, HW_MEMSIZE}; // MacOS uses HW_MEMSIZE for total memory
  size_t length = sizeof(total_memory);
  if (sysctl(mib, 2, &total_memory, &length, NULL, 0) == 0) {
    vm_size_t page_size;
    mach_port_t mach_port = mach_host_self();
    mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
    vm_statistics64_data_t vm_stats;

    if (host_page_size(mach_port, &page_size) == KERN_SUCCESS &&
        host_statistics64(mach_port, HOST_VM_INFO, (host_info64_t)&vm_stats,
                          &count) == KERN_SUCCESS) {
      long long free_memory = (int64_t)vm_stats.free_count * (int64_t)page_size;
      long long used_memory = total_memory - free_memory;

      std::cout << "Total Memory (macOS): " << total_memory / (1024 * 1024)
                << " MB" << std::endl;
      std::cout << "Free Memory (macOS): " << free_memory / (1024 * 1024)
                << " MB" << std::endl;
      std::cout << "Used Memory (macOS): " << used_memory / (1024 * 1024)
                << " MB" << std::endl;
    }
  }
#endif
}

int main() {
  getMemoryUsage();
  return 0;
}
