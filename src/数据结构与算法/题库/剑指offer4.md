## 91

`剑指 Offer II 091. 粉刷房子`

一排房子n个，可以涂成红色、蓝色、绿色这三种颜色中的一种，需要让各个颜色并不相同

给定一个花费数组，其中的每个元素就是该房子涂成红、蓝、绿三种颜色所需要的花费

计算粉刷完所有房子最少的花费成本

```go
func minCost(costs [][]int) int {
    dp := costs[0]
    for _, cost := range costs[1:] {
        dpNew := make([]int, 3)
        for j, c := range cost {
            dpNew[j] = min(dp[(j+1)%3], dp[(j+2)%3]) + c
        }
        dp = dpNew
    }
    return min(min(dp[0], dp[1]), dp[2])
}

func min(a, b int) int {
    if a > b {
        return b
    }
    return a
}
```

## 92

`剑指 Offer II 092. 翻转字符`

一个`0 1`组成的字符串，求使得s单调递增(前面全是0 后面全是1)的最小翻转次数

```go
func minFlipsMonoIncr(s string) int {
    dp0, dp1 := 0, 0
    for _, c := range s {
        dp0New, dp1New := dp0, min(dp0, dp1)
        if c == '1' {
            dp0New++
        } else {
            dp1New++
        }
        dp0, dp1 = dp0New, dp1New
    }
    return min(dp0, dp1)
}

func min(a, b int) int {
    if a > b {
        return b
    }
    return a
}
```

## 93

`剑指 Offer II 093. 最长斐波那契数列`

给定一个递增的正整数数组，找到其中最长的一个满足斐波那契数列的元素

```go
func lenLongestFibSubseq(arr []int) (ans int) {
    n := len(arr)
    indices := make(map[int]int, n)
    for i, x := range arr {
        indices[x] = i
    }
    dp := make([][]int, n)
    for i := range dp {
        dp[i] = make([]int, n)
    }
    for i, x := range arr {
        for j := n - 1; j >= 0 && arr[j]*2 > x; j-- {
            if k, ok := indices[x-arr[j]]; ok {
                dp[j][i] = max(dp[k][j]+1, 3)
                ans = max(ans, dp[j][i])
            }
        }
    }
    return
}

func max(a, b int) int {
    if b > a {
        return b
    }
    return a
}
```

## 94

`剑指 Offer II 094. 最少回文分割`

给定一个字符串s，找到分割的最小次数，将s分割成字串，且每个字串都是回文串，

```go
func minCut(s string) int {
    n := len(s)
    g := make([][]bool, n)
    for i := range g {
        g[i] = make([]bool, n)
        for j := range g[i] {
            g[i][j] = true
        }
    }
    for i := n - 1; i >= 0; i-- {
        for j := i + 1; j < n; j++ {
            g[i][j] = s[i] == s[j] && g[i+1][j-1]
        }
    }

    f := make([]int, n)
    for i := range f {
        if g[0][i] {
            continue
        }
        f[i] = math.MaxInt64
        for j := 0; j < i; j++ {
            if g[j+1][i] && f[j]+1 < f[i] {
                f[i] = f[j] + 1
            }
        }
    }
    return f[n-1]
}
```

## 95

`剑指 Offer II 095. 最长公共子序列`

找到两个字符串的最长的公共子序列(即满足不改变字符的相对顺序的情况下删除某些字符)

```go
func longestCommonSubsequence(text1, text2 string) int {
    m, n := len(text1), len(text2)
    dp := make([][]int, m+1)
    for i := range dp {
        dp[i] = make([]int, n+1)
    }
    for i, c1 := range text1 {
        for j, c2 := range text2 {
            if c1 == c2 {
                dp[i+1][j+1] = dp[i][j] + 1
            } else {
                dp[i+1][j+1] = max(dp[i][j+1], dp[i+1][j])
            }
        }
    }
    return dp[m][n]
}

func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}
```

## 96

`剑指 Offer II 096. 字符串交织`

