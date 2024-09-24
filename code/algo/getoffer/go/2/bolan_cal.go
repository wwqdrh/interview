package main

import "strconv"

func evalRPN(tokens []string) int {
	stack := make([]int, (len(tokens)+1)/2)
	index := -1
	for _, token := range tokens {
		val, err := strconv.Atoi(token)
		if err == nil {
			index++
			stack[index] = val
		} else {
			index--
			switch token {
			case "+":
				stack[index] += stack[index+1]
			case "-":
				stack[index] -= stack[index+1]
			case "*":
				stack[index] *= stack[index+1]
			default:
				stack[index] /= stack[index+1]
			}
		}
	}
	return stack[0]
}
