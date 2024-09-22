## 31、

`剑指 Offer II 031. 最近最少使用缓存`

设计一个最近最少使用的缓存数据结构，提供get和put方法

```go
import "container/list"

type LRUCache struct {
    capacity int
    cache    map[int]*list.Element
    list     *list.List
}

type entry struct {
    key   int
    value int
}

func Constructor(capacity int) LRUCache {
    return LRUCache{
        capacity: capacity,
        cache:    make(map[int]*list.Element),
        list:     list.New(),
    }
}

func (this *LRUCache) Get(key int) int {
    if elem, ok := this.cache[key]; ok {
        this.list.MoveToFront(elem)
        return elem.Value.(*entry).value
    }
    return -1
}

func (this *LRUCache) Put(key int, value int) {
    if elem, ok := this.cache[key]; ok {
        elem.Value.(*entry).value = value
        this.list.MoveToFront(elem)
        return
    }
    if this.list.Len() == this.capacity {
        lastElem := this.list.Back()
        delete(this.cache, lastElem.Value.(*entry).key)
        this.list.Remove(lastElem)
    }
    newElem := this.list.PushFront(&entry{key: key, value: value})
    this.cache[key] = newElem
}
```

## 32、

`剑指 Offer II 032. 有效的变位词`

判断字符串s和t是否是一组有效的变位词，即元素相同位置不同

```go
func isAnagram(s, t string) bool {
    if s == t {
        return false
    }
    var c1, c2 [26]int
    for _, ch := range s {
        c1[ch-'a']++
    }
    for _, ch := range t {
        c2[ch-'a']++
    }
    return c1 == c2
}
```

## 33、

`剑指 Offer II 033. 变位词组`

给定一个字符串数组，将所有是同一类变位词的组合在一起

```go
func groupAnagrams(strs []string) [][]string {
    mp := map[[26]int][]string{}
    for _, str := range strs {
        cnt := [26]int{}
        for _, b := range str {
            cnt[b-'a']++
        }
        mp[cnt] = append(mp[cnt], str)
    }
    ans := make([][]string, 0, len(mp))
    for _, v := range mp {
        ans = append(ans, v)
    }
    return ans
}
```

## 34、

`剑指 Offer II 034. 外星语言是否排序`

给定一种新的order字符顺序，判断一个字符串数组words中的字符串是否是按照字典序进行排列的

```go
func isAlienSorted(words []string, order string) bool {
    index := [26]int{}
    for i, c := range order {
        index[c-'a'] = i
    }
next:
    for i := 1; i < len(words); i++ {
        for j := 0; j < len(words[i-1]) && j < len(words[i]); j++ {
            pre, cur := index[words[i-1][j]-'a'], index[words[i][j]-'a']
            if pre > cur {
                return false
            }
            if pre < cur {
                continue next
            }
        }
        if len(words[i-1]) > len(words[i]) {
            return false
        }
    }
    return true
}
```

## 35、

`剑指 Offer II 035. 最小时间差`

给定一个字符串列表，其中字符串是以"HH:MM"的24小时时间格式进行表示，找到列表中时间差最小值，并以分钟格式进行表示

```go
func getMinutes(t string) int {
    return (int(t[0]-'0')*10+int(t[1]-'0'))*60 + int(t[3]-'0')*10 + int(t[4]-'0')
}

func findMinDifference(timePoints []string) int {
    if len(timePoints) > 1440 {
        return 0
    }
    sort.Strings(timePoints)
    ans := math.MaxInt32
    t0Minutes := getMinutes(timePoints[0])
    preMinutes := t0Minutes
    for _, t := range timePoints[1:] {
        minutes := getMinutes(t)
        ans = min(ans, minutes-preMinutes) // 相邻时间的时间差
        preMinutes = minutes
    }
    ans = min(ans, t0Minutes+1440-preMinutes) // 首尾时间的时间差
    return ans
}

func min(a, b int) int {
    if a > b {
        return b
    }
    return a
}
```

## 36、

`剑指 Offer II 036. 后缀表达式`

