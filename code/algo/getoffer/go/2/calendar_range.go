package main

type MyCalendar struct {
	tree, lazy map[int]bool
}

func NewMyCalendar() MyCalendar {
	return MyCalendar{map[int]bool{}, map[int]bool{}}
}

func (c MyCalendar) query(start, end, l, r, idx int) bool {
	if r < start || end < l {
		return false
	}
	if c.lazy[idx] { // 如果该区间已被预订，则直接返回
		return true
	}
	if start <= l && r <= end {
		return c.tree[idx]
	}
	mid := (l + r) >> 1
	return c.query(start, end, l, mid, 2*idx) ||
		c.query(start, end, mid+1, r, 2*idx+1)
}

func (c MyCalendar) update(start, end, l, r, idx int) {
	if r < start || end < l {
		return
	}
	if start <= l && r <= end {
		c.tree[idx] = true
		c.lazy[idx] = true
	} else {
		mid := (l + r) >> 1
		c.update(start, end, l, mid, 2*idx)
		c.update(start, end, mid+1, r, 2*idx+1)
		c.tree[idx] = true
		if c.lazy[2*idx] && c.lazy[2*idx+1] {
			c.lazy[idx] = true
		}
	}
}

func (c MyCalendar) Book(start, end int) bool {
	if c.query(start, end-1, 0, 1e9, 1) {
		return false
	}
	c.update(start, end-1, 0, 1e9, 1)
	return true
}
