#include <iostream>
#include <vector>
using namespace std;

int singleNumber(const vector<int>& nums) {
    int ans = 0;  // 32位整数，保存结果
    for (int i = 0; i < 32; ++i) {
        int total = 0;  // 记录第i位的1的个数
        for (int num : nums) {
            total += (num >> i) & 1;  // 取出num的第i位并累加
        }
        if (total % 3 > 0) {  // 如果该位上的1的个数不是3的倍数
            ans |= (1 << i);  // 将该位设置为1
        }
    }
    return ans;
}

int main() {
    vector<int> nums = { 1,1,1,2,2,2,3,3,3,4 };
    int ans = singleNumber(nums);
    cout << ans << endl;
    return 0;
}