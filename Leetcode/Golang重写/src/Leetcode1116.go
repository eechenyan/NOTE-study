// 输入：n = 2
// 输出："0102"
// 解释：三条线程异步执行，其中一个调用 zero()，另一个线程调用 even()，最后一个线程调用odd()。正确的输出为 "0102"。
// 示例 2：

// 输入：n = 5
// 输出："0102030405"
 
// 思路是起三个线程包括一个main主线程 然后使用一个map控制不同的chan 根据不同的chan来控制哪一个线程启动

package main;
import "fmt";

var map_thread map[int]chan int = make(map[int]chan int, 3);
var is_ok chan bool = make(chan bool);
var print_number int = 1;

func PrintZero(count int) {
	for i,n := 0,count ; i < n; i++ {
		<- map_thread[0];
		fmt.Printf("%d",0);
		is_ok <- true;
	}
}

func PrintOdd(count int) {
	for i,n := 1,count ; i <= n; i++ {
		<-map_thread[1];
		fmt.Printf("%d",print_number);
		print_number++;
		is_ok <- true;
	}
}

func PrintEven(count int) {
	for i,n := 2,count ; i <= n; i++ {
		<- map_thread[2];
		fmt.Printf("%d",print_number);
		print_number++;
		is_ok <- true;
	}
}

func main() {
	for i,n := 0,3; i < n; i++ {
		map_thread[i] = make(chan int)
	}
	go PrintZero(5);
	go PrintEven(5);
	go PrintOdd(5);

	for i,n := 0,5; i < n; i++ {
		map_thread[0] <- 1;
		// <- is_ok;
		if i % 2 == 0{
			map_thread[2] <- 1;
		} else {
			map_thread[1] <- 1;
		}
		<- is_ok;
	}
}