package main

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
				path = path[:len(path)-1]
			}
		}
	}
	dfs()
	return ans
}
