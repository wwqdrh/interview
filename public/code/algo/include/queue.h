#include <deque>
#include <stdexcept>

void ExampleMonoQueue();

template <typename T> class MonotonicQueue {
private:
  std::deque<T> data_queue;
  std::deque<T> max_queue;
  std::deque<T> min_queue;

public:
  void push(T value) {
    data_queue.push_back(value);

    while (!max_queue.empty() && max_queue.back() < value) {
      max_queue.pop_back();
    }
    max_queue.push_back(value);

    while (!min_queue.empty() && min_queue.back() > value) {
      min_queue.pop_back();
    }
    min_queue.push_back(value);
  }

  void pop() {
    if (data_queue.empty())
      return;
    T value = data_queue.front();
    data_queue.pop_front();

    if (value == max_queue.front()) {
      max_queue.pop_front();
    }

    if (value == min_queue.front()) {
      min_queue.pop_front();
    }
  }

  T max() const {
    if (max_queue.empty())
      throw std::runtime_error("Max queue is empty");
    return max_queue.front();
  }

  T min() const {
    if (min_queue.empty())
      throw std::runtime_error("Min queue is empty");
    return min_queue.front();
  }
};