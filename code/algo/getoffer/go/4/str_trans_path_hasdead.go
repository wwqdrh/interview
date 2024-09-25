package main

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
