// 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
// 你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。
// 你可以按任意顺序返回答案。
package main;

import "fmt";

func findIndex(nums []int, target int) []int { // funcd的参数是 变量名 类型 返回值是 类型
	var numsmap map[int]int = make(map[int]int);
	var result []int = make([]int , 0);
	for index,value := range nums {
		var findnum = target - value;
		otherIndex, exists := numsmap[findnum];
		if exists == true {
			result = append(result, otherIndex, index);
		} else {
			numsmap[value] = index;
		}
	}
	return result;
};

func main()  {
	fmt.Println("hello word");
	var nums []int = []int{2,7,11,15};
	var target int = 9;
	var result []int;
	result = findIndex(nums,target);
	fmt.Println(result);
}