给定一个token字符串列表，该token列表是逆波兰表达式，用来求该后缀表达式的结果，整数除法只保留整数部分

```go
func evalRPN(tokens []string) int {
    stack := make([]int, (len(tokens)+1)/2)
    index := -1
    for _, token := range tokens {
        val, err := strconv.Atoi(token)
        if err == nil {
            index++
            stack[index] = val
        } else {
            index--
            switch token {
            case "+":
                stack[index] += stack[index+1]
            case "-":
                stack[index] -= stack[index+1]
            case "*":
                stack[index] *= stack[index+1]
            default:
                stack[index] /= stack[index+1]
            }
        }
    }
    return stack[0]
}
```

## 37、

`剑指 Offer II 037. 小行星碰撞`

给定一个整数数组用来表示同一行的小行星，绝对值表示大小，正负表示方向，正表示向右移动，负表示向左移动。

当两个行星相遇会进行碰撞，留下大小大的那个，大小相同两个一起爆炸

求解最后的小行星情况

```go
func asteroidCollision(asteroids []int) (st []int) {
    for _, aster := range asteroids {
        alive := true
        for alive && aster < 0 && len(st) > 0 && st[len(st)-1] > 0 {
            alive = st[len(st)-1] < -aster // aster 是否存在
            if st[len(st)-1] <= -aster {   // 栈顶小行星爆炸
                st = st[:len(st)-1]
            }
        }
        if alive {
            st = append(st, aster)
        }
    }
    return
}
```

## 38、

`剑指 Offer II 038. 每日温度`

给定一个每天的气温列表，返回最近的一个温度更高的相差的天数

```go
func dailyTemperatures(temperatures []int) []int {
    length := len(temperatures)
    ans := make([]int, length)
    stack := []int{}
    for i := 0; i < length; i++ {
        temperature := temperatures[i]
        for len(stack) > 0 && temperature > temperatures[stack[len(stack)-1]] {
            prevIndex := stack[len(stack)-1]
            stack = stack[:len(stack)-1]
            ans[prevIndex] = i - prevIndex
        }
        stack = append(stack, i)
    }
    return ans
}
```

## 39、

`剑指 Offer II 039. 直方图最大矩形面积`

给定一个整数数组，表示一个二维平面，其中每个元素表示其y轴的高度，返回该二维平面中覆盖的最大的矩形面积

```go
func largestRectangleArea(heights []int) int {
    n := len(heights)
    left, right := make([]int, n), make([]int, n)
    mono_stack := []int{}
    for i := 0; i < n; i++ {
        for len(mono_stack) > 0 && heights[mono_stack[len(mono_stack)-1]] >= heights[i] {
            mono_stack = mono_stack[:len(mono_stack)-1]
        }
        if len(mono_stack) == 0 {
            left[i] = -1
        } else {
            left[i] = mono_stack[len(mono_stack)-1]
        }
        mono_stack = append(mono_stack, i)
    }
    mono_stack = []int{}
    for i := n - 1; i >= 0; i-- {
        for len(mono_stack) > 0 && heights[mono_stack[len(mono_stack)-1]] >= heights[i] {
            mono_stack = mono_stack[:len(mono_stack)-1]
        }
        if len(mono_stack) == 0 {
            right[i] = n
        } else {
            right[i] = mono_stack[len(mono_stack)-1]
        }
        mono_stack = append(mono_stack, i)
    }
    ans := 0
    for i := 0; i < n; i++ {
        ans = max(ans, (right[i] - left[i] - 1) * heights[i])
    }
    return ans
}

func max(x, y int) int {
    if x > y {
        return x
    }
    return y
}
```

## 40、

`剑指 Offer II 040. 矩阵中最大的矩形`

一个只包含0、1元素的矩阵，找到全部为1的元素的最大矩阵的面积

