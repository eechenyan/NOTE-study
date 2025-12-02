
package main

import "fmt"

func MoveZero(nums []int) []int {
	var left int = 0;
	var right int = len(nums) - 1;
	for left < right {
		if nums[right] == 0 {
			right--;
		} else {
			nums[left], nums[right] = nums[right], nums[left];
			right--;
		}
	}
	return nums;
}

func main() {
	var nums []int = []int{0,1,0,3,12};
	fmt.Println("result is:", MoveZero(nums));
}