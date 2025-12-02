package main

import "fmt"

func IsVail(s string) bool {
	// 判断一个字符串是否合法的括号
	var stack []byte = make([]byte, 0);
	for _, value := range s {
		if value != '(' && value != ')' {
			continue;
		}
		if value == '(' { //左括号
			stack = append(stack, byte(value));
		} else {
			// 右括号
			if len(stack) == 0 {
				return false; //空栈直接错误
			} else {
				stack = stack[: len(stack) - 1];
			}
		}
	}
	if len(stack) == 0 {
		return true;
	} else {
		return false;
	}
}

func LastLen(s string) int {
	// 获取最后的长度
	var left_extra int = 0;
	var right_extra int = 0;
	var balance int = 0;
	var last_len int = 0;
	for i,n := 0, len(s); i < n; i++ {
		if s[i] == '(' {
			balance++;
		} else {
			if balance > 0 {
				balance--;
			} else {
				right_extra++;
			}
		}
	}
	left_extra = balance;
	last_len = len(s) - left_extra - right_extra;
	return last_len;
}

var path string = "";
// var result []string = make([]string, 0);
var result map[string]int = make(map[string]int, 0); //需要去重

func backtracking(s string, start_index int, last_len int) {
	if len(path) == last_len && IsVail(path) == true {
		// result = append(result, path);
		result[path] = 0;
		return ;
	}
	if len(path) > last_len {
		return ;
	}
	// 剪枝
	for i,n := start_index, len(s); i < n; i++ {
		if i > start_index && s[i] == s[i - 1] && s[i] == '('  {
			continue;
		}
		if i > start_index && s[i] == s[i - 1] &&  s[i] == ')' {
			continue;
		}
		path = path + string(s[i]);
		backtracking(s, i + 1, last_len);
		path = path[: len(path) - 1];
	}
}

func main() {
	var s string = "(aa)()"; 
	var last_len int = LastLen(s);

	
	backtracking(s,0,last_len);
	for key, _ := range result {
		fmt.Println("result is:",key);
	}
}