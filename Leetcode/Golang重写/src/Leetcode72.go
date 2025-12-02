package main

import "fmt"

// 二维长度dp dp[i][j]表示长度i和j的word1和word2所需的最少操作数
// 如果word-i-1 和 word2-j-1 相等 那么不需要操作哦
// 如果不相等 那么就是取最小 有增删替换三种操作 取最小就行了

func LeastNum(word1 string, word2 string) int {
	var dp [][]int = make([][]int, len(word1));
	for index, _ := range dp {
		dp[index] = make([]int, len(word2)); //注意二维的初始化哦
	}
	// dp[0][j] 就是j咯
	// dp[i][0] 就是i咯
	for i,row := 0, len(dp); i < row; i++ {
		dp[i][0] = i;
	}
	for j,col := 0, len(dp[0]); j < col; j++ {
		dp[0][j] = j;
	}
	for i,row := 1, len(dp); i < row; i++ {
		for j,col := 1, len(dp[0]); j < col; j++ {
			if word1[i - 1] == word2[j - 1] {
				dp[i][j] = dp[i - 1][j - 1];
			} else {
				dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1);
			}
		}
	}
	return dp[len(word1) - 1][len(word2) - 1];
}

func main() {
	var word1 string = "intention";
	var word2 string = "execution";
	fmt.Println("least nums is:", LeastNum(word1,word2));
}