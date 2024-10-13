#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef __APPLE__
#include <mach/mach.h> // macOS specific
#endif

// user: 用户态cpu时间
// nice：用户态下具有调整优先级的进程所占用的 CPU 时间
// system: 内核态cpu时间
// idle: 代表 CPU 处于空闲状态时的时间
// iowait: 等待磁盘、网络或其他 I/O 设备完成操作
// irq: 处理硬件中断请求（Interrupt Requests）所占用的 CPU 时间
// softirq: softirq 代表处理软中断（Soft Interrupt）所占用的 CPU
// 时间。软中断是由内核调度，用来处理较低优先级的中断工作，例如网络包处理。
// steal: steal 代表虚拟化环境中，由于虚拟机监控器（hypervisor）将 CPU
// 时间分配给其他虚拟机，当前虚拟机被"抢占"走的时间。

void getCpuUsage() {
#ifdef __linux__
  std::ifstream file("/proc/stat");
  std::string line;

  if (file.is_open()) {
    std::getline(file, line); // 读取第一行
    std::istringstream iss(line);
    std::string cpu;
    long user, nice, system, idle, iowait, irq, softirq, steal;

    iss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >>
        steal;

    long total_idle = idle + iowait;
    long total_non_idle = user + nice + system + irq + softirq + steal;
    long total = total_idle + total_non_idle;

    std::cout << "CPU Usage (Linux): " << ((total_non_idle * 100.0) / total)
              << "%" << std::endl;
  }
  file.close();
#elif __APPLE__
  // macOS: Use sysctl to get CPU load
  host_cpu_load_info_data_t cpuinfo;
  mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
  if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO,
                      (host_info_t)&cpuinfo, &count) == KERN_SUCCESS) {
    long total_user = cpuinfo.cpu_ticks[CPU_STATE_USER];
    long total_system = cpuinfo.cpu_ticks[CPU_STATE_SYSTEM];
    long total_idle = cpuinfo.cpu_ticks[CPU_STATE_IDLE];
    long total_nice = cpuinfo.cpu_ticks[CPU_STATE_NICE];
    long total = total_user + total_system + total_idle + total_nice;
    long total_non_idle = total_user + total_system + total_nice;

    std::cout << "CPU Usage (macOS): " << ((total_non_idle * 100.0) / total)
              << "%" << std::endl;
  }
#endif
}

int main() {
  getCpuUsage();
  return 0;
}
