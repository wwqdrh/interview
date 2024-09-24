#include <vector>

std::vector<int> asteroidCollision(const std::vector<int> &asteroids) {
  std::vector<int> st;
  for (int aster : asteroids) {
    bool alive = true;
    while (alive && aster < 0 && !st.empty() && st.back() > 0) {
      alive = st.back() < -aster; // Check if the current asteroid survives
      if (st.back() <= -aster) {  // Top of the stack asteroid explodes
        st.pop_back();
      }
    }
    if (alive) {
      st.push_back(aster);
    }
  }
  return st;
}
