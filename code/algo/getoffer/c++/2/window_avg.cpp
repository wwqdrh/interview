#include <vector>

class MovingAverage {
public:
  MovingAverage(int size) : size(size), sum(0) {}

  double next(int val) {
    if (q.size() == size) {
      sum -= q.front();
      q.erase(q.begin());
    }
    sum += val;
    q.push_back(val);
    return static_cast<double>(sum) / q.size();
  }

private:
  int size;
  int sum;
  std::vector<int> q;
};
