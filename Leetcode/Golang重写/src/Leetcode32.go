package main

import "fmt"

func FindMaxLen(s string) int {
	// 一个满足的可能的一定是连续不交叉的
	var start int = 0;
	var max_len int = 0;
	var stack []int = make([]int, 0);
	for index,value := range s {
		if value == '(' {
			stack = append(stack, index);
		} else {
			if len(stack) != 0 {
				stack = stack[: len(stack) - 1]; //先进后出
				if len(stack) == 0 {
					max_len = max(max_len, index - start + 1);
				} else {
					max_len = max(max_len, index - stack[len(stack) - 1]);
				}
			} else {
				start = index + 1;
			}
		}
	}
	return max_len;
}

func main() {
	var s string = ")()()())(()";
	fmt.Println("result is:", FindMaxLen(s));
}