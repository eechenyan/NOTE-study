// ----------------------------------------------------------------------此文件用来验证学习go过程中的各种想要验证的想法----------------------------------------------------------------//

package main
import "fmt"
// import "time"

// 1.验证defer执行顺序
// func test() int {
// 	var ret int = 0
// 	defer func () {
// 		fmt.Println("This is first defer")
// 	}()
// 	defer func () {
// 		fmt.Println("This is second defer")
// 	}()
// 	return ret
// }

// 2.体验闭包功能
// func test() func() int {
// 	var count int = 0 // 被捕获的状态变量（私有，外部无法直接修改）
// 	f:= func() int { // 闭包 用于捕获私有变量并返回
// 		count++
// 		fmt.Println("count is %d", count)
// 		return count
// 	} 
// 	return f // 返回一个函数声明加实现
// }

// // 3.验证遍历map是无序的
// func PrintMap() {
// 	var umap map[int]int = make(map[int]int)
// 	for i, n := 0, 9; i < n; i++ {
// 		umap[i] = i
// 	}
// 	// map不可以使用i顺序遍历 这个是错误的 只能使用range范围遍历 c++也是只能范围遍历（使用迭代器）
// 	// for i, n :=0, len(umap); i < n; i++ {
// 	// 	fmt.Println("umap[%d] is %d", i, umap[i])
// 	// }
// 	for key,value := range umap {
// 		fmt.Printf("umap[%d] is %d ", key, value)
// 	}
// 	fmt.Printf("\n")
// }

// // 4.使用一下golang里面的channel 
// func send(ch chan int) {
// 	fmt.Printf("send:正在发送数据到channal\n")
// 	ch <- 1
// 	fmt.Printf("send:数据已经发送完到channal了\n")
// }

// func receive(ch chan int) {
// 	time.Sleep(1 * time.Second) // 模拟耗时操作
// 	fmt.Printf("receive:正在从channal中取数据\n")
// 	var num int = <- ch
// 	time.Sleep(1 * time.Second) // 模拟耗时操作
// 	fmt.Printf("receive:数据取出来了,是%d\n",num)
// }

// 5.开启100个协程，顺序打印1-1000，且保证协程号1的，打印尾数为1的数字
// 思路是使用一个对应关系的容器实现当前数字交给哪一个协程去打印 这个实现最好的就是map了
// 最好采用匿名函数去做 这里不采用匿名函数的话就需要全局变量了
// var is_ok chan bool = make(chan bool) // 同步变量 检查是否打印完了
// var map_thread map[int]chan int = make(map[int]chan int, 100) //100个哈希表，对应100和协程
// func PrintNums(id int) {
// 	for {
// 		var num int = <-map_thread[id]
// 		fmt.Printf("goruntinue%d is printing %d \n",id, num)
// 		is_ok <- true //写入同步变量 表示已经完成 这个信号量告诉主协程main已经完成一个操作了 
// 	}
// }

// 6.三个goroutinue交替打印abc 10次
// 和5一样的思路 使用信号量进行主协程同步 然后指定一个字母丢给确定的那个协程去打印
var is_ok chan bool = make(chan bool) //实现顺序的核心 不过没有这个的话 main会不断的丢数据进chan 这样子消费者也不会按照顺序去去 会乱去取 这样子打印就乱套了
var map_thread map[byte]chan byte = make(map[byte]chan byte, 3)
func PrintChar(c byte) {
	for {
		var char byte = <- map_thread[c]
		fmt.Printf("thread %c : %c \n", c, char)
		is_ok <- true
	}
}
func main() {
	// ------------------1.defer---------------------
	// fmt.Println("This is main", test()) 

	// ------------------2.闭包----------------------
	// f := test() //计数器 返回这个的函数会一直持有私有变量
	// f()
	// f()
	// f()

	// ------------------3.map遍历----------------------
	// PrintMap() // 运行这个就会发现他们的两次遍历输出的元素的顺序是完全不同的 是完全随机的
	// PrintMap()

	// ------------------4.channel---------------------
	// var ch chan int = make(chan int) //无容量的channel 会强制同步
	// go send(ch)
	// go receive(ch)
	// time.Sleep(2 * time.Second) // 阻塞主线程 保证子线程运行完毕
	// fmt.Println("main is end")

    // ------------------5.100 goroutinue---------------------
	// 一定要先创建这100个chan 不然就是nil chan 会出现一堆错误
	// for i,n := 1,100; i <= n; i++ {
	// 	map_thread[i] = make(chan int)
	// } 
	// //启动100个协程
	// for i,n := 1,100; i <= n; i++ {
	// 	go PrintNums(i)
	// } //启动100个协程
	// // 下面开始分配数字
	// for i,n := 1,1000; i <= n; i++ {
	// 	var id int = i % 100
	// 	if id == 0 {
	// 		id = 100
	// 	}
	// 	map_thread[id] <- i
	// 	<-is_ok
	// }
	// ------------------6.3 goroutinue---------------------
	map_thread['a'] = make(chan byte)
	map_thread['b'] = make(chan byte)
	map_thread['c'] = make(chan byte)
	go PrintChar('a')
	go PrintChar('b')
	go PrintChar('c')

	var str string = "abc"
	for i,n := 0,10; i < n; i++ {
		fmt.Printf("This is %d cout \n", i + 1)
		for j,m := 0,len(str); j < m; j++ {
			var c byte  = str[j]
			map_thread[c] <- c
			<- is_ok			
		}
		
	}
}

