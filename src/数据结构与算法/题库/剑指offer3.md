## 61、

`剑指 Offer II 061. 和最小的 k 个数对`

给定两个升序数组，找到前n小的数对

```go
func kSmallestPairs(nums1, nums2 []int, k int) (ans [][]int) {
    h := hp{nums1: nums1, nums2: nums2}
    m, n := len(nums1), len(nums2)
    for i := 0; i < k && i < m; i++ {
        heap.Push(&h, pair{i, 0})
    }
    for h.Len() > 0 && len(ans) < k {
        p := heap.Pop(&h).(pair)
        i, j := p.i, p.j
        ans = append(ans, []int{nums1[i], nums2[j]})
        if j + 1 < n {
            heap.Push(&h, pair{i, j+1})
        }
    }
    return
}

type hp struct{
    data []pair
    nums1, nums2 []int
}

type pair struct{
    i, j int
}

func (h hp) Len() int {
    return len(h.data)
}

func (h hp) Less(i, j int) bool {
    p1, p2 := h.data[i], h.data[j]
    return h.nums1[p1.i] + h.nums2[p1.j] < h.nums1[p2.i] + h.nums2[p2.j]
}

func (h hp) Swap(i, j int) {
    h.data[i], h.data[j] = h.data[j], h.data[i]
}

func (h *hp) Push(val interface{}) {
    h.data = append(h.data, val.(pair))
}

func (h *hp) Pop() interface{} {
    data := h.data
    val := data[len(data)-1]
    h.data = data[:len(data)-1]
    return val
}
```

## 62、

`剑指 Offer II 062. 实现前缀树`

设计一个前缀树，提供数据插入，数据搜索，判断是否存在某个前缀

```go
type Trie struct {
    children [26]*Trie
    isEnd    bool
}

func Constructor() Trie {
    return Trie{}
}

func (t *Trie) Insert(word string) {
    node := t
    for _, ch := range word {
        ch -= 'a'
        if node.children[ch] == nil {
            node.children[ch] = &Trie{}
        }
        node = node.children[ch]
    }
    node.isEnd = true
}

func (t *Trie) SearchPrefix(prefix string) *Trie {
    node := t
    for _, ch := range prefix {
        ch -= 'a'
        if node.children[ch] == nil {
            return nil
        }
        node = node.children[ch]
    }
    return node
}

func (t *Trie) Search(word string) bool {
    node := t.SearchPrefix(word)
    return node != nil && node.isEnd
}

func (t *Trie) StartsWith(prefix string) bool {
    return t.SearchPrefix(prefix) != nil
}
```

## 63、

`剑指 Offer II 063. 替换单词`

当一个词为另一个词的前缀那么称其为词根，后者称为继承词

给定一个词根数组，一个句子，将句子中的所有词语，如果存在其词根，那么就用词根进行替换

```go
func replaceWords(dictionary []string, sentence string) string {
    type trie map[rune]trie
    root := trie{}
    for _, s := range dictionary {
        cur := root
        for _, c := range s {
            if cur[c] == nil {
                cur[c] = trie{}
            }
            cur = cur[c]
        }
        cur['#'] = trie{}
    }

    words := strings.Split(sentence, " ")
    for i, word := range words {
        cur := root
        for j, c := range word {
            if cur['#'] != nil {
                words[i] = word[:j]
                break
            }
            if cur[c] == nil {
                break
            }
            cur = cur[c]
        }
    }
    return strings.Join(words, " ")
}
```

## 64、

`剑指 Offer II 064. 神奇的字典`

一个初始字符串列表，提供一个搜索方法，判断需要搜索的字符串进行一次字符替换后是否出现在初始字符串列表。