```go
func maximalRectangle(matrix []string) (ans int) {
    if len(matrix) == 0 {
        return
    }
    m, n := len(matrix), len(matrix[0])
    left := make([][]int, m)
    for i, row := range matrix {
        left[i] = make([]int, n)
        for j, v := range row {
            if v == '0' {
                continue
            }
            if j == 0 {
                left[i][j] = 1
            } else {
                left[i][j] = left[i][j-1] + 1
            }
        }
    }
    for i, row := range matrix {
        for j, v := range row {
            if v == '0' {
                continue
            }
            width := left[i][j]
            area := width
            for k := i - 1; k >= 0; k-- {
                width = min(width, left[k][j])
                if width == 0 {
                    break
                }
                area = max(area, (i-k+1)*width)
            }
            ans = max(ans, area)
        }
    }
    return
}

func min(a, b int) int {
    if a < b {
        return a
    }
    return b
}

func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}
```

## 41、

`剑指 Offer II 041. 滑动窗口的平均值`

给定一个指定大小的窗口，提供数据流并返回这个窗口内的元素的平均值

```go
type MovingAverage struct {
    size, sum int
    q         []int
}

func Constructor(size int) MovingAverage {
    return MovingAverage{size: size}
}

func (m *MovingAverage) Next(val int) float64 {
    if len(m.q) == m.size {
        m.sum -= m.q[0]
        m.q = m.q[1:]
    }
    m.sum += val
    m.q = append(m.q, val)
    return float64(m.sum) / float64(len(m.q))
}
```

## 42、

`剑指 Offer II 042. 最近请求次数`

记录请求的时间等，并且返回最近3000ms内的调用次数

```go
type RecentCounter []int

func Constructor() (_ RecentCounter) { return }

func (q *RecentCounter) Ping(t int) int {
    *q = append(*q, t)
    for (*q)[0] < t-3000 {
        *q = (*q)[1:]
    }
    return len(*q)
}
```

## 43、

`剑指 Offer II 043. 往完全二叉树添加节点`

一个尽量集中在左边的完全二叉树，提供插入以及获取根节点的元素

```go
type CBTInserter struct {
    root      *TreeNode
    candidate []*TreeNode
}

func Constructor(root *TreeNode) CBTInserter {
    q := []*TreeNode{root}
    candidate := []*TreeNode{}
    for len(q) > 0 {
        node := q[0]
        q = q[1:]
        if node.Left != nil {
            q = append(q, node.Left)
        }
        if node.Right != nil {
            q = append(q, node.Right)
        }
        if node.Left == nil || node.Right == nil {
            candidate = append(candidate, node)
        }
    }
    return CBTInserter{root, candidate}
}

func (c *CBTInserter) Insert(val int) int {
    child := &TreeNode{Val: val}
    node := c.candidate[0]
    if node.Left == nil {
        node.Left = child
    } else {
        node.Right = child
        c.candidate = c.candidate[1:]
    }
    c.candidate = append(c.candidate, child)
    return node.Val
}

func (c *CBTInserter) Get_root() *TreeNode {
    return c.root
}
```

## 44、

`剑指 Offer II 044. 二叉树每层的最大值`

给定一个二叉树，找出二叉树每一层的最大值

```go
func largestValues(root *TreeNode) (ans []int) {
    var dfs func(*TreeNode, int)
    dfs = func(node *TreeNode, curHeight int) {
        if node == nil {
            return
        }
        if curHeight == len(ans) {
            ans = append(ans, node.Val)
        } else {
            ans[curHeight] = max(ans[curHeight], node.Val)
        }
        dfs(node.Left, curHeight+1)
        dfs(node.Right, curHeight+1)
    }
    dfs(root, 0)
    return
}

func max(a, b int) int {
    if b > a {
        return b
    }
    return a
}
```

## 45、

`剑指 Offer II 045. 二叉树最底层最左边的值`

给定一个二叉树，找出二叉树最底层，最左边的元素

```go
func findBottomLeftValue(root *TreeNode) (curVal int) {
    curHeight := 0
    var dfs func(*TreeNode, int)
    dfs = func(node *TreeNode, height int) {
        if node == nil {
            return
        }
        height++
        dfs(node.Left, height)
        dfs(node.Right, height)
        if height > curHeight {
            curHeight = height
            curVal = node.Val
        }
    }
    dfs(root, 0)
    return
}
```