判断两个字符串s1 s2交织(轮流选择元素)后是否与s3相等

```go
func isInterleave(s1 string, s2 string, s3 string) bool {
    n, m, t := len(s1), len(s2), len(s3)
    if (n + m) != t {
        return false
    }
    f := make([]bool, m + 1)
    f[0] = true
    for i := 0; i <= n; i++ {
        for j := 0; j <= m; j++ {
            p := i + j - 1
            if i > 0 {
                f[j] = f[j] && s1[i-1] == s3[p]
            }
            if j > 0 {
                f[j] = f[j] || f[j-1] && s2[j-1] == s3[p]
            }
        }
    }
    return f[m]
}
```

## 97

`剑指 Offer II 097. 子序列的数目`

判断字符串s中有多少个子序列是在t中出现了

```go
func numDistinct(s, t string) int {
    m, n := len(s), len(t)
    if m < n {
        return 0
    }
    dp := make([][]int, m+1)
    for i := range dp {
        dp[i] = make([]int, n+1)
        dp[i][n] = 1
    }
    for i := m - 1; i >= 0; i-- {
        for j := n - 1; j >= 0; j-- {
            if s[i] == t[j] {
                dp[i][j] = dp[i+1][j+1] + dp[i+1][j]
            } else {
                dp[i][j] = dp[i+1][j]
            }
        }
    }
    return dp[0][0]
}
```

## 98

`剑指 Offer II 098. 路径的数目`

一个`m*n`的网格，从左上到右下，只能向下或者向右移动一步，问总共有多少条不同的路径。

```go
func uniquePaths(m, n int) int {
    dp := make([][]int, m)
    for i := range dp {
        dp[i] = make([]int, n)
        dp[i][0] = 1
    }
    for j := 0; j < n; j++ {
        dp[0][j] = 1
    }
    for i := 1; i < m; i++ {
        for j := 1; j < n; j++ {
            dp[i][j] = dp[i-1][j] + dp[i][j-1]
        }
    }
    return dp[m-1][n-1]
}
```

## 99

`剑指 Offer II 099. 最小路径之和`

一个`m*n`的网格，从左上角到右下角的路径，使得路径上的数字总和为最小。

每次向下或者向右移动一步

```go
func minPathSum(grid [][]int) int {
    if len(grid) == 0 || len(grid[0]) == 0 {
        return 0
    }
    rows, columns := len(grid), len(grid[0])
    dp := make([][]int, rows)
    for i := 0; i < len(dp); i++ {
        dp[i] = make([]int, columns)
    }
    dp[0][0] = grid[0][0]
    for i := 1; i < rows; i++ {
        dp[i][0] = dp[i - 1][0] + grid[i][0]
    }
    for j := 1; j < columns; j++ {
        dp[0][j] = dp[0][j - 1] + grid[0][j]
    }
    for i := 1; i < rows; i++ {
        for j := 1; j < columns; j++ {
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j]
        }
    }
    return dp[rows - 1][columns - 1]
}

func min(x, y int) int {
    if x < y {
        return x
    }
    return y
}
```

## 100

`剑指 Offer II 100. 三角形中最小路径之和`

一个三角形的矩阵，从上往下找到最小路径之和

下标移动的时候只能移动到`i`以及`i+1`