```go
type MagicDictionary struct {
    trie *trie
}

type trie struct{
    children [26]*trie
    isEnd bool
}

/** Initialize your data structure here. */
func Constructor() MagicDictionary {
    return MagicDictionary{trie: &trie{}}
}


func (this *MagicDictionary) BuildDict(dictionary []string)  {
    for _, word := range dictionary {
        cur := this.trie
        for _, ch := range word {
            idx := ch - 'a'
            if cur.children[idx] == nil {
                cur.children[idx] = &trie{}
            }
            cur = cur.children[idx]
        }
        cur.isEnd = true
    }
}


func (this *MagicDictionary) Search(searchWord string) bool {
    var dfs func(node *trie, searchWord string, modified bool) bool
    dfs = func(node *trie, searchWord string, modified bool) bool {
        if searchWord == "" {
            return modified && node.isEnd
        }
        c := searchWord[0] - 'a'
        if node.children[c] != nil && dfs(node.children[c], searchWord[1:], modified) {
            return true
        }
        if !modified {
            for i, child := range node.children {
                if i != int(c) && child != nil && dfs(child, searchWord[1:], true) {
                    return true
                }
            }
        }
        return false
    }
    return dfs(this.trie, searchWord, false)
}
```

## 65、

`剑指 Offer II 065. 最短的单词编码`

> 暂时没理解到含义，详情查看https://leetcode.cn/problems/iSwD2y/?favorite=e8X3pBZi

```go

type Trie struct {
	child [26]*Trie
	depth int
}

func Constructor() *Trie {
	return &Trie{
		child: [26]*Trie{},
		depth: 1,
	}
}

func (t *Trie) Insert(word string) {
	curr := t
	n := len(word)
	for i := n - 1; i >= 0; i-- {
		c := word[i] - 'a'
		if curr.child[c] == nil {
			curr.child[c] = Constructor()
		}
		curr.child[c].depth = curr.depth + 1
		curr = curr.child[c]
	}
}

func minimumLengthEncoding(words []string) int {
	t := Constructor()
	for _, w := range words {
		t.Insert(w)
	}
	var res int
	var dfs func(node *Trie)
	dfs = func(node *Trie) {
		var hasChild bool
		for i := 0; i < 26; i++ {
			if node.child[i] != nil {
				hasChild = true
				dfs(node.child[i])
			}
		}
		if !hasChild {
			res += node.depth
		}
	}
	dfs(t)
	return res
}
```

## 66、

`剑指 Offer II 066. 单词之和`

提供两个方法，插入字符串以及个数，查询一个前缀所包含的值的大小。

如果该key已经存在则进行替换，给定一个字符串查询以该字符串为前缀的元素总和

```go
type TrieNode struct {
    children [26]*TrieNode
    val      int
}

type MapSum struct {
    root *TrieNode
    cnt  map[string]int
}

func Constructor() MapSum {
    return MapSum{
        &TrieNode{}, 
        map[string]int{},
    }
}

func (m *MapSum) Insert(key string, val int) {
    delta := val
    if m.cnt[key] > 0 {
        delta -= m.cnt[key]
    }
    m.cnt[key] = val
    node := m.root
    for _, ch := range key {
        ch -= 'a'
        if node.children[ch] == nil {
            node.children[ch] = &TrieNode{}
        }
        node = node.children[ch]
        node.val += delta
    }
}

func (m *MapSum) Sum(prefix string) int {
    node := m.root
    for _, ch := range prefix {
        ch -= 'a'
        if node.children[ch] == nil {
            return 0
        }
        node = node.children[ch]
    }
    return node.val
}
```

## 67、

`剑指 Offer II 067. 最大的异或`

给定一个整数数组，两两元素进行异或，找到最大值

