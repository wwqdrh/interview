#include <algorithm>
#include <vector>

int minEatingSpeed(const std::vector<int> &piles, int h) {
  int maxPile = *std::max_element(piles.begin(), piles.end());
  return 1 + std::lower_bound(1, maxPile - 1, [&](int speed) -> bool {
           int time = 0;
           for (int pile : piles) {
             time += (pile + speed - 1) / speed;
           }
           return time <= h;
         });
}