```go
func minimumTotal(triangle [][]int) int {
    n := len(triangle)
    f := make([][]int, n)
    for i := 0; i < n; i++ {
        f[i] = make([]int, n)
    }
    f[0][0] = triangle[0][0]
    for i := 1; i < n; i++ {
        f[i][0] = f[i - 1][0] + triangle[i][0]
        for j := 1; j < i; j++ {
            f[i][j] = min(f[i - 1][j - 1], f[i - 1][j]) + triangle[i][j]
        }
        f[i][i] = f[i - 1][i - 1] + triangle[i][i]
    }
    ans := math.MaxInt32
    for i := 0; i < n; i++ {
        ans = min(ans, f[n-1][i])
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

## 101

`剑指 Offer II 101. 分割等和子集`

给定一个非空的正整数数组 nums ，请判断能否将这些数字分成元素和相等的两部分。

```go
func canPartition(nums []int) bool {
    n := len(nums)
    if n < 2 {
        return false
    }

    sum, max := 0, 0
    for _, v := range nums {
        sum += v
        if v > max {
            max = v
        }
    }
    if sum%2 != 0 {
        return false
    }

    target := sum / 2
    if max > target {
        return false
    }

    dp := make([][]bool, n)
    for i := range dp {
        dp[i] = make([]bool, target+1)
    }
    for i := 0; i < n; i++ {
        dp[i][0] = true
    }
    dp[0][nums[0]] = true
    for i := 1; i < n; i++ {
        v := nums[i]
        for j := 1; j <= target; j++ {
            if j >= v {
                dp[i][j] = dp[i-1][j] || dp[i-1][j-v]
            } else {
                dp[i][j] = dp[i-1][j]
            }
        }
    }
    return dp[n-1][target]
}
```

## 102

`剑指 Offer II 102. 加减的目标值`

给定一个数组以及target值，提供正负符号使得数组中的和等于目标值

```go
func findTargetSumWays(nums []int, target int) (count int) {
    var backtrack func(int, int)
    backtrack = func(index, sum int) {
        if index == len(nums) {
            if sum == target {
                count++
            }
            return
        }
        backtrack(index+1, sum+nums[index])
        backtrack(index+1, sum-nums[index])
    }
    backtrack(0, 0)
    return
}
```

## 103

剑指 Offer II 103. 最少的硬币数目

给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。

每种硬币的数量是无限的。

```go
func coinChange(nums []int, target int) int {
	dp := make([]int, target+1)
	for i := 1; i <= target; i++ {
		dp[i] = math.MaxInt32
	}
	for _, num := range nums {
		for i := 0; i <= target-num; i++ {
			if dp[i] == math.MaxInt32 {
				continue
			}
			dp[i+num] = min(dp[i+num], dp[i]+1)
		}
	}
	if dp[target] == math.MaxInt32 {
		return -1
	}
	return dp[target]
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
```

## 104

剑指 Offer II 104. 排列的数目

给定一个由 不同 正整数组成的数组 nums ，和一个目标整数 target 。请从 nums 中找出并返回总和为 target 的元素组合的个数。数组中的数字可以在一次排列中出现任意次，但是顺序不同的序列被视作不同的组合。

```go
func combinationSum4(nums []int, target int) int {
    dp := make([]int, target+1)
    dp[0] = 1
    for i := 1; i <= target; i++ {
        for _, num := range nums {
            if num <= i {
                dp[i] += dp[i-num]
            }
        }
    }
    return dp[target]
}
```

## 105

`剑指 Offer II 105. 岛屿的最大面积`

01二维矩阵，全1代表陆地，找到岛屿的最大面积

```go
func maxAreaOfIsland(grid [][]int) int {
	m, n := len(grid), len(grid[0])
	visited := make([][]bool, m)
	for i := 0; i < m; i++ {
		visited[i] = make([]bool, n)
	}
	var getArea func(int, int) int
	getArea = func(i, j int) int {
		if i < 0 || i == m || j < 0 || j == n {
			return 0
		}
		if grid[i][j] == 0 || visited[i][j] {
			return 0
		}
		visited[i][j] = true
		return getArea(i-1, j) + getArea(i+1, j) + getArea(i, j-1) + getArea(i, j+1) + 1
	}
	ans := 0
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			area := getArea(i, j)
			if area > ans {
				ans = area
			}
		}
	}
	return ans
}
```

## 106

`剑指 Offer II 106. 二分图`

二分图 定义：如果能将一个图的节点集合分割成两个独立的子集 A 和 B ，并使图中的每一条边的两个节点一个来自 A 集合，一个来自 B 集合，就将这个图称为 二分图 。

如果图是二分图，返回 true ；否则，返回 false 。

```go
// some comment
var (
    UNCOLOR, RED, GREEN = 0, 1, 2
)

