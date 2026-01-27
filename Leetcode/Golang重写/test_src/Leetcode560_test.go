package main

import "testing"

// 练习编写测试用例 以后工作要用到的

// go test -v 运行测试用例

// go test -coverprofile=coverage.out && go tool cover -html=coverage.out 运行测试用例并且输出覆盖率生成html文件


func TestFindCount(t *testing.T) {
	type testcase struct {
		name string //测试用例名称
		nums []int //输入数组
		k int //目标和
		expected int //期望返回值
	}
	var testcases []testcase = []testcase{
		{
			name : "常规场景：连续两个1-和为2",
			nums : []int{1,1,1},
			k : 2,
			expected :  2, // 子数组[0,1]、[1,2]，共2个
		},
		{
			name:     "空数组",
			nums:     []int{},
			k:        0,
			expected: 0, // 空数组无任何子数组
		},
		{
			name:     "k为0-子数组和为0",
			nums:     []int{1, -1, 2, -2},
			k:        0,
			expected: 3, // [0,1]、[2,3]、[0,3]，共3个
		},
		{
			name:     "无符合条件的子数组",
			nums:     []int{2, 3, 4},
			k:        1,
			expected: 0,
		},
		{
			name:     "单个元素匹配k",
			nums:     []int{5},
			k:        5,
			expected: 1, // 子数组[0]，共1个
		},
		{
			name:     "包含负数的常规场景",
			nums:     []int{1, -1, 0},
			k:        0,
			expected: 3, // [0,1]、[2]、[0,2]，共3个
		},
	}

	for _, tc := range testcases {
		t.Run(tc.name, func(t *testing.T) {
			// t.Run(测试用例名字， 测试函数经常写为匿名函数)
			result := FindCount(tc.nums, tc.k)
			if result != tc.expected {
				t.Errorf("用例[%s]失败：预期%d，实际%d", tc.name, tc.expected, result)
			}
		}) 
	}
}
