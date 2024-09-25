package main

import (
	"math/rand"
	"sort"
)

type WeightRandom struct {
	pre []int
}

func NewWeightRandom(w []int) WeightRandom {
	for i := 1; i < len(w); i++ {
		w[i] += w[i-1]
	}
	return WeightRandom{w}
}

func (s *WeightRandom) PickIndex() int {
	x := rand.Intn(s.pre[len(s.pre)-1]) + 1
	return sort.SearchInts(s.pre, x)
}
