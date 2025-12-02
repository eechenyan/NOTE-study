// 416. 分割等和子集
// 相关企业
// 给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等

// 背包问题 dp 一个背包是否可以装满sum/2的容量 如果能装满 那么就是可以的 背包的最大容量就是nums.size 看最后的重量是否是sum / 2

// dp[i][j]表示0 - i 下标的物品里面 容量为j的可以装满的最大重量

// dp[i][j] = max(dp[i - 1][j], dp[i][j - nums[i]] + nums[i]) j > nums[i]
package main
import "fmt"
func FindBucket(nums []int) bool {
	var sum int = 0
	for _, value := range nums {
		sum = sum + value
	}
	if sum % 2 != 0 {
		return false
	}
	var target int = sum / 2
	var dp [][]int  = make([][]int, len(nums))
	for i, n := 0, len(nums); i < n; i++ {
		dp[i] = make([]int, target + 1)
	}
	// dp[0][j] 在j》=nums【0】的时候就是 nums【0】
	// dp【i】【0】就是0 不用再初始化了
	for j, m := 0, len(dp[0]); j < m; j++ {
		if j < nums[0] {
			continue
		} else {
			dp[0][j] = nums[0]
		}
	}
	for i, n := 1, len(nums); i < n; i++ {
		for j, m := 0, len(dp[0]); j < m; j++ {
			if j < nums[i] {
				dp[i][j] = dp[i - 1][j]
			} else {
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - nums[i]] + nums[i])
			}
		}
	}
	var ret int = dp[len(nums) - 1][target]
	fmt.Println(dp)
	if ret == target {
		return true
	} else {
		return false
	}
}

func main() {
	var nums []int = []int{1,2,3,5}
	fmt.Println("result is :%t",FindBucket(nums))
}