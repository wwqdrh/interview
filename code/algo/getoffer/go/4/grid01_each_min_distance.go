package main

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
