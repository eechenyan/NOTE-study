package main
import "fmt"

func findcoins(coins []int, amount int) int {
	var dp [][]int = make([][]int, len(coins));
	// dp[i][j] 表示0-i 下标 选取刚好装好j容量的背包
	// dp[0][j] 那就j和coins0的倍数有关
	// dp[i][0] 需要统计i返回内 0 的个数 然后方案有2的次方 就是一种方案
	for i,n := 0, len(dp); i < n; i++ {
		dp[i] = make([]int, amount + 1);
	}
	var zeronum int = 0;
	for i,n := 0, len(dp); i < n; i++ {
		if coins[i] == 0 {
			zeronum++;
			dp[i][0] = 1 << zeronum;
		}
	}
	for j,m := 1, len(dp[0]); j < m; j++ {
		if j < coins[0] {
			dp[0][j] = 0;
		} else if j % coins[0] != 0 {
			dp[0][j] = 0;
		} else {
			dp[0][j] = 1;
		}
	}
	for i,n := 1, len(dp); i < n; i++ {
		for j,m := 0, len(dp[0]); j < m; j++ {
			if j < coins[i] {
				dp[i][j] = dp[i - 1][j];
			} else {
				dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i]]; 
			}
		}
	}
	return dp[len(coins) - 1][amount];
}

func main() {
	var coins []int = []int{1, 2, 5};
	var amount int = 5;
	fmt.Println("result is", findcoins(coins,amount));
}