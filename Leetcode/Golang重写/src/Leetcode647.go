// 647. 回文子串
// 已解答
// 中等
// 相关标签
// premium lock icon
// 相关企业
// 提示
// 给你一个字符串 s ，请你统计并返回这个字符串中 回文子串 的数目。

// 回文字符串 是正着读和倒过来读一样的字符串。

// 子字符串 是字符串中的由连续字符组成的一个序列。

// 回溯获得所有连续字串并且符合回文串的path 然后统计result数目

package main

import "fmt"

var path string
var result []string  
func IsVaild(s string) bool {
    var left int = 0
    var right int = len(s) - 1
    for left <= right {
        if s[left] != s[right] {
            return false
        } 
        left++
        right--
    }
    return true;
}

func backtracking(s string, start_index int) {
    if start_index > len(s) {
        return 
    }
    if IsVaild(path) == true {
	result = append(result, path);
    }
    for i,n := start_index, len(s); i < n; i++ {
        path = path + string(s[i])
        backtracking(s, i + 1)
        path = path[:len(path) - 1]
		if start_index != 0 {
            break;
        } // 不懂
    }
}

func countSubstrings(s string) int {
    backtracking(s, 0)
    return len(result) - 1
}

func main() {
	var s string = "aaa"
	fmt.Println("result length is:", countSubstrings(s))
	fmt.Println("result is:", result)
}