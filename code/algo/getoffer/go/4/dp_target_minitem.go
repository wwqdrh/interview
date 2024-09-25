package main

import "math"

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
