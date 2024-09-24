package main

type RecentCounter []int

func NewRecentCounter() (_ RecentCounter) { return }

func (q *RecentCounter) Ping(t int) int {
	*q = append(*q, t)
	for (*q)[0] < t-3000 {
		*q = (*q)[1:]
	}
	return len(*q)
}
