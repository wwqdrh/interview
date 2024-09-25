package main

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
