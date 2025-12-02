// 287. 寻找重复数

// 给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和 n），可知至少存在一个重复的整数。

// 假设 nums 只有 一个重复的整数 ，返回 这个重复的数 。

// 你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1) 的额外空间。

// nums = [1,3,4,2,2] 4 + 1 [1 4]
// 输出：2

// 思路就是对于 当作下标 如果遇到重复的数组 那么 0 - n  一个数字n - 1那么就是下标 第一次遍历变成负数 如果再一次遇到了 然后如果是负数 那么就是?

package main

import "fmt"

func FindReNums(nums []int) int {
	var result int = 0; 
	for _, value := range nums {
		fmt.Println("value is:", value);
		var index int = 0;
		if value < 0 {
			index = -value;
		} else {
			index = value;
		}
		var i int = index - 1;
		if nums[i] < 0 {
			if value < 0 {
				result = -value;
			} else {
				result = value;
			}
		} else {
			nums[i] = -nums[i];
		}
	}
	return result;
}

func main() {
	var nums []int = []int{3,1,3,4,2};
	fmt.Println("result is :", FindReNums(nums));
}