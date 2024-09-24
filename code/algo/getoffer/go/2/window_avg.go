package main

type MovingAverage struct {
	size, sum int
	q         []int
}

func Constructor(size int) MovingAverage {
	return MovingAverage{size: size}
}

func (m *MovingAverage) Next(val int) float64 {
	if len(m.q) == m.size {
		m.sum -= m.q[0]
		m.q = m.q[1:]
	}
	m.sum += val
	m.q = append(m.q, val)
	return float64(m.sum) / float64(len(m.q))
}