```go
const highBit = 30

type trie struct {
    left, right *trie
}

func (t *trie) add(num int) {
    cur := t
    for i := highBit; i >= 0; i-- {
        bit := num >> i & 1
        if bit == 0 {
            if cur.left == nil {
                cur.left = &trie{}
            }
            cur = cur.left
        } else {
            if cur.right == nil {
                cur.right = &trie{}
            }
            cur = cur.right
        }
    }
}

func (t *trie) check(num int) (x int) {
    cur := t
    for i := highBit; i >= 0; i-- {
        bit := num >> i & 1
        if bit == 0 {
            // a_i 的第 k 个二进制位为 0，应当往表示 1 的子节点 right 走
            if cur.right != nil {
                cur = cur.right
                x = x*2 + 1
            } else {
                cur = cur.left
                x = x * 2
            }
        } else {
            // a_i 的第 k 个二进制位为 1，应当往表示 0 的子节点 left 走
            if cur.left != nil {
                cur = cur.left
                x = x*2 + 1
            } else {
                cur = cur.right
                x = x * 2
            }
        }
    }
    return
}

func findMaximumXOR(nums []int) (x int) {
    root := &trie{}
    for i := 1; i < len(nums); i++ {
        // 将 nums[i-1] 放入字典树，此时 nums[0 .. i-1] 都在字典树中
        root.add(nums[i-1])
        // 将 nums[i] 看作 ai，找出最大的 x 更新答案
        x = max(x, root.check(nums[i]))
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

## 68、

`剑指 Offer II 068. 查找插入位置`

往一个有序数组中进行数据插入，查找数据的插入位置，要求使用O(logn)复杂度

```go
func searchInsert(nums []int, target int) int {
    n := len(nums)
    left, right := 0, n - 1
    ans := n
    for left <= right {
        mid := (right - left) >> 1 + left
        if target <= nums[mid] {
            ans = mid
            right = mid - 1
        } else {
            left = mid + 1
        }
    }
    return ans
}
```

## 69、

`剑指 Offer II 069. 山峰数组的顶部`

找到下标i，在i之前是递增数据，在i之后是递减数据

题目保证满足存在这样的i

```go
func peakIndexInMountainArray(arr []int) int {
    return sort.Search(len(arr)-1, func(i int) bool { return arr[i] > arr[i+1] })
}
```

## 70、

剑指 Offer II 070. 排序数组中只出现一次的数字

一个有序数组，有一个元素只出现一次，其他元素出现了两次，找到这个只出现了一次的元素，满足O(logn)时间复杂度，O(1)空间复杂度

```go
func singleNonDuplicate(nums []int) int {
    low, high := 0, len(nums)-1
    for low < high {
        mid := low + (high-low)/2
        if nums[mid] == nums[mid^1] {
            low = mid + 1
        } else {
            high = mid
        }
    }
    return nums[low]
}
```

## 71、

`剑指 Offer II 071. 按权重生成随机数`

按照值的大小作为权重占比进行随机数获取，返回其数据下标

```go
type Solution struct {
    pre []int
}

func Constructor(w []int) Solution {
    for i := 1; i < len(w); i++ {
        w[i] += w[i-1]
    }
    return Solution{w}
}

func (s *Solution) PickIndex() int {
    x := rand.Intn(s.pre[len(s.pre)-1]) + 1
    return sort.SearchInts(s.pre, x)
}
```

## 72、

`剑指 Offer II 072. 求平方根`

计算一个整数的开平方根，只取正数那一个

```go
func mySqrt(x int) int {
    l, r := 0, x
    ans := -1
    for l <= r {
        mid := l + (r - l) / 2
        if mid * mid <= x {
            ans = mid
            l = mid + 1
        } else {
            r = mid - 1
        }
    }
    return ans
}
```

## 73、

`剑指 Offer II 073. 狒狒吃香蕉`

n堆香蕉，在h小时内要吃完，选择要吃完所有香蕉的最小速度，不过需要注意如果选择了一堆香蕉后，小于k个也会等待下一个小时才会继续吃。

```go
func minEatingSpeed(piles []int, h int) int {
    max := 0
    for _, pile := range piles {
        if pile > max {
            max = pile
        }
    }
    return 1 + sort.Search(max-1, func(speed int) bool {
        speed++
        time := 0
        for _, pile := range piles {
            time += (pile + speed - 1) / speed
        }
        return time <= h
    })
}
```

## 74、

`剑指 Offer II 074. 合并区间`

给定一个元组数组，其中的元素即为一个左右区间，将所有重叠的区间进行合并，并返回一个不重叠的区间数组

```go
func merge(intervals [][]int) [][]int {
	sort.Slice(intervals, func(i, j int) bool {
		return intervals[i][0] < intervals[j][0] || (intervals[i][0] == intervals[j][0] && intervals[i][1] < intervals[j][1])
	})
	var res [][]int
	for _, interval := range intervals {
		if len(res) == 0 || res[len(res)-1][1] < interval[0] {
			res = append(res, interval)
		} else {
			res[len(res)-1][1] = max(res[len(res)-1][1], interval[1])
		}
	}
	return res
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}
```

## 75

`剑指 Offer II 075. 数组相对排序`

给定两个数组arr1和arr2，将arr1按照arr2的顺序进行排序，未出现过的就按照升序之后放在arr1的末尾。

```go
type zset map[int]int