func isBipartite(graph [][]int) bool {
    n := len(graph)

    state := make([]int, n)
    valid := true

    var dfs func(idx, color int)
    dfs = func(idx, color int) {
        necolor := RED
        if color == RED {
            necolor = GREEN
        }
        state[idx] = color

        for _, ne := range graph[idx] {
            if state[ne] == UNCOLOR {
                dfs(ne, necolor)
            } else {
                valid = necolor == state[ne]
            }

            if !valid {
                return
            }
        }
    }

    for i := 0; i < n && valid; i++ {
        if state[i] == UNCOLOR {
            dfs(i, RED)
        }
    }
    return valid
}
```

## 107

`剑指 Offer II 107. 矩阵中的距离`

一个01矩阵，找到每个元素距离其最近0的距离长度，结果用二维矩阵表达

```go
func updateMatrix(mat [][]int) [][]int {
	m := len(mat)
	n := len(mat[0])
	res := make([][]int, m)
	for i := range res {
		res[i] = make([]int, n)
	}
	dx := []int{1, 0, -1, 0}
	dy := []int{0, -1, 0, 1}
	var queue [][]int
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			if mat[i][j] == 0 {
				queue = append(queue, []int{i, j})
			}
		}
	}
	for len(queue) > 0 {
		x := queue[0][0]
		y := queue[0][1]
		queue = queue[1:]
		for k := 0; k < 4; k++ {
			nx := x + dx[k]
			ny := y + dy[k]
			if nx >= 0 && ny >= 0 && nx < m && ny < n && mat[nx][ny] == 1 {
				if res[nx][ny] == 0 || res[x][y]+1 < res[nx][ny] {
					res[nx][ny] = res[x][y] + 1
					queue = append(queue, []int{nx, ny})
				}
			}
		}
	}
	return res
}
```

## 108

`剑指 Offer II 108. 单词演变`

将单词从begin转换成end需要的最小步骤，并且每次的转换中间节点要在wordList中出现

```go
func ladderLength(beginWord string, endWord string, wordList []string) int {
    wordId := map[string]int{}
    graph := [][]int{}
    addWord := func(word string) int {
        id, has := wordId[word]
        if !has {
            id = len(wordId)
            wordId[word] = id
            graph = append(graph, []int{})
        }
        return id
    }
    addEdge := func(word string) int {
        id1 := addWord(word)
        s := []byte(word)
        for i, b := range s {
            s[i] = '*'
            id2 := addWord(string(s))
            graph[id1] = append(graph[id1], id2)
            graph[id2] = append(graph[id2], id1)
            s[i] = b
        }
        return id1
    }

    for _, word := range wordList {
        addEdge(word)
    }
    beginId := addEdge(beginWord)
    endId, has := wordId[endWord]
    if !has {
        return 0
    }

    const inf int = math.MaxInt64
    dist := make([]int, len(wordId))
    for i := range dist {
        dist[i] = inf
    }
    dist[beginId] = 0
    queue := []int{beginId}
    for len(queue) > 0 {
        v := queue[0]
        queue = queue[1:]
        if v == endId {
            return dist[endId]/2 + 1
        }
        for _, w := range graph[v] {
            if dist[w] == inf {
                dist[w] = dist[v] + 1
                queue = append(queue, w)
            }
        }
    }
    return 0
}
```

## 109

`剑指 Offer II 109. 开密码锁`

四个环形波轮组成的锁，找到转到目标值target的最小转动次数，另外不能转动到deadends列表中的数据

```go
func openLock(deadends []string, target string) int {
    if target == "0000" {
        return 0
    }

    deadendsSet := map[string]bool{}
    for _, item := range deadends {
        deadendsSet[item] = true
    }
    if deadendsSet[target] || deadendsSet["0000"] {
        return -1
    }

    visit := map[string]bool{}
    
    getnei := func(state string) []string {
        res := []string{}
        s := []byte(state)
        for i, ch := range s {
            s[i] = ch + 1
            if s[i] > '9' {
                s[i] = '0'
            }
            res = append(res, string(s))

            s[i] = ch - 1
            if s[i] < '0' {
                s[i] = '9'
            }
            res = append(res, string(s))

            s[i] = ch
        }
        return res
    }
    
    queue := []string{"0000"}
    step := 0
    for len(queue) > 0 {
        newqueue := []string{}
        for _, state := range queue {
            for _, ne := range getnei(state) {
                if !visit[ne] && !deadendsSet[ne] {
                    if ne == target {
                        return step + 1
                    }
                    visit[ne] = true
                    newqueue = append(newqueue, ne)
                }
            }
        }
        queue = newqueue
        step++
    }
    return -1
}
```

## 110

`剑指 Offer II 110. 所有路径`

给定一个邻接矩阵结构，用于表示一个有向有环图，找到其中的所有的从0到n-1节点的路径

```go
func allPathsSourceTarget(graph [][]int) (ans [][]int) {
    stk := []int{0}
    var dfs func(int)
    dfs = func(x int) {
        if x == len(graph)-1 {
            ans = append(ans, append([]int{}, stk...))
            return
        }
        for _, y := range graph[x] {
            stk = append(stk, y)
            dfs(y)
            stk = stk[:len(stk)-1]
        }
    }
    dfs(0)
    return
}
```

## 111

`剑指 Offer II 111. 计算除法`

给定一些已知变量除法获取到的值，提供数据查询结果

```go
func calcEquation(equations [][]string, values []float64, queries [][]string) []float64 {
    // 给方程组中的每个变量编号
    id := map[string]int{}
    for _, eq := range equations {
        a, b := eq[0], eq[1]
        if _, has := id[a]; !has {
            id[a] = len(id)
        }
        if _, has := id[b]; !has {
            id[b] = len(id)
        }
    }

    // 建图
    type edge struct {
        to     int
        weight float64
    }
    graph := make([][]edge, len(id))
    for i, eq := range equations {
        v, w := id[eq[0]], id[eq[1]]
        graph[v] = append(graph[v], edge{w, values[i]})
        graph[w] = append(graph[w], edge{v, 1 / values[i]})
    }

    bfs := func(start, end int) float64 {
        ratios := make([]float64, len(graph))
        ratios[start] = 1
        queue := []int{start}
        for len(queue) > 0 {
            v := queue[0]
            queue = queue[1:]
            if v == end {
                return ratios[v]
            }
            for _, e := range graph[v] {
                if w := e.to; ratios[w] == 0 {
                    ratios[w] = ratios[v] * e.weight
                    queue = append(queue, w)
                }
            }
        }
        return -1
    }

    ans := make([]float64, len(queries))
    for i, q := range queries {
        start, hasS := id[q[0]]
        end, hasE := id[q[1]]
        if !hasS || !hasE {
            ans[i] = -1
        } else {
            ans[i] = bfs(start, end)
        }
    }
    return ans
}
```

## 112

`剑指 Offer II 112. 最长递增路径`

给定一个 m x n 整数矩阵 matrix ，找出其中 最长递增路径 的长度。

```go
var (
    dirs = [][2]int{
        {-1, 0}, 
        {1, 0},
        {0, -1},
        {0, 1},
    }
    rows, columns int
)

