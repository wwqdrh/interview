#include "queue.h"
#include <iostream>

void ExampleMonoQueue() {
  MonotonicQueue<int> q;
  q.push(5);
  q.push(6);
  q.push(2);

  std::cout << q.max() << std::endl;
  std::cout << q.min() << std::endl;

  q.pop();
  q.pop();
  
  std::cout << q.max() << std::endl;
  std::cout << q.min() << std::endl;
}