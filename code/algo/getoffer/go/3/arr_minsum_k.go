package main

import "container/heap"

func kSmallestPairs(nums1, nums2 []int, k int) (ans [][]int) {
	h := hp{nums1: nums1, nums2: nums2}
	m, n := len(nums1), len(nums2)
	for i := 0; i < k && i < m; i++ {
		heap.Push(&h, pair{i, 0})
	}
	for h.Len() > 0 && len(ans) < k {
		p := heap.Pop(&h).(pair)
		i, j := p.i, p.j
		ans = append(ans, []int{nums1[i], nums2[j]})
		if j+1 < n {
			heap.Push(&h, pair{i, j + 1})
		}
	}
	return
}

type hp struct {
	data         []pair
	nums1, nums2 []int
}

type pair struct {
	i, j int
}

func (h hp) Len() int {
	return len(h.data)
}

func (h hp) Less(i, j int) bool {
	p1, p2 := h.data[i], h.data[j]
	return h.nums1[p1.i]+h.nums2[p1.j] < h.nums1[p2.i]+h.nums2[p2.j]
}

func (h hp) Swap(i, j int) {
	h.data[i], h.data[j] = h.data[j], h.data[i]
}

func (h *hp) Push(val interface{}) {
	h.data = append(h.data, val.(pair))
}

func (h *hp) Pop() interface{} {
	data := h.data
	val := data[len(data)-1]
	h.data = data[:len(data)-1]
	return val
}
