# 剑指offer

> 题库链接: https://leetcode.cn/problem-list/e8X3pBZi/

## 整数除法

`剑指 Offer II 001. 整数除法`

给定整数a、b，求得商的结果

条件:

1、不能使用除法、取余数等运算
2、只能存储32位有符号整数(范围是[-2^31,2^31-1])，如果溢出了就返回`2^31-1`

`解法`

- 处理边界条件，当a是最小值，判断b是1或者-1；当b是最小值，a是最小值则为1，其他都为0
- 使用二分法+快速乘来判断是否满足

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/intdevide.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/intdevide.go}}
<<<<<
```

## 2、

`剑指 Offer II 002. 二进制加法`

给定两个01字符串，求得加法字符串

`解法`

- 相对应下标(len-i-1)不断相加，计算商继续作为carry、模作为当前下标的值。

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/bstradd.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/bstradd.go}}
<<<<<
```

## 3、

`剑指 Offer II 003. 前 n 个数字二进制中 1 的个数`

给定一个数字n，从[0,n]中计算出二进制表示中1的个数

`解法`

- 计算一个数的二进制表示中有多少个1，`x>0`的循环条件中，能有多少次`x&=x-1`满足条件


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/bitcount.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/bitcount.go}}
<<<<<
```

## 4、

`剑指 Offer II 004. 只出现一次的数字`

给定一个整数数组，其中一个元素出现了一次，其他元素出现了三次，找到那个只出现了一次的元素

要求: `O(n)`时间复杂度, `O(1)`空间复杂度

`解法`

- 将数组中的数字看成二进制格式，对于出现了三次的数字，他们对应的比特位数字和为0或者3，对于出现一次的数字，对应的比特位数字和为1或者4，将每一位的和取余所得到的余数就是结果对应的元素对应的位置。


```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/foundonetime.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/foundonetime.go}}
<<<<<
```


## 5、

`剑指 Offer II 005. 单词长度的最大乘积`

一个字符串数组，寻找满足 不包含相同字符 的两个字符串的长度乘积，找到满足条件的最大长度

`解法`

- 将字符串转为int类型mask来表示哪些字母是出现了的
- 使用位运算来判断是否存在相同的字符

```multicode
>>>>> cpp
{{#include ../../../code/algo/getoffer/c++/unistr_maxlen.cpp}}
<<<<<
>>>>> go
{{#include ../../../code/algo/getoffer/go/unistr_maxlen.go}}
<<<<<
```

## 6、

`剑指 Offer II 006. 排序数组中两个数字之和`

一个升序数组，找到其中的两个元素和为目标值，返回其目标下标。同一个数字不能使用两次，并且题目要求一定会存在满足条件的答案。

```go
func twoSum(numbers []int, target int) []int {
    low, high := 0, len(numbers) - 1
    for low < high {
        sum := numbers[low] + numbers[high]
        if sum == target {
            return []int{low, high}
        } else if sum < target {
            low++
        } else {
            high--
        }
    }
    return []int{-1, -1}
}
```

## 7、

`剑指 Offer II 007. 数组中和为 0 的三个数`

给定一个整数数组，返回其中和为0的三元组，并且需要答案不能重复

`解法`

- 先进行排序，优化搜索条件
- 记得跳过相同的值，即相同的一段，只计算第一个进行剪枝。

```go
func threeSum(nums []int) [][]int {
    n := len(nums)
    sort.Ints(nums)
    ans := make([][]int, 0)
 
    // 枚举 a
    for first := 0; first < n; first++ {
        // 需要和上一次枚举的数不相同
        if first > 0 && nums[first] == nums[first - 1] {
            continue
        }
        // c 对应的指针初始指向数组的最右端
        third := n - 1
        target := -1 * nums[first]
        // 枚举 b
        for second := first + 1; second < n; second++ {
            // 需要和上一次枚举的数不相同
            if second > first + 1 && nums[second] == nums[second - 1] {
                continue
            }
            // 需要保证 b 的指针在 c 的指针的左侧
            for second < third && nums[second] + nums[third] > target {
                third--
            }
            // 如果指针重合，随着 b 后续的增加
            // 就不会有满足 a+b+c=0 并且 b<c 的 c 了，可以退出循环
            if second == third {
                break
            }
            if nums[second] + nums[third] == target {
                ans = append(ans, []int{nums[first], nums[second], nums[third]})
            }
        }
    }
    return ans
}
```

## 8、

`剑指 Offer II 008. 和大于等于 target 的最短子数组`

给定一个整数数组，寻找满足数组和大于target的一个最短连续子数组

`解法`

- 滑动窗口: 计算满足和大于目标值的最短子数组长度

```go
func minSubArrayLen(s int, nums []int) int {
    n := len(nums)
    if n == 0 {
        return 0
    }
    ans := math.MaxInt32
    start, end := 0, 0
    sum := 0
    for end < n {
        sum += nums[end]
        for sum >= s {
            ans = min(ans, end - start + 1)
            sum -= nums[start]
            start++
        }
        end++
    }
    if ans == math.MaxInt32 {
        return 0
    }
    return ans
}

func min(x, y int) int {
    if x < y {
        return x
    }
    return y
}
```

## 9、

`剑指 Offer II 009. 乘积小于 K 的子数组`

给定一个数组，寻找其中满足数组乘积小于k的子数组的个数

```go
func numSubarrayProductLessThanK(nums []int, k int) (ans int) {
    prod, i := 1, 0
    for j, num := range nums {
        prod *= num
        for ; i <= j && prod >= k; i++ {
            prod /= nums[i]
        }
        ans += j - i + 1
    }
    return
}
```

## 10、

`剑指 Offer II 010. 和为 k 的子数组`

给定一个数组，寻找其中满足数组和为k的子数组的个数

`解法`

- 数组和在计算过程中需要记录下来，并且同时计算该数组和对应的个数

```go
func subarraySum(nums []int, k int) int {
    count, pre := 0, 0
    m := map[int]int{}
    m[0] = 1
    for i := 0; i < len(nums); i++ {
        pre += nums[i]
        if _, ok := m[pre - k]; ok {
            count += m[pre - k]
        }
        m[pre] += 1
    }
    return count
} 
```

## 11、

`剑指 Offer II 011. 0 和 1 个数相同的子数组`

给定一个只包含0和1的数组，找到其中含有相同`0和1`数量的最大长度的子数组

`解法`

- 使用map记录某个前缀和最左边的下标是多少

```go
func findMaxLength(nums []int) (maxLength int) {
    mp := map[int]int{0: -1}
    counter := 0
    for i, num := range nums {
        if num == 1 {
            counter++
        } else {
            counter--
        }
        if prevIndex, has := mp[counter]; has {
            maxLength = max(maxLength, i-prevIndex)
        } else {
            mp[counter] = i
        }
    }
    return
}

func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}
```

## 12、

`剑指 Offer II 012. 左右两边子数组的和相等`

找到数组的最左边的中心下标，中心下标是指以该下标为分界，左右数组元素和相同的下标

`解法`

- 判断`2 * 前缀和 + 当前值`是否等于数组总和

```go
func pivotIndex(nums []int) int {
    total := 0
    for _, v := range nums {
        total += v
    }
    sum := 0
    for i, v := range nums {
        if 2*sum+v == total {
            return i
        }
        sum += v
    }
    return -1
}
```

## 13、

`剑指 Offer II 013. 二维子矩阵的和`

给定一个二维矩阵，提供多次查询，计算子矩阵的和

`解法`

- 预处理(0,0)到(i,j)的子数组的和

```go
type NumMatrix struct {
    sums [][]int
}

func Constructor(matrix [][]int) NumMatrix {
    m := len(matrix)
    if m == 0 {
        return NumMatrix{}
    }
    n := len(matrix[0])
    sums := make([][]int, m+1)
    sums[0] = make([]int, n+1)
    for i, row := range matrix {
        sums[i+1] = make([]int, n+1)
        for j, v := range row {
            sums[i+1][j+1] = sums[i+1][j] + sums[i][j+1] - sums[i][j] + v
        }
    }
    return NumMatrix{sums}
}

func (nm *NumMatrix) SumRegion(row1, col1, row2, col2 int) int {
    return nm.sums[row2+1][col2+1] - nm.sums[row1][col2+1] - nm.sums[row2+1][col1] + nm.sums[row1][col1]
}
```

## 14、

`剑指 Offer II 014. 字符串中的变位词`

给定两个字符串，判断字符串的排列之一是否是另一个字符串的子串

`解法`

- 使用26长度的数组来保存字符情况

```go
func checkInclusion(s1, s2 string) bool {
    n, m := len(s1), len(s2)
    if n > m {
        return false
    }
    cnt := [26]int{}
    for _, ch := range s1 {
        cnt[ch-'a']--
    }
    left := 0
    for right, ch := range s2 {
        x := ch - 'a'
        cnt[x]++
        for cnt[x] > 0 {
            cnt[s2[left]-'a']--
            left++
        }
        if right-left+1 == n {
            return true
        }
    }
    return false
}
```

## 15、

`剑指 Offer II 015. 字符串中的所有变位词`

给定两个字符串，返回一个子串的所有变位形式判断在另一个字符串中是子串的话，就返回其起始下标

`解法`

- 26位长度数组
- 滑动窗口

```go
func findAnagrams(s, p string) (ans []int) {
    sLen, pLen := len(s), len(p)
    if sLen < pLen {
        return
    }

    var sCount, pCount [26]int
    for i, ch := range p {
        sCount[s[i]-'a']++
        pCount[ch-'a']++
    }
    if sCount == pCount {
        ans = append(ans, 0)
    }

    for i, ch := range s[:sLen-pLen] {
        sCount[ch-'a']--
        sCount[s[i+pLen]-'a']++
        if sCount == pCount {
            ans = append(ans, i+1)
        }
    }
    return
}
```

## 16、

`剑指 Offer II 016. 不含重复字符的最长子字符串`

给定一个字符串，返回不包含重复字符的最长子字符串长度

`解法`

- 滑动窗口，记录在窗口中字符的个数

```go
func lengthOfLongestSubstring(s string) int {
    // 哈希集合，记录每个字符是否出现过
    m := map[byte]int{}
    n := len(s)
    // 右指针，初始值为 -1，相当于我们在字符串的左边界的左侧，还没有开始移动
    rk, ans := -1, 0
    for i := 0; i < n; i++ {
        if i != 0 {
            // 左指针向右移动一格，移除一个字符
            delete(m, s[i-1])
        }
        for rk + 1 < n && m[s[rk+1]] == 0 {
            // 不断地移动右指针
            m[s[rk+1]]++
            rk++
        }
        // 第 i 到 rk 个字符是一个极长的无重复字符子串
        ans = max(ans, rk - i + 1)
    }
    return ans
}

func max(x, y int) int {
    if x < y {
        return y
    }
    return x
}
```

## 17、

`剑指 Offer II 017. 含有所有字符的最短字符串`

给定两个字符串s和t，找到s中的一个最短字符串，包含t的所有字符，如果不存在这样的子字符串，则返回空字符串

```go
func minWindow(s string, t string) string {
    ori, cnt := map[byte]int{}, map[byte]int{}
    for i := 0; i < len(t); i++ {
        ori[t[i]]++
    }

    sLen := len(s)
    len := math.MaxInt32
    ansL, ansR := -1, -1

    check := func() bool {
        for k, v := range ori {
            if cnt[k] < v {
                return false
            }
        }
        return true
    }
    for l, r := 0, 0; r < sLen; r++ {
        if r < sLen && ori[s[r]] > 0 {
            cnt[s[r]]++
        }
        for check() && l <= r {
            if (r - l + 1 < len) {
                len = r - l + 1
                ansL, ansR = l, l + len
            }
            if _, ok := ori[s[l]]; ok {
                cnt[s[l]] -= 1
            }
            l++
        }
    }
    if ansL == -1 {
        return ""
    }
    return s[ansL:ansR]
}
```

## 18、

`剑指 Offer II 018. 有效的回文`

给定一个字符串，验证是否是回文字符串, 只考虑字母和数字字符，可以忽略字母的大小写。

```go
func isPalindrome(s string) bool {
    var sgood string
    for i := 0; i < len(s); i++ {
        if isalnum(s[i]) {
            sgood += string(s[i])
        }
    }

    n := len(sgood)
    sgood = strings.ToLower(sgood)
    for i := 0; i < n/2; i++ {
        if sgood[i] != sgood[n-1-i] {
            return false
        }
    }
    return true
}

func isalnum(ch byte) bool {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')
}
```

## 19、

`剑指 Offer II 019. 最多删除一个字符得到回文`

给定一个字符串，删除其中一个字符判断是否是回文

```go
func validPalindrome(s string) bool {
    low, high := 0, len(s) - 1
    for low < high {
        if s[low] == s[high] {
            low++
            high--
        } else {
            flag1, flag2 := true, true
            for i, j := low, high - 1; i < j; i, j = i + 1, j - 1 {
                if s[i] != s[j] {
                    flag1 = false
                    break
                }
            }
            for i, j := low + 1, high; i < j; i, j = i + 1, j - 1 {
                if s[i] != s[j] {
                    flag2 = false
                    break
                }
            }
            return flag1 || flag2
        }
    }
    return true
}
```

## 20、

`剑指 Offer II 020. 回文子字符串的个数`

计算一个字符串中有多少个回文子字符串

```go
func countSubstrings(s string) int {
    n := len(s)
    ans := 0
    for i := 0; i < 2 * n - 1; i++ {
        l, r := i / 2, i / 2 + i % 2
        for l >= 0 && r < n && s[l] == s[r] {
            l--
            r++
            ans++
        }
    }
    return ans
}
```

## 21、

`剑指 Offer II 021. 删除链表的倒数第 n 个结点`

给定一个链表，删除链表的倒数第n个节点，并且返回头节点

`解法`

- 快慢指针

```go
func removeNthFromEnd(head *ListNode, n int) *ListNode {
    dummy := &ListNode{0, head}
    first, second := head, dummy
    for i := 0; i < n; i++ {
        first = first.Next
    }
    for ; first != nil; first = first.Next {
        second = second.Next
    }
    second.Next = second.Next.Next
    return dummy.Next
}
```

## 22、

`剑指 Offer II 022. 链表中环的入口节点`

给定一个数组形式的链表，数组中每个元素对应着下一个节点的下标，如果该链表没有环，就返回-1，如果有环，则返回环入口的下标

`解法`

- 快慢指针，当相遇了之后从当前以及初始位置以相同速度前进，当再次相遇就是环的入口

```go
func detectCycle(head *ListNode) *ListNode {
    slow, fast := head, head
    for fast != nil {
        slow = slow.Next
        if fast.Next == nil {
            return nil
        }
        fast = fast.Next.Next
        if fast == slow {
            p := head
            for p != slow {
                p = p.Next
                slow = slow.Next
            }
            return p
        }
    }
    return nil
}
```

## 23、

`剑指 Offer II 023. 两个链表的第一个重合节点`

给定两个链表，题目保证该链式结构没有环，找到该两个链表的相交节点，如果不存在相交节点，就返回空

`解法`

- 链表走完了之后到另外一个上，这样到达相交节点的节点数相同，是会相遇的

```go
func getIntersectionNode(headA, headB *ListNode) *ListNode {
    if headA == nil || headB == nil {
        return nil
    }
    pa, pb := headA, headB
    for pa != pb {
        if pa == nil {
            pa = headB
        } else {
            pa = pa.Next
        }
        if pb == nil {
            pb = headA
        } else {
            pb = pb.Next
        }
    }
    return pa
}
```

## 24、

`剑指 Offer II 024. 反转链表`

给定一个链式结构，反转后返回其头节点

```go
func reverseList(head *ListNode) *ListNode {
    if head == nil || head.Next == nil {
        return head
    }
    newHead := reverseList(head.Next)
    head.Next.Next = head
    head.Next = nil
    return newHead
}
```

## 25、

`剑指 Offer II 025. 链表中的两数相加`

使用两个链表表示非负整数，尾节点为个位数，返回两个链表的相加结果，并以链表形式返回

`解法`

- 将链表转为数组，然后计算完后进行重新构造成链表

```go
func addTwoNumbers(l1 *ListNode, l2 *ListNode) (head *ListNode) {
    var s1, s2 []int
    for l1 != nil{
        s1 = append(s1, l1.Val)
        l1 = l1.Next
    }
    for l2 != nil{
        s2 = append(s2, l2.Val)
        l2 = l2.Next
    }
    carry := 0
    for len(s1) > 0 || len(s2) > 0 || carry > 0{
        sum := 0
        if len(s1) > 0{
            sum += s1[len(s1)-1]
            s1 = s1[:len(s1)-1]
        }
        if len(s2) > 0{
            sum += s2[len(s2)-1]
            s2 = s2[:len(s2)-1]
        }
        sum += carry
        node := &ListNode{Val:sum%10}
        node.Next = head
        head = node
        carry = sum / 10
    }
    return
}
```

## 26、

`剑指 Offer II 026. 重排链表`

给定一个链表结构，原始为'1 2 3 4 5 6 ... n-1 n' 修改为'1 n 2 n-1 3 n-2 ...'

```go
func reorderList(head *ListNode) {
    if head == nil {
        return
    }
    nodes := []*ListNode{}
    for node := head; node != nil; node = node.Next {
        nodes = append(nodes, node)
    }
    i, j := 0, len(nodes)-1
    for i < j {
        nodes[i].Next = nodes[j]
        i++
        if i == j {
            break
        }
        nodes[j].Next = nodes[i]
        j--
    }
    nodes[i].Next = nil
}
```

## 27、

`剑指 Offer II 027. 回文链表`

给定一个链表结构，判断该链表是否是回文

```go
func isPalindrome(head *ListNode) bool {
    vals := []int{}
    for ; head != nil; head = head.Next {
        vals = append(vals, head.Val)
    }
    n := len(vals)
    for i, v := range vals[:n/2] {
        if v != vals[n-1-i] {
            return false
        }
    }
    return true
}
```

## 28、

`剑指 Offer II 028. 展平多级双向链表`

将多级双向链表展平

这里多级双向链表就是包含前后指针，还包含子链表的指针，(其实就相当于链表)

```go
func dfs(node *Node) (last *Node) {
    cur := node
    for cur != nil {
        next := cur.Next
        // 如果有子节点，那么首先处理子节点
        if cur.Child != nil {
            childLast := dfs(cur.Child)

            next = cur.Next
            // 将 node 与 child 相连
            cur.Next = cur.Child
            cur.Child.Prev = cur

            // 如果 next 不为空，就将 last 与 next 相连
            if next != nil {
                childLast.Next = next
                next.Prev = childLast
            }

            // 将 child 置为空
            cur.Child = nil
            last = childLast
        } else {
            last = cur
        }
        cur = next
    }
    return
}

func flatten(root *Node) *Node {
    dfs(root)
    return root
}
```

## 29、

`剑指 Offer II 029. 排序的循环链表`

给定一个循环链表，它的值是单调非递减的，提供一个元素插入的方法，使得元素插入之后值依然是单调非递减的

`解法`

- 第一种情况 `cur.val <= val <= next.val`, 直接插入到这里
- 第二种情况 `cur.val > next.val`, 说明是链表遍历完了，break，直接加入到cur的后面

```go
func insert(head *Node, insertVal int) *Node {
    node := &Node{Val: insertVal}
    if head == nil {
        node.Next = node
        return node
    }
    if head.Next == head {
        head.Next = node
        node.Next = head
        return head
    }
    curr, next := head, head.Next
    for next != head {
        if insertVal >= curr.Val && insertVal <= next.Val {
            break
        }
        if curr.Val > next.Val {
            if insertVal > curr.Val || insertVal < next.Val {
                break
            }
        }
        curr = curr.Next
        next = next.Next
    }
    curr.Next = node
    node.Next = next
    return head
}
```

## 30、

`剑指 Offer II 030. 插入、删除和随机访问都是 O(1) 的容器`

创造一个数据结构，它的插入、删除、随机访问都是O(1)时间复杂度

`解法`

- 由于需要随机访问，所以将数据存储到数组中，通过对下标进行随机来进行访问
- 插入和删除也需要O(1), 使用map来存储值与下标
- 当删除的时候，将末尾的一个移动到要删除的位置并且更新下对应下标，然后数组只需要减一个长度即可

```go
type RandomizedSet struct {
    nums    []int
    indices map[int]int
}

func Constructor() RandomizedSet {
    return RandomizedSet{
        []int{}, map[int]int{},
    }
}

func (rs *RandomizedSet) Insert(val int) bool {
    if _, ok := rs.indices[val]; ok {
        return false
    }
    rs.indices[val] = len(rs.nums)
    rs.nums = append(rs.nums, val)
    return true
}

func (rs *RandomizedSet) Remove(val int) bool {
    id, ok := rs.indices[val]
    if !ok {
        return false
    }
    last := len(rs.nums) - 1
    rs.nums[id] = rs.nums[last]
    rs.indices[rs.nums[id]] = id
    rs.nums = rs.nums[:last]
    delete(rs.indices, val)
    return true
}

func (rs *RandomizedSet) GetRandom() int {
    return rs.nums[rand.Intn(len(rs.nums))]
}
```
