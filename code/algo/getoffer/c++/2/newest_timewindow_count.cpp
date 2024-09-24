#include <deque>

class RecentCounter {
public:
  RecentCounter() {}

  int ping(int t) {
    q.push_back(t);
    while (q.front() < t - 3000) {
      q.pop_front();
    }
    return q.size();
  }

private:
  std::deque<int> q;
};
