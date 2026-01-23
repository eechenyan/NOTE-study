package main

import "fmt"

func IsNum(c byte) bool {
    if c <= '9' && c >= '0' {
        return true;
    } else {
        return false;
    }
}

func calculate(s string) int {
    // 维护result 和 当前阶段计算的num结果 
    // 而且需要记住的是 当前计算的结果需要乘上sign符号
    // （需要把上一层的结果压入栈 同时清零 ）需要把当前计算的结果加到result里面去；
    var result int = 0;
    var num int = 0;
    var stack []int = make([]int, 0); //用slice模拟栈
    var sign int = 1; // 1表示正数 -1表示负数

    for i,n := 0, len(s); i < n; i++ {
        var c byte = s[i];
        if IsNum(c) == true {
            num = num * 10 + int(c - '0');
        } else if c == '+' {
            result = result + sign * num;
            num = 0;
            sign = 1;
        } else if c == '-' {
            result = result + sign * num;
            num = 0;
            sign = -1;
        } else if c == '(' {
            // 保存上文的东西
            stack = append(stack, sign);
            stack = append(stack, result);
            result = 0;
            // 注意保存上文之后下一个的sign 默认是正数；
            sign = 1;
        } else if c == ')' {
            // 遇到）的时候该怎么做？？
            // 还是太tm难了
            // 首先遇到）的时候需要计算完当前的result
            // 之后需要把（之前的符号取出来 这个就是当前result的正负号
            // 之后取出上一个result加到一起来
            result = result + sign * num;
            num = 0;
            var last_result int = stack[len(stack) - 1];
            stack = stack[:len(stack) - 1];
            var cur_sign int = stack[len(stack) - 1];
            stack = stack[:len(stack) - 1];
            result = cur_sign * result;
            result = result + last_result;
        } else if c == ' '{
            continue;
        }
    }
    if num >= 0 {
        result = result + sign * num;
    }
    return result;
}

func main() {
	var s string = "(1+(4+5+2)-3)+(6+8)"
	fmt.Println("result is:", calculate(s))
}