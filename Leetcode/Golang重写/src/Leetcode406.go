package main

import "fmt"
import "sort"


// go写的我真的难受
func ReQueue(people [][]int) [][]int {
	// 你就记得这里的Slice函数就是正在对people排序就是了
	sort.Slice(people, func(i,j int) bool{ 
		//匿名函数有匿名函数的写法 不同于一般的函数 
		people1, people2 := people[i], people[j];
		if people1[0] > people2[0] {
			return true;
		} else if people1[0] == people2[0] {
			if people1[1] < people2[1] {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}) // 匿名函数记得闭合 
	return people;
}

func main() {
	var nums [][]int  = [][]int{{6,0},{5,0},{4,0},{3,2},{2,2},{1,4}}
	var people = ReQueue(nums);
	var que [][]int = make([][]int, 0);
	for _,value := range people {
		var _ int = value[0];
		var k int = value[1];
		que = append(que[:k], append([][]int{value}, que[k:]...)...);
	}
	fmt.Println("que is", que);
}