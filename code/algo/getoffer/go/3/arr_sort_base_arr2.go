package main

import "sort"

type zset map[int]int

func (zs *zset) keys() []int {
	res := []int{}
	for key := range *zs {
		res = append(res, key)
	}
	sort.Ints(res)
	return res
}

func relativeSortArray(arr1 []int, arr2 []int) []int {
	zs := zset{}
	for _, val := range arr1 {
		zs[val]++
	}

	res := make([]int, 0, len(arr1))
	for _, val := range arr2 {
		for i := 0; i < zs[val]; i++ {
			res = append(res, val)
		}
		delete(zs, val)
	}
	for _, key := range zs.keys() {
		for i := 0; i < zs[key]; i++ {
			res = append(res, key)
		}
	}
	return res
}
