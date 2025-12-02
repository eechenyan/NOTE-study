package main

import "fmt"

func Quick(nums []int, i int, j int) int {
	var base int = nums[i];
	for i < j {
		for i < j && nums[j] >= base {j--;}
		nums[i] = nums[j];
		for i < j && nums[i] <= base {i++;}
		nums[j] = nums[i];
	}
	nums[i] = base;
	return i;
}

func QuickSort(nums []int, i int, j int, y int) {
	if j < i {return ;} //下标不合法
	if j == i {return ;} //一个数字天然有序
	var base int = Quick(nums, i, j);
	if(base > y) {
		QuickSort(nums, i, base - 1, y);
	} else if(base < y){
		QuickSort(nums, base + 1, j, y);
	} else {
		return ;
	}
}


func findKthNums(nums []int, k int) {
	QuickSort(nums, 0, len(nums) - 1, len(nums) - k);
}
func main() {
	var nums []int = []int{3,2,3,1,2,4,5,5,6};
	var k int = 4;
	findKthNums(nums,k);
	fmt.Println("nums数组是:" , nums);
	fmt.Println("第k的数字是:" , nums[len(nums) - k]);
}