func(zs *zset) keys() []int {
    res := []int{}
    for key := range *zs {
        res = append(res, key)
    }
    sort.Ints(res)
    return res
}

func relativeSortArray(arr1 []int, arr2 []int) []int {
    zs := zset{}
    for _, val := range arr1 {
        zs[val]++
    }

    res := make([]int, 0, len(arr1))
    for _, val := range arr2 {
        for i := 0; i < zs[val]; i++ {
            res = append(res, val)
        }
        delete(zs, val)
    }
    for _, key := range zs.keys() {
        for i := 0; i < zs[key]; i++ {
            res = append(res, key)
        }
    }
    return res
}
```

## 76

`剑指 Offer II 076. 数组中的第 k 大的数字`

给定一个整数数组和整数，返回数组中第k个最大的元素

```go
func findKthLargest(nums []int, k int) int {
    rand.Seed(time.Now().UnixNano())
    return quickSelect(nums, 0, len(nums)-1, len(nums)-k)
}

func quickSelect(a []int, l, r, index int) int {
    q := randomPartition(a, l, r)
    if q == index {
        return a[q]
    } else if q < index {
        return quickSelect(a, q + 1, r, index)
    }
    return quickSelect(a, l, q - 1, index)
}

func randomPartition(a []int, l, r int) int {
    i := rand.Int() % (r - l + 1) + l
    a[i], a[r] = a[r], a[i]
    return partition(a, l, r)
}

func partition(a []int, l, r int) int {
    x := a[r]
    i := l - 1
    for j := l; j < r; j++ {
        if a[j] <= x {
            i++
            a[i], a[j] = a[j], a[i]
        }
    }
    a[i+1], a[r] = a[r], a[i+1]
    return i + 1
}
```

## 77

`剑指 Offer II 077. 链表排序`

对链表节点进行升序排序

```go
func merge(head1, head2 *ListNode) *ListNode {
    dummyHead := &ListNode{}
    temp, temp1, temp2 := dummyHead, head1, head2
    for temp1 != nil && temp2 != nil {
        if temp1.Val <= temp2.Val {
            temp.Next = temp1
            temp1 = temp1.Next
        } else {
            temp.Next = temp2
            temp2 = temp2.Next
        }
        temp = temp.Next
    }
    if temp1 != nil {
        temp.Next = temp1
    } else if temp2 != nil {
        temp.Next = temp2
    }
    return dummyHead.Next
}

func sort(head, tail *ListNode) *ListNode {
    if head == nil {
        return head
    }

    if head.Next == tail {
        head.Next = nil
        return head
    }

    slow, fast := head, head
    for fast != tail {
        slow = slow.Next
        fast = fast.Next
        if fast != tail {
            fast = fast.Next
        }
    }

    mid := slow
    return merge(sort(head, mid), sort(mid, tail))
}

