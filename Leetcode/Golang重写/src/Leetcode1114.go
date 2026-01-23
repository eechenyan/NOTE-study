// 输入：nums = [1,3,2]
// 输出："firstsecondthird"
// 解释：
// 输入 [1,3,2] 表示线程 A 将会调用 first() 方法，线程 B 将会调用 third() 方法，线程 C 将会调用 second() 方法。正确的输出是 "firstsecondthird"。

// 起三个协程 然后主协程从nums里面取出数字 传给 对应的chan 使用同步信号量来指定顺序来打印


package main

import "fmt"

var is_ok chan bool = make(chan bool, 1);
var map_thread map[int]chan int = make(map[int]chan int, 3);

func first() {
	var num int;
	num=<-map_thread[0];
	fmt.Println("first",num)
	is_ok <- true
	
}

func second() {
	var num int;
	num=<-map_thread[1];
	fmt.Println("second",num)
	is_ok <- true
}

func third() {
	var num int;
	num=<-map_thread[2];
	fmt.Println("third",num)
	is_ok <- true
}

func main() {
	for i,n := 0, 3; i < n; i++ {
		map_thread[i] = make(chan int, 1);
	}
	go first();
	go second();
	go third();
	var nums []int = []int{1,3,2};
	for i,n := 0, len(nums); i < n; i++ {
		map_num := nums[i] - 1;
		map_thread[map_num] <- map_num;
		<-is_ok;
	}
}

























// package main

// import "fmt"

// var map_thread map[int]chan int = make(map[int]chan int, 3)
// var is_ok chan bool = make(chan bool)

// func first() {
// 	for{
// 		<- map_thread[0]
// 		fmt.Printf("first ")
// 		is_ok <- true
// 	}
// }

// func second() {
// 	<- map_thread[1]
// 	fmt.Printf("second ")
// 	is_ok <- true
// }

// func third() {
// 	<- map_thread[2]
// 	fmt.Printf("third ")
// 	is_ok <- true
// }



// func Solutin(nums []int) {
// 	for i,n := 0,3; i < n; i++ {
// 		map_thread[i] = make(chan int)
// 	} 
// 	go first()
// 	go second()
// 	go third()
// 	for i,n := 0,len(nums); i < n; i++ {
// 		var id int = nums[i] - 1
// 		map_thread[id] <- id
// 		<- is_ok
// 	}
// }

// func main() {
// 	nums := []int{3, 1, 1}
// 	Solutin(nums)
// }