## 46、

`剑指 Offer II 046. 二叉树的右侧视图`

给定一个二叉树，返回其右边的第一层视图，并从上往下打印出来

```go
/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func rightSideView(root *TreeNode) []int {
    ans:=[]int{}
    if root==nil{
        return  ans
    }
    var dfs func(node *TreeNode,depth int)
    dfs = func(node *TreeNode,depth int){
        if node==nil{
            return
        }
        
        if len(ans)==depth{
            ans = append(ans,node.Val)
        }
        dfs(node.Right,depth+1)
        dfs(node.Left,depth+1)
    }
    dfs(root,0)
    return ans
}
```

## 47、

`剑指 Offer II 047. 二叉树剪枝`

给定一个二叉树，对所有只包含0数据的子树进行剪枝

```go

func pruneTree(root *TreeNode) *TreeNode {
    if root == nil {
        return nil
    }
    root.Left = pruneTree(root.Left)
    root.Right = pruneTree(root.Right)
    if root.Left == nil && root.Right == nil && root.Val == 0 {
        return nil
    }
    return root
}
```

## 48、

`剑指 Offer II 048. 序列化与反序列化二叉树`

将二叉树进行序列化和反序列化

```go
type Codec struct{}

func Constructor() (_ Codec) {
    return
}

func (Codec) serialize(root *TreeNode) string {
    sb := &strings.Builder{}
    var dfs func(*TreeNode)
    dfs = func(node *TreeNode) {
        if node == nil {
            sb.WriteString("null,")
            return
        }
        sb.WriteString(strconv.Itoa(node.Val))
        sb.WriteByte(',')
        dfs(node.Left)
        dfs(node.Right)
    }
    dfs(root)
    return sb.String()
}

func (Codec) deserialize(data string) *TreeNode {
    sp := strings.Split(data, ",")
    var build func() *TreeNode
    build = func() *TreeNode {
        if sp[0] == "null" {
            sp = sp[1:]
            return nil
        }
        val, _ := strconv.Atoi(sp[0])
        sp = sp[1:]
        return &TreeNode{val, build(), build()}
    }
    return build()
}
```

## 49、

`剑指 Offer II 049. 从根节点到叶节点的路径数字之和`

给定一个二叉树，获取从根节点到叶子节点的所有路径所表示的数字之和。

```go
func dfs(root *TreeNode, prevSum int) int {
    if root == nil {
        return 0
    }
    sum := prevSum*10 + root.Val
    if root.Left == nil && root.Right == nil {
        return sum
    }
    return dfs(root.Left, sum) + dfs(root.Right, sum)
}

func sumNumbers(root *TreeNode) int {
    return dfs(root, 0)
}
```

## 50、

`剑指 Offer II 050. 向下的路径节点之和`

给定一个二叉树，返回其中路径和为target的路径个数，其中这路径只能从上往下

```go
func pathSum(root *TreeNode, targetSum int) (ans int) {
    preSum := map[int64]int{0: 1}
    var dfs func(*TreeNode, int64)
    dfs = func(node *TreeNode, curr int64) {
        if node == nil {
            return
        }
        curr += int64(node.Val)
        ans += preSum[curr-int64(targetSum)]
        preSum[curr]++
        dfs(node.Left, curr)
        dfs(node.Right, curr)
        preSum[curr]--
        return
    }
    dfs(root, 0)
    return
}
```

## 51、

`剑指 Offer II 051. 节点之和最大的路径`

给定一个二叉树，返回其最大的路径和，这里的路径可以是任意两个节点之间相连的路径

