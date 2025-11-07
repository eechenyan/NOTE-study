package main

import "fmt"
// go直接使用[]int 模拟stack的操作
func findtemperature(temperature []int) []int {
	var result []int = make([]int, len(temperature));
	var stack []int = make([]int, 0);
	for i,n := 0, len(temperature); i<n; i++ {
		for len(stack) != 0 && temperature[i] > temperature[stack[len(stack) - 1]] {
			var preindex int = stack[len(stack) - 1];
			result[preindex] = i - preindex;
			stack = stack[:len(stack) - 1];
		}
		stack = append(stack,i);
	}
	return result;
}

func main() {
	var temperature []int = []int{73,74,75,71,69,72,76,73};
	fmt.Println(findtemperature(temperature));
}
