// 三数之和
// 获得三个数字的下标
// 三指针不能使用哈希表的
package main

import "fmt"
import "sort"

func FindNums(nums []int, target int) [][]int {
	var result [][]int = make([][]int, 0);
	sort.Ints(nums);
	for i, n := 0, len(nums); i < n; i++ {
		if i > 0 && nums[i] == nums[i - 1] {
			continue;
		}
		var left int = i + 1;
		var right int = len(nums) - 1;
		for left < right {
			var sum int = nums[i] + nums[left] + nums[right];
			if sum < target {
				left++;
			} else if sum > target {
				right--;
			} else {
				result = append(result, []int{nums[i], nums[left], nums[right]});
				for left < right && nums[left] == nums[left + 1] {
					left++;
				}
				for left < right && nums[right] == nums[right - 1] {
					right--;
				}
				left++;
				right--;
			}
		}
	}
	return result;
}

func main() {
	var nums []int = []int{-1,0,1,2,-1,-4};
	var target int = 0;
	fmt.Println("result is:", FindNums(nums, target));
}