```go
func maxPathSum(root *TreeNode) int {
    maxSum := math.MinInt32
    var maxGain func(*TreeNode) int
    maxGain = func(node *TreeNode) int {
        if node == nil {
            return 0
        }

        // 递归计算左右子节点的最大贡献值
        // 只有在最大贡献值大于 0 时，才会选取对应子节点
        leftGain := max(maxGain(node.Left), 0)
        rightGain := max(maxGain(node.Right), 0)

        // 节点的最大路径和取决于该节点的值与该节点的左右子节点的最大贡献值
        priceNewPath := node.Val + leftGain + rightGain

        // 更新答案
        maxSum = max(maxSum, priceNewPath)

        // 返回节点的最大贡献值
        return node.Val + max(leftGain, rightGain)
    }
    maxGain(root)
    return maxSum
}

func max(x, y int) int {
    if x > y {
        return x
    }
    return y
}
```

## 52、

`剑指 Offer II 052. 展平二叉搜索树`

给定一个二叉搜索树，将其进行结构转换，使得没有左节点，只有右节点

```go
func increasingBST(root *TreeNode) *TreeNode {
    dummyNode := &TreeNode{}
    resNode := dummyNode

    var inorder func(*TreeNode)
    inorder = func(node *TreeNode) {
        if node == nil {
            return
        }
        inorder(node.Left)

        // 在中序遍历的过程中修改节点指向
        resNode.Right = node
        node.Left = nil
        resNode = node

        inorder(node.Right)
    }
    inorder(root)

    return dummyNode.Right
}
```

## 53、

`剑指 Offer II 053. 二叉搜索树中的中序后继`

给定一个二叉搜索树以及一个节点，找到这个节点的中序后继

```go
func inorderSuccessor(root *TreeNode, p *TreeNode) *TreeNode {
    var successor *TreeNode
    if p.Right != nil {
        successor = p.Right
        for successor.Left != nil {
            successor = successor.Left
        }
        return successor
    }
    node := root
    for node != nil {
        if node.Val > p.Val {
            successor = node
            node = node.Left
        } else {
            node = node.Right
        }
    }
    return successor
}
```

## 54、

`剑指 Offer II 054. 所有大于等于节点的值之和`

给定一个二叉搜索树，将每个节点替换成大于他节点的元素的和

```go
func convertBST(root *TreeNode) *TreeNode {
    sum := 0
    var dfs func(*TreeNode)
    dfs = func(node *TreeNode) {
        if node != nil {
            dfs(node.Right)
            sum += node.Val
            node.Val = sum
            dfs(node.Left)
        }
    }
    dfs(root)
    return root
}
```

## 55、

`剑指 Offer II 055. 二叉搜索树迭代器`

给定一个二叉搜素树迭代器，提供next和hasNext两个方法

```go
type BSTIterator struct {
    stack []*TreeNode
    cur   *TreeNode
}

func Constructor(root *TreeNode) BSTIterator {
    return BSTIterator{cur: root}
}

func (it *BSTIterator) Next() int {
    for node := it.cur; node != nil; node = node.Left {
        it.stack = append(it.stack, node)
    }
    it.cur, it.stack = it.stack[len(it.stack)-1], it.stack[:len(it.stack)-1]
    val := it.cur.Val
    it.cur = it.cur.Right
    return val
}

func (it *BSTIterator) HasNext() bool {
    return it.cur != nil || len(it.stack) > 0
}
```

## 56、

`剑指 Offer II 056. 二叉搜索树中两个节点之和`

判断二叉搜索树中是否存在两个节点，和为目标值

```go
func findTarget(root *TreeNode, k int) bool {
    visit := map[int]struct{}{}
    flag := false
    var inorder func(*TreeNode)
    inorder = func(node *TreeNode) {
        if node == nil || flag {
            return
        }
        inorder(node.Left)
        if _, ok := visit[k-node.Val]; ok {
            flag = true
            return
        }
        visit[node.Val] = struct{}{}
        inorder(node.Right)
    }
    inorder(root)
    return flag
}
```

## 57、

`剑指 Offer II 057. 值和下标之差都在给定的范围内`

给定一个数组，判断是否存在两个下标i、j，下标差绝对值小于等于k，所对应的值差值小于等于t

