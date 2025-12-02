//  给定一个数组nums 和 一个整数 target 合理划分这个数组使得两部分的相减绝对值等于target 返回有多少个这个样子的组合
// 0 -1 背包问题

package main

import "fmt"

func findTargetSum(nums []int, target int) int {
    var sum int = 0
	var num_no_zero []int = make([]int, 0)
	var zero_cnt int = 0
	for _, value := range nums {
		if value != 0 {
			num_no_zero = append(num_no_zero, value)
		} else {
			zero_cnt++
		}
	}
    if zero_cnt == len(nums) {
        return (1 << zero_cnt)
    }
	for _, value := range num_no_zero {
		sum = sum  + value;
	}
    if target > sum {
        return 0
    } else if (target + sum) % 2 != 0 {
        return 0
    }
	var targetsum int = (target + sum) / 2 ;
    if targetsum < 0 {
        return 0
    }
	var dp [][]int = make([][]int, len(num_no_zero));
	for index, _ := range dp {
		dp[index] = make([]int, targetsum + 1);
	}
	// 转化为非0的情况 非0情况下
	// dp[i][0] 只能是0 因为没有任何办法可以刚好装满0容量的背包 有一种 那就是不装
    for i, n := 0, len(dp); i < n; i++ {
		dp[i][0] = 1; 
	}
	// dp[0][j] 在j==nums[0]的时候 就装它 等于1  
	for j, m := 0, len(dp[0]); j < m; j++ {
		if j == num_no_zero[0] {
			dp[0][j] = 1; 
		} 
	}
	for i, n := 1, len(num_no_zero); i < n; i++ {
		for j, m := 1, len(dp[0]); j < m; j++ {
			if j < num_no_zero[i] {
				dp[i][j] = dp[i - 1][j];
			} else {
				dp[i][j] = dp[i - 1][j] + dp[i - 1][j - num_no_zero[i]];
			}
		}
	}
	return dp[len(num_no_zero) - 1][targetsum] * (1 << zero_cnt); //最后是*而不是+
}
func main() {
	var nums []int = []int{1,1,1,1,1};
	var target int =  3;
	var result int = findTargetSum(nums,target);
	fmt.Println("result is :", result);
}