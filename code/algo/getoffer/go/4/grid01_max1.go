package main

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
