// 给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。

// 一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。

// 例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
// 两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。

// 思路是动态规划 dp[i][j]表示长度为i的子字符串和j的子字符串的最大的 公共子序列长度 如果s[i] == s[j] dp+1 
// 否则 dp[i][j] 等于他们之间最大的 还有当前长度的最大值

package main

import "fmt"

func max(a int, b int) int {
	if a > b {
		return a 
	} else {
		return b
	}
}

func FindLongestStr(text1 string, text2 string) int {
	var dp [][]int = make([][]int, len(text1) + 1);
	for i,n := 0, len(dp); i < n; i++ {
		dp[i] = make([]int, len(text2) + 1)
	}

	// 初始化dp[0][j] = 0
	// dp[i][0] = 0;
	for i,n :=1, len(dp); i < n; i++ {
		for j,m := 1, len(dp[0]); j < m; j++ {
			if text1[i - 1] == text2[j - 1] {
				dp[i][j] = dp[i - 1][j - 1] + 1
			} else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
			}
		}
	}
	return dp[len(text1)][len(text2)]
}

func main() {
	var text1 string = "abc"
	var text2 string = "def"
	fmt.Println("result is: ",FindLongestStr(text1,text2))
}