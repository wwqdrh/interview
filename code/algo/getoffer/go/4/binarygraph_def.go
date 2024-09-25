package main

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
