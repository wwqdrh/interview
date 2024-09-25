package main

// 动态规划版本
func generateParenthesisDP(n int) []string {
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
func generateParenthesisDFS(n int) []string {
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