func longestIncreasingPath(matrix [][]int) int {
    if len(matrix) == 0 || len(matrix[0]) == 0 {
        return 0
    }
    rows, columns = len(matrix), len(matrix[0])
    outdegrees := make([][]int, rows)
    for i := 0; i < rows; i++ {
        outdegrees[i] = make([]int, columns)
    }
    for i := 0; i < rows; i++ {
        for j := 0; j < columns; j++ {
            for _, dir := range dirs {
                newRow, newColumn := i + dir[0], j + dir[1]
                if newRow >= 0 && newRow < rows && newColumn >= 0 && newColumn < columns && matrix[newRow][newColumn] > matrix[i][j] {
                    outdegrees[i][j]++
                }
            }
        }
    }

    queue := [][]int{}
    for i := 0; i < rows; i++ {
        for j := 0; j < columns; j++ {
            if outdegrees[i][j] == 0 {
                queue = append(queue, []int{i, j})
            }
        }
    }
    ans := 0
    for len(queue) != 0 {
        ans++
        size := len(queue)
        for i := 0; i < size; i++ {
            cell := queue[0]
            queue = queue[1:]
            row, column := cell[0], cell[1]
            for _, dir := range dirs {
                newRow, newColumn := row + dir[0], column + dir[1]
                if newRow >= 0 && newRow < rows && newColumn >= 0 && newColumn < columns && matrix[newRow][newColumn] < matrix[row][column] {
                    outdegrees[newRow][newColumn]--
                    if outdegrees[newRow][newColumn] == 0 {
                        queue = append(queue, []int{newRow, newColumn})
                    }
                }
            }
        }
    }
    return ans
}
```

## 113

`剑指 Offer II 113. 课程顺序`

总共n门课，并且有一些先后依赖顺序，返回要完成所有课程所需要的一个正确的课程顺序

```go
func findOrder(numCourses int, prerequisites [][]int) []int {
    var (
        edges = make([][]int, numCourses)
        indeg = make([]int, numCourses)
        result []int
    )

    for _, info := range prerequisites {
        edges[info[1]] = append(edges[info[1]], info[0])
        indeg[info[0]]++
    }

    q := []int{}
    for i := 0; i < numCourses; i++ {
        if indeg[i] == 0 {
            q = append(q, i)
        }
    }

    for len(q) > 0 {
        u := q[0]
        q = q[1:]
        result = append(result, u)
        for _, v := range edges[u] {
            indeg[v]--
            if indeg[v] == 0 {
                q = append(q, v)
            }
        }
    }
    if len(result) != numCourses {
        return []int{}
    }
    return result
}
```

## 114

`剑指 Offer II 114. 外星文字典`

通过已知的满足特定顺序的字符串数组，来推导出这个而特定的顺序

```go
func alienOrder(words []string) string {
    g := map[byte][]byte{}
    inDeg := map[byte]int{}
    for _, c := range words[0] {
        inDeg[byte(c)] = 0
    }
next:
    for i := 1; i < len(words); i++ {
        s, t := words[i-1], words[i]
        for _, c := range t {
            inDeg[byte(c)] += 0
        }
        for j := 0; j < len(s) && j < len(t); j++ {
            if s[j] != t[j] {
                g[s[j]] = append(g[s[j]], t[j])
                inDeg[t[j]]++
                continue next
            }
        }
        if len(s) > len(t) {
            return ""
        }
    }

    order := make([]byte, len(inDeg))
    q := order[:0]
    for u, d := range inDeg {
        if d == 0 {
            q = append(q, u)
        }
    }
    for len(q) > 0 {
        u := q[0]
        q = q[1:]
        for _, v := range g[u] {
            if inDeg[v]--; inDeg[v] == 0 {
                q = append(q, v)
            }
        }
    }
    if cap(q) == 0 {
        return string(order)
    }
    return ""
}
```

## 115

`剑指 Offer II 115. 重建序列`

https://leetcode.cn/problems/ur2n8P/?favorite=e8X3pBZi

```go
func sequenceReconstruction(nums []int, sequences [][]int) bool {
    n := len(nums)
    g := make([][]int, n+1)
    inDeg := make([]int, n+1)
    for _, sequence := range sequences {
        for i := 1; i < len(sequence); i++ {
            x, y := sequence[i-1], sequence[i]
            g[x] = append(g[x], y)
            inDeg[y]++
        }
    }

    q := []int{}
    for i := 1; i <= n; i++ {
        if inDeg[i] == 0 {
            q = append(q, i)
        }
    }
    for len(q) > 0 {
        if len(q) > 1 {
            return false
        }
        x := q[0]
        q = q[1:]
        for _, y := range g[x] {
            if inDeg[y]--; inDeg[y] == 0 {
                q = append(q, y)
            }
        }
    }
    return true
}
```

## 116

`剑指 Offer II 116. 省份数量`

省份 是一组直接或间接相连的城市，组内不含其他没有相连的城市。

给你一个 n x n 的矩阵 isConnected ，其中 isConnected[i][j] = 1 表示第 i 个城市和第 j 个城市直接相连，而 isConnected[i][j] = 0 表示二者不直接相连。

返回矩阵中 省份 的数量。

```go
func findCircleNum(isConnected [][]int) (ans int) {
    n := len(isConnected)
    parent := make([]int, n)
    for i := range parent {
        parent[i] = i
    }
    var find func(int) int
    find = func(x int) int {
        if parent[x] != x {
            parent[x] = find(parent[x])
        }
        return parent[x]
    }
    union := func(from, to int) {
        parent[find(from)] = find(to)
    }

    for i, row := range isConnected {
        for j := i + 1; j < n; j++ {
            if row[j] == 1 {
                union(i, j)
            }
        }
    }
    for i, p := range parent {
        if i == p {
            ans++
        }
    }
    return
}
```

## 117

`剑指 Offer II 117. 相似的字符串`

寻找一个字符串数组中，有多少个分组，这些分组里面都是同一种字母异位词。

```go
type unionFind struct {
    parent, size []int
    setCount     int // 当前连通分量数目
}

