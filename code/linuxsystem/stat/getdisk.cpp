#include <iostream>
#include <sys/mount.h> // macOS-specific header for statfs
#include <sys/statvfs.h>

void getDiskUsage(const char *path) {
#ifdef __linux__
  struct statvfs stat;

  if (statvfs(path, &stat) != 0) {
    std::cerr << "Error getting disk usage information (Linux)" << std::endl;
    return;
  }

  unsigned long total = stat.f_blocks * stat.f_frsize;
  unsigned long free = stat.f_bfree * stat.f_frsize;
  unsigned long available = stat.f_bavail * stat.f_frsize;
  unsigned long used = total - free;

  std::cout << "Total Disk (Linux): " << total / (1024 * 1024) << " MB"
            << std::endl;
  std::cout << "Used Disk (Linux): " << used / (1024 * 1024) << " MB"
            << std::endl;
  std::cout << "Available Disk (Linux): " << available / (1024 * 1024) << " MB"
            << std::endl;
#elif __APPLE__
  struct statfs stat;

  if (statfs(path, &stat) != 0) {
    std::cerr << "Error getting disk usage information (macOS)" << std::endl;
    return;
  }

  unsigned long total = stat.f_blocks * stat.f_bsize;
  unsigned long free = stat.f_bfree * stat.f_bsize;
  unsigned long available = stat.f_bavail * stat.f_bsize;
  unsigned long used = total - free;

  std::cout << "Total Disk (macOS): " << total / (1024 * 1024) << " MB"
            << std::endl;
  std::cout << "Used Disk (macOS): " << used / (1024 * 1024) << " MB"
            << std::endl;
  std::cout << "Available Disk (macOS): " << available / (1024 * 1024) << " MB"
            << std::endl;
#endif
}

int main() {
  getDiskUsage("/");
  return 0;
}
