package main

import "fmt"

// 修复：实现 int 类型的 max 函数
func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func FindLastestStr(s string) int {
	var left int = 0;
	var right int = 0;
	var max_len int = 0;
	var umap map[byte]int = make(map[byte]int, 0);
	for left <= right && left < len(s) && right < len(s) {
		for umap[s[right]] > 0 {
			delete(umap, s[left]);
			left++;
		}
		umap[s[right]]++
		max_len = max(max_len, right - left + 1);
		right++;
	}
	return max_len;
}

func main() {
	var s string = "abcabcbbabcdefg";
	fmt.Println("Lastest length is:", FindLastestStr(s));
}