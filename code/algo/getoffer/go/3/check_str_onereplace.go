package main

type MagicDictionary struct {
	trie *trie
}

type trie struct {
	children [26]*trie
	isEnd    bool
}

/** Initialize your data structure here. */
func NewMagicDictionary() MagicDictionary {
	return MagicDictionary{trie: &trie{}}
}

func (this *MagicDictionary) BuildDict(dictionary []string) {
	for _, word := range dictionary {
		cur := this.trie
		for _, ch := range word {
			idx := ch - 'a'
			if cur.children[idx] == nil {
				cur.children[idx] = &trie{}
			}
			cur = cur.children[idx]
		}
		cur.isEnd = true
	}
}

func (this *MagicDictionary) Search(searchWord string) bool {
	var dfs func(node *trie, searchWord string, modified bool) bool
	dfs = func(node *trie, searchWord string, modified bool) bool {
		if searchWord == "" {
			return modified && node.isEnd
		}
		c := searchWord[0] - 'a'
		if node.children[c] != nil && dfs(node.children[c], searchWord[1:], modified) {
			return true
		}
		if !modified {
			for i, child := range node.children {
				if i != int(c) && child != nil && dfs(child, searchWord[1:], true) {
					return true
				}
			}
		}
		return false
	}
	return dfs(this.trie, searchWord, false)
}
