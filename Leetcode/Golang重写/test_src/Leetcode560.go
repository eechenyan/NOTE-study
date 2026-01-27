// 560. 和为K的子数组

// 给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数。

// 子数组是数组中元素的连续非空序列。

// 前缀和 + 哈希表

// 得到前缀和数组 这道题后面的处理逻辑是两数之差 如果当前下标-k得到的数字存在于前面遍历得到的情况 那么这个当前下标减去检索到的下标就是一个满足答案的区间 因为他们之间相差k

package main

import "fmt"

func FindCount(nums []int, k int) int {
	if len(nums) == 0 {
		return 0
	}
	var umap map[int]int = make(map[int]int, len(nums))
	var result int = 0;
	var pre_sum []int = make([]int, len(nums))
	umap[0] = 1
	pre_sum[0] = nums[0]
	for i,n := 1, len(nums); i < n; i++ {
		pre_sum[i] = pre_sum[i - 1] + nums[i]
	}

	for i,n := 0, len(nums); i < n; i++ {
		var target int = pre_sum[i] - k
		value, exit := umap[target] //如果exit 那么 _ 就是对应的value
		if exit {
			result = result + value;
		}
		umap[pre_sum[i]]++;
	}
	return result
}

func main() {
	var nums []int = []int{1,1,1}
	var k int = 2
	fmt.Println("result is:", FindCount(nums, k))
}