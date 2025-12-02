// ------------------此文件用来验证各种想要验证的想法---------------------
package main
import "fmt"

// 1.defer
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

// 2.闭包
// func test() func() int {
// 	var count int = 0 // 被捕获的状态变量（私有，外部无法直接修改）
// 	f:= func() int { // 闭包 用于捕获私有变量并返回
// 		count++
// 		fmt.Println("count is %d", count)
// 		return count
// 	} 
// 	return f // 返回一个函数声明加实现
// }

func main() {
	// ------------------1.defer---------------------
	// fmt.Println("This is main", test()) 

	// ------------------2.闭包----------------------
	// f := test() //计数器 返回这个的函数会一直持有私有变量
	// f()
	// f()
	// f()
}