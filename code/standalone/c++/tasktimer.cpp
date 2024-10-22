#include <__atomic/aliases.h>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>

class Timer {
public:
  using TimePoint = std::chrono::steady_clock::time_point;
  using TaskId = uint64_t;
  struct Task {
    TaskId id;
    TimePoint timePoint;
    std::function<void()> callback;
    bool operator>(const Task &other) const {
      return timePoint > other.timePoint;
    }
  };

private:
  std::atomic_bool running_;
  std::thread worker_;
  std::mutex mutex_;
  std::condition_variable cv_;
  std::priority_queue<Task, std::vector<Task>, std::greater<Task>> taskQueue_;
  std::map<TaskId, TimePoint> taskMap_;
  TaskId nextId_{0};

public:
  Timer() : running_(true) {
    worker_ = std::thread([this] { run(); });
  }

  ~Timer() {
    if (running_) {
      stop();
    }
  }

  TaskId addOnceTask(std::chrono::milliseconds delay,
                     std::function<void()> callback) {
    auto timePoint = std::chrono::steady_clock::now() + delay;
    return addTask(timePoint, std::move(callback));
  }

  bool cancelTask(TaskId id) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (taskMap_.find(id) != taskMap_.end()) {
      taskMap_.erase(id);
      return true;
    }
    return false;
  }

  void stop() {
    running_ = false;
    cv_.notify_one();
    if (worker_.joinable()) {
      worker_.join();
    }
  }

private:
  TaskId addTask(TimePoint timePoint, std::function<void()> callback) {
    std::lock_guard<std::mutex> lock(mutex_);
    TaskId id = nextId_++;
    Task task{id, timePoint, std::move(callback)};
    taskQueue_.push(task);
    taskMap_[id] = timePoint;
    cv_.notify_one();
    return id;
  }
  void run() {
    while (running_) {
      std::unique_lock<std::mutex> lock(mutex_);
      if (taskQueue_.empty()) {
        cv_.wait(lock);
        continue;
      }

      auto &task = taskQueue_.top();
      auto now = std::chrono::steady_clock::now();
      if (task.timePoint <= now) {
        auto callback = std::move(task.callback);
        taskMap_.erase(task.id);
        taskQueue_.pop();
        lock.unlock();
        callback();
      } else {
        cv_.wait_until(lock, task.timePoint);
      }
    }
  }
};

int main() {
  Timer timer;

  // 添加一个3秒后执行的任务
  auto taskId = timer.addOnceTask(std::chrono::seconds(3), []() {
    std::cout << "Task executed after 3 seconds!" << std::endl;
  });
  auto taskId2 = timer.addOnceTask(std::chrono::seconds(5), []() {
    std::cout << "Task executed after 5 seconds!" << std::endl;
  });
  auto taskId3 = timer.addOnceTask(std::chrono::seconds(7), []() {
    std::cout << "Task executed after 7 seconds!" << std::endl;
  });

  // 等待20秒停止
  std::this_thread::sleep_for(std::chrono::seconds(10));

  // 取消任务, 已经完成的任务下面的代码没有作用
  std::cout << timer.cancelTask(taskId) << std::endl;
  std::cout << timer.cancelTask(taskId2) << std::endl;
  std::cout << timer.cancelTask(taskId3) << std::endl;

  // 停止定时器
  timer.stop();
}