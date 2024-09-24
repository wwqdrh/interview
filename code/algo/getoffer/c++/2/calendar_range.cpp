#include <map>

class MyCalendar {
public:
  MyCalendar() {}

  bool book(int start, int end) {
    if (query(start, end - 1, 0, 1e9, 1)) {
      return false;
    }
    update(start, end - 1, 0, 1e9, 1);
    return true;
  }

private:
  std::map<int, bool> tree, lazy;

  bool query(int start, int end, int l, int r, int idx) {
    if (r < start || end < l) {
      return false;
    }
    if (lazy[idx]) { // If the interval is already booked, return true
      return true;
    }
    if (start <= l && r <= end) {
      return tree[idx];
    }
    int mid = (l + r) >> 1;
    return query(start, end, l, mid, 2 * idx) ||
           query(start, end, mid + 1, r, 2 * idx + 1);
  }

  void update(int start, int end, int l, int r, int idx) {
    if (r < start || end < l) {
      return;
    }
    if (start <= l && r <= end) {
      tree[idx] = true;
      lazy[idx] = true;
    } else {
      int mid = (l + r) >> 1;
      update(start, end, l, mid, 2 * idx);
      update(start, end, mid + 1, r, 2 * idx + 1);
      tree[idx] = true;
      if (lazy[2 * idx] && lazy[2 * idx + 1]) {
        lazy[idx] = true;
      }
    }
  }
};
