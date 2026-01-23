// 滑动窗口最大值
// 对于给定的一个数组 求k个一组的最大值
// 滑动窗口的思路是 存储可能的极值 注意存储的是下标 每次压入数字 维护这个双端单调队列

package main

import "fmt"

func FindMax(nums []int, k int) []int {
	// 1.创建一个双端队列
	var deque []int = make([]int, 0);
	var result []int = make([]int, 0);
	// 2.遍历数组 维护双端队列的单调减特性
	for i,n := 0, len(nums); i < n; i++ {
		// 3.压入队列
		for len(deque) > 0 && nums[i] >= nums[deque[len(deque) - 1]] {
			// 4.出队
			deque = deque[1:];
		}
		// 5.入队
		deque = append(deque, i);
		// 6.判断是否超出范围
		for i - deque[0] + 1 > k {
			deque = deque[1:];
		}
		// 7.形成窗口 存入结果
		if i - 0 + 1 >= k {
			result = append(result, nums[deque[0]]);
		}
	}
	return result;
}

func main() {
	var nums []int = []int{1,3,-1,-3,5,3,6,7};
	var k int = 3;
	fmt.Println(FindMax(nums, k));
}