func newUnionFind(n int) *unionFind {
    parent := make([]int, n)
    size := make([]int, n)
    for i := range parent {
        parent[i] = i
        size[i] = 1
    }
    return &unionFind{parent, size, n}
}

func (uf *unionFind) find(x int) int {
    if uf.parent[x] != x {
        uf.parent[x] = uf.find(uf.parent[x])
    }
    return uf.parent[x]
}

func (uf *unionFind) union(x, y int) {
    fx, fy := uf.find(x), uf.find(y)
    if fx == fy {
        return
    }
    if uf.size[fx] < uf.size[fy] {
        fx, fy = fy, fx
    }
    uf.size[fx] += uf.size[fy]
    uf.parent[fy] = fx
    uf.setCount--
}

func (uf *unionFind) inSameSet(x, y int) bool {
    return uf.find(x) == uf.find(y)
}

func isSimilar(s, t string) bool {
    diff := 0
    for i := range s {
        if s[i] != t[i] {
            diff++
            if diff > 2 {
                return false
            }
        }
    }
    return true
}

func numSimilarGroups(strs []string) int {
    n := len(strs)
    uf := newUnionFind(n)
    for i, s := range strs {
        for j := i + 1; j < n; j++ {
            if !uf.inSameSet(i, j) && isSimilar(s, strs[j]) {
                uf.union(i, j)
            }
        }
    }
    return uf.setCount
}
```

## 118

`剑指 Offer II 118. 多余的边`

给定一个无向图，找到找出一条可以删除的边，使其变为树

```go
func findRedundantConnection(edges [][]int) []int {
    parent := make([]int, len(edges)+1)
    for i := range parent {
        parent[i] = i
    }
    var find func(int) int
    find = func(x int) int {
        if parent[x] != x {
            parent[x] = find(parent[x])
        }
        return parent[x]
    }
    union := func(from, to int) bool {
        x, y := find(from), find(to)
        if x == y {
            return false
        }
        parent[x] = y
        return true
    }
    for _, e := range edges {
        if !union(e[0], e[1]) {
            return e
        }
    }
    return nil
}
```

## 119

`剑指 Offer II 119. 最长连续序列`

给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

要求时间复杂度为O(n)

```go
func longestConsecutive(nums []int) int {
    numSet := map[int]bool{}
    for _, num := range nums {
        numSet[num] = true
    }
    longestStreak := 0
    for num := range numSet {
        if !numSet[num-1] {
            currentNum := num
            currentStreak := 1
            for numSet[currentNum+1] {
                currentNum++
                currentStreak++
            }
            if longestStreak < currentStreak {
                longestStreak = currentStreak
            }
        }
    }
    return longestStreak
}
```