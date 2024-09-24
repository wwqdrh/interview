package main

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
