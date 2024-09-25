package main

type WordEncodeTrie struct {
	child [26]*WordEncodeTrie
	depth int
}

func NewTrie() *WordEncodeTrie {
	return &WordEncodeTrie{
		child: [26]*WordEncodeTrie{},
		depth: 1,
	}
}

func (t *WordEncodeTrie) Insert(word string) {
	curr := t
	n := len(word)
	for i := n - 1; i >= 0; i-- {
		c := word[i] - 'a'
		if curr.child[c] == nil {
			curr.child[c] = NewTrie()
		}
		curr.child[c].depth = curr.depth + 1
		curr = curr.child[c]
	}
}

func minimumLengthEncoding(words []string) int {
	t := NewTrie()
	for _, w := range words {
		t.Insert(w)
	}
	var res int
	var dfs func(node *WordEncodeTrie)
	dfs = func(node *WordEncodeTrie) {
		var hasChild bool
		for i := 0; i < 26; i++ {
			if node.child[i] != nil {
				hasChild = true
				dfs(node.child[i])
			}
		}
		if !hasChild {
			res += node.depth
		}
	}
	dfs(t)
	return res
}