```go
func getID(x, w int) int {
    if x >= 0 {
        return x / w
    }
    return (x+1)/w - 1
}

func containsNearbyAlmostDuplicate(nums []int, k, t int) bool {
    mp := map[int]int{}
    for i, x := range nums {
        id := getID(x, t+1)
        if _, has := mp[id]; has {
            return true
        }
        if y, has := mp[id-1]; has && abs(x-y) <= t {
            return true
        }
        if y, has := mp[id+1]; has && abs(x-y) <= t {
            return true
        }
        mp[id] = x
        if i >= k {
            delete(mp, getID(nums[i-k], t+1))
        }
    }
    return false
}

func abs(x int) int {
    if x < 0 {
        return -x
    }
    return x
}
```

## 58、

`剑指 Offer II 058. 日程表`

提供一个方法，在添加日程的时候，时间区间为`[start, end)`, 只要这个时间段没有其他安排就能够使用

```go
type MyCalendar struct {
    tree, lazy map[int]bool
}

func Constructor() MyCalendar {
    return MyCalendar{map[int]bool{}, map[int]bool{}}
}

func (c MyCalendar) query(start, end, l, r, idx int) bool {
    if r < start || end < l {
        return false
    }
    if c.lazy[idx] { // 如果该区间已被预订，则直接返回
        return true
    }
    if start <= l && r <= end {
        return c.tree[idx]
    }
    mid := (l + r) >> 1
    return c.query(start, end, l, mid, 2*idx) ||
        c.query(start, end, mid+1, r, 2*idx+1)
}

func (c MyCalendar) update(start, end, l, r, idx int) {
    if r < start || end < l {
        return
    }
    if start <= l && r <= end {
        c.tree[idx] = true
        c.lazy[idx] = true
    } else {
        mid := (l + r) >> 1
        c.update(start, end, l, mid, 2*idx)
        c.update(start, end, mid+1, r, 2*idx+1)
        c.tree[idx] = true
        if c.lazy[2*idx] && c.lazy[2*idx+1] {
            c.lazy[idx] = true
        }
    }
}

func (c MyCalendar) Book(start, end int) bool {
    if c.query(start, end-1, 0, 1e9, 1) {
        return false
    }
    c.update(start, end-1, 0, 1e9, 1)
    return true
}
```

## 59、

`剑指 Offer II 059. 数据流的第 K 大数值`

一个数据流结构，在插入元素的时候返回数据中第k大的数。

```go
type KthLargest struct {
    sort.IntSlice
    k int
}

func Constructor(k int, nums []int) KthLargest {
    kl := KthLargest{k: k}
    for _, val := range nums {
        kl.Add(val)
    }
    return kl
}

func (kl *KthLargest) Push(v interface{}) {
    kl.IntSlice = append(kl.IntSlice, v.(int))
}

func (kl *KthLargest) Pop() interface{} {
    a := kl.IntSlice
    v := a[len(a)-1]
    kl.IntSlice = a[:len(a)-1]
    return v
}

func (kl *KthLargest) Add(val int) int {
    heap.Push(kl, val)
    if kl.Len() > kl.k {
        heap.Pop(kl)
    }
    return kl.IntSlice[0]
}
```

## 60、

剑指 Offer II 060. 出现频率最高的 k 个数字

统计数字数组中元素的出现次数，返回出现频率最高的几个

```go
func topKFrequent(nums []int, k int) []int {
    occurrences := map[int]int{}
    for _, num := range nums {
        occurrences[num]++
    }
    h := &IHeap{}
    heap.Init(h)
    for key, value := range occurrences {
        heap.Push(h, [2]int{key, value})
        if h.Len() > k {
            heap.Pop(h)
        }
    }
    ret := make([]int, k)
    for i := 0; i < k; i++ {
        ret[k - i - 1] = heap.Pop(h).([2]int)[0]
    }
    return ret
}

type IHeap [][2]int

func (h IHeap) Len() int           { return len(h) }
func (h IHeap) Less(i, j int) bool { return h[i][1] < h[j][1] }
func (h IHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *IHeap) Push(x interface{}) {
    *h = append(*h, x.([2]int))
}

func (h *IHeap) Pop() interface{} {
    old := *h
    n := len(old)
    x := old[n-1]
    *h = old[0 : n-1]
    return x
}
```