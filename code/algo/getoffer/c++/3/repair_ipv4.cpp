#include <string>
#include <vector>

using namespace std;

const int SEG_COUNT = 4;

vector<string> ans;
vector<int> segments(SEG_COUNT);

void dfs(const string &s, int segId, int segStart) {
  // If we have found 4 segments and traversed the entire string, it's a valid
  // IP address
  if (segId == SEG_COUNT) {
    if (segStart == s.size()) {
      string ipAddr;
      for (int i = 0; i < SEG_COUNT; ++i) {
        ipAddr += to_string(segments[i]);
        if (i != SEG_COUNT - 1) {
          ipAddr += ".";
        }
      }
      ans.push_back(ipAddr);
    }
    return;
  }

  // If we haven't found 4 segments but traversed the entire string, backtrack
  if (segStart == s.size()) {
    return;
  }

  // If the current number is 0, this segment can only be 0
  if (s[segStart] == '0') {
    segments[segId] = 0;
    dfs(s, segId + 1, segStart + 1);
    return;
  }

  // General case: enumerate each possibility and recurse
  int addr = 0;
  for (int segEnd = segStart; segEnd < s.size(); ++segEnd) {
    addr = addr * 10 + (s[segEnd] - '0');
    if (addr > 0 && addr <= 255) {
      segments[segId] = addr;
      dfs(s, segId + 1, segEnd + 1);
    } else {
      break;
    }
  }
}

vector<string> restoreIpAddresses(string s) {
  ans.clear();
  segments = vector<int>(SEG_COUNT);
  dfs(s, 0, 0);
  return ans;
}