func sortList(head *ListNode) *ListNode {
    return sort(head, nil)
}
```

## 78

`剑指 Offer II 078. 合并排序链表`

给定一个链表数组，将链表按照升序排列

```go
//合并K个升序链表
func mergeKLists(lists []*ListNode) (res *ListNode) {
	for _, v := range lists {
		res = mergeTwoLists(res, v)
	}
	return res
}

//合并两个升序链表
func mergeTwoLists(list1 *ListNode, list2 *ListNode) *ListNode {
	//初始化一个虚拟的头节点
	newList := &ListNode{}
	p := newList
	p1 := list1
	p2 := list2
	//遍历对比两个指针值的大小，有一个走完了就停止
	for p1 != nil && p2 != nil {
		//将值小的节点接到p指针后面
		if p1.Val > p2.Val {
			p.Next = p2
			p2 = p2.Next
		} else {
			p.Next = p1
			p1 = p1.Next
		}
		//p指针前进
		p = p.Next
	}
	//将未比较的剩余节点都放到p指针后面
	if p1 != nil {
		p.Next = p1
	}
	if p2 != nil {
		p.Next = p2
	}
	//返回虚拟头节点的下一个节点就是真正的头节点
	return newList.Next
}
```

## 79

`剑指 Offer II 079. 所有子集`

给定一个元素各不相同的的数组，返回所有不重复的子集

```go
func subsets(nums []int) (ans [][]int) {
    n := len(nums)
    for mask := 0; mask < 1<<n; mask++ {
        set := []int{}
        for i, v := range nums {
            if mask>>i&1 > 0 {
                set = append(set, v)
            }
        }
        ans = append(ans, append([]int(nil), set...))
    }
    return
}
```

## 80

`剑指 Offer II 080. 含有 k 个元素的组合`

给定整数n和k，返回`1...n`中所有可能的k个数的组合

```go
func combine(n int, k int) (ans [][]int) {
	temp := []int{}
	var dfs func(int)
	dfs = func(cur int) {
		// 剪枝：temp 长度加上区间 [cur, n] 的长度小于 k，不可能构造出长度为 k 的 temp
		if len(temp) + (n - cur + 1) < k {
			return
		}
		// 记录合法的答案
		if len(temp) == k {
			comb := make([]int, k)
			copy(comb, temp)
			ans = append(ans, comb)
			return
		}
		// 考虑选择当前位置
		temp = append(temp, cur)
		dfs(cur + 1)
		temp = temp[:len(temp)-1]
		// 考虑不选择当前位置
		dfs(cur + 1)
	}
	dfs(1)
	return
}
```

## 81

`剑指 Offer II 081. 允许重复选择元素的组合`

从数组中寻找和为目标值的组合，数组中的元素可以重复选择

> 下面这种题解是标准解法，不过不能去除重复的情况，详情看82

```go
func combinationSum(candidates []int, target int) (ans [][]int) {
	comb := []int{}
	var dfs func(target, idx int)
	dfs = func(target, idx int) {
		if idx == len(candidates) {
			return
		}
		if target == 0 {
			ans = append(ans, append([]int(nil), comb...))
			return
		}
		// 直接跳过
		dfs(target, idx+1)
		// 选择当前数
		if target-candidates[idx] >= 0 {
			comb = append(comb, candidates[idx])
			dfs(target-candidates[idx], idx)
			comb = comb[:len(comb)-1]
		}
	}
	dfs(target, 0)
	return
}
```

## 82

`剑指 Offer II 082. 含有重复元素集合的组合`

与81题类似，不过这里元素只能使用一次

```go
func combinationSum2(candidates []int, target int) (ans [][]int) {
    sort.Ints(candidates)
    var freq [][2]int // [值，次数]
    for _, num := range candidates {
        if freq == nil || num != freq[len(freq)-1][0] {
            freq = append(freq, [2]int{num, 1})
        } else {
            freq[len(freq)-1][1]++
        }
    }

    var sequence []int
    var dfs func(pos, rest int)
    dfs = func(pos, rest int) {
        if rest == 0 {
            ans = append(ans, append([]int(nil), sequence...))
            return
        }
        if pos == len(freq) || rest < freq[pos][0] {
            return
        }

        dfs(pos+1, rest)

        most := min(rest/freq[pos][0], freq[pos][1])
        for i := 1; i <= most; i++ {
            sequence = append(sequence, freq[pos][0])
            dfs(pos+1, rest-i*freq[pos][0])
        }
        sequence = sequence[:len(sequence)-most]
    }
    dfs(0, target)
    return
}

