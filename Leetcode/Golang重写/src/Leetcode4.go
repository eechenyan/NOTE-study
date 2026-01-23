// 4. 寻找两个正序数组的中位数

// 相关企业
// 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。

package main
import "fmt"

func FindMiddleNum(nums1 []int, nums2 []int) float64 {
	// 思路就是找中间那个数字 就是排序两个有序链表的思路
	// 两个指针比较 更新指针,谁小谁移动, 一共移动的步数就是要找的那个数字的下标
	var index1 int = 0
	var index2 int = 0
	var length int = len(nums1) + len(nums2)
	// 如果是奇数 那么length / 2 就刚好是哪个下标 如果是偶数 length / 2 就是后一个数字
	var k1 int = length / 2
	var pre float64 = 0;
	var cur float64 = 0;
	for k1 >= 0 {
		pre = cur
		if index1 < len(nums1) && index2 < len(nums2) && nums1[index1] <= nums2[index2] {
			cur = float64(nums1[index1]) //记录当前的数值-插入新链表
			index1++;
		} else {
			cur = float64(nums2[index2]) //记录当前的数值
			index2++;
		}
		k1--
	}
	if length % 2 != 0 {
		return cur
	} else {
		return (cur + pre) / 2
	}
}

func main() {
	var nums1 []int = []int{1,3}
	var nums2 []int = []int{2,4}
	var result float64 = FindMiddleNum(nums1, nums2)
	fmt.Printf("middle number is%f",result)
}