func min(a, b int) int {
    if a < b {
        return a
    }
    return b
}
```

## 83

`剑指 Offer II 083. 没有重复元素集合的全排列`

给定一个不包含重复数字的整数数组，返回所有可能的全排列

```go
func permute(nums []int) [][]int {
	n := len(nums)
	var ans [][]int
	var path []int
	vis := make([]bool, n)
	var dfs func()
	dfs = func() {
		if len(path) == n {
			ans = append(ans, append([]int{}, path...))
			return
		}
		for i := 0; i < n; i++ {
			if !vis[i] {
				vis[i] = true
				path = append(path, nums[i])
				dfs()
				vis[i] = false
				path = path[:len(path) - 1]
			}
		}
	}
	dfs()
	return ans
}
```

## 84

`剑指 Offer II 084. 含有重复元素集合的全排列`

给定一个可包含重复数字的整数集合 nums ，按任意顺序 返回它所有不重复的全排列。

```go
func permuteUnique(nums []int) (ans [][]int) {
    sort.Ints(nums)
    n := len(nums)
    perm := []int{}
    vis := make([]bool, n)
    var backtrack func(int)
    backtrack = func(idx int) {
        if idx == n {
            ans = append(ans, append([]int(nil), perm...))
            return
        }
        for i, v := range nums {
            if vis[i] || i > 0 && !vis[i-1] && v == nums[i-1] {
                continue
            }
            perm = append(perm, v)
            vis[i] = true
            backtrack(idx + 1)
            vis[i] = false
            perm = perm[:len(perm)-1]
        }
    }
    backtrack(0)
    return
}
```

## 85

`剑指 Offer II 085. 生成匹配的括号`

正整数 n 代表生成括号的对数，请设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

```go
// 动态规划版本
func generateParenthesis(n int) []string {
	dp := make([][]string, n+1)
	dp[0] = []string{""}
	for i := 1; i <= n; i++ {
		for j := 0; j < i; j++ {
			for _, left := range dp[j] {
				for _, right := range dp[i-j-1] {
					dp[i] = append(dp[i], "("+left+")"+right)
				}
			}

		}
	}
	return dp[n]
}

// 递归版本
func generateParenthesis(n int) []string {
	var res []string
	var leftCnt, rightCnt int
	var tmp []byte
	var dfs func(cnt int)
	dfs = func(cnt int) {
		if cnt == n*2 {
			res = append(res, string(tmp))
			return
		}
		if leftCnt < n {
			leftCnt++
			tmp = append(tmp, '(')
			dfs(cnt + 1)
			leftCnt--
			tmp = tmp[:len(tmp)-1]
		}
		if leftCnt > rightCnt {
			rightCnt++
			tmp = append(tmp, ')')
			dfs(cnt + 1)
			rightCnt--
			tmp = tmp[:len(tmp)-1]
		}
	}
	dfs(0)
	return res
}
```

## 86

`剑指 Offer II 086. 分割回文子字符串`

将字符串分割成回文串, 返回所有可能的方案

```go
func partition(s string) (ans [][]string) {
    n := len(s)
    f := make([][]bool, n)
    for i := range f {
        f[i] = make([]bool, n)
        for j := range f[i] {
            f[i][j] = true
        }
    }
    for i := n - 1; i >= 0; i-- {
        for j := i + 1; j < n; j++ {
            f[i][j] = s[i] == s[j] && f[i+1][j-1]
        }
    }

    splits := []string{}
    var dfs func(int)
    dfs = func(i int) {
        if i == n {
            ans = append(ans, append([]string(nil), splits...))
            return
        }
        for j := i; j < n; j++ {
            if f[i][j] {
                splits = append(splits, s[i:j+1])
                dfs(j + 1)
                splits = splits[:len(splits)-1]
            }
        }
    }
    dfs(0)
    return
}
```

## 87

`剑指 Offer II 087. 复原 IP`

将字符串格式化成所有合法的ipv4地址

```go
const SEG_COUNT = 4

var (
    ans []string
    segments []int
)

func restoreIpAddresses(s string) []string {
    segments = make([]int, SEG_COUNT)
    ans = []string{}
    dfs(s, 0, 0)
    return ans
}

func dfs(s string, segId, segStart int) {
    // 如果找到了 4 段 IP 地址并且遍历完了字符串，那么就是一种答案
    if segId == SEG_COUNT {
        if segStart == len(s) {
            ipAddr := ""
            for i := 0; i < SEG_COUNT; i++ {
                ipAddr += strconv.Itoa(segments[i])
                if i != SEG_COUNT - 1 {
                    ipAddr += "."
                }
            }
            ans = append(ans, ipAddr)
        }
        return
    }

    // 如果还没有找到 4 段 IP 地址就已经遍历完了字符串，那么提前回溯
    if segStart == len(s) {
        return
    }
    // 由于不能有前导零，如果当前数字为 0，那么这一段 IP 地址只能为 0
    if s[segStart] == '0' {
        segments[segId] = 0
        dfs(s, segId + 1, segStart + 1)
    }
    // 一般情况，枚举每一种可能性并递归
    addr := 0
    for segEnd := segStart; segEnd < len(s); segEnd++ {
        addr = addr * 10 + int(s[segEnd] - '0')
        if addr > 0 && addr <= 0xFF {
            segments[segId] = addr
            dfs(s, segId + 1, segEnd + 1)
        } else {
            break
        }
    }
}
```

## 88

`剑指 Offer II 088. 爬楼梯的最少成本`

给定一个一维数组表示爬楼梯需要的成本，并且每次支付一次就可以往上爬一个阶梯或者爬两个阶梯, 计算爬楼梯的最少成本。

```go
func minCostClimbingStairs(cost []int) int {
    n := len(cost)
    pre, cur := 0, 0
    for i := 2; i <= n; i++ {
        pre, cur = cur, min(cur+cost[i-1], pre+cost[i-2])
    }
    return cur
}

func min(a, b int) int {
    if a < b {
        return a
    }
    return b
}
```

## 89

`剑指 Offer II 089. 房屋偷盗`

给定一个一维数组表示每间房子的价值，不能偷相邻的两家，问能够偷窃到的最高金额

```go
func rob(nums []int) int {
    if len(nums) == 0 {
        return 0
    }
    if len(nums) == 1 {
        return nums[0]
    }
    dp := make([]int, len(nums))
    dp[0] = nums[0]
    dp[1] = max(nums[0], nums[1])
    for i := 2; i < len(nums); i++ {
        dp[i] = max(dp[i-2] + nums[i], dp[i-1])
    }
    return dp[len(nums)-1]
}

func max(x, y int) int {
    if x > y {
        return x
    }
    return y
}
```

## 90

`剑指 Offer II 090. 环形房屋偷盗`

与上一题类似，不过这一题房屋是首位相连的，问能够偷窃到的最大价值

```go
func _rob(nums []int) int {
    first, second := nums[0], max(nums[0], nums[1])
    for _, v := range nums[2:] {
        first, second = second, max(first+v, second)
    }
    return second
}

func rob(nums []int) int {
    n := len(nums)
    if n == 1 {
        return nums[0]
    }
    if n == 2 {
        return max(nums[0], nums[1])
    }
    return max(_rob(nums[:n-1]), _rob(nums[1:]))
}

func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}
```