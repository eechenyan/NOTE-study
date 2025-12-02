package main
import "fmt"

// 输入：grid = [
//   ['1','1','0','0','0'],
//   ['1','1','0','0','0'],
//   ['0','0','1','0','0'],
//   ['0','0','0','1','1']
// ]
// 输出：3
//  dfs 负责把一片岛屿全部插上旗帜2 然后 对这个岛屿进行遍历 每到一个dfs的时候就数量增1 之后就结束

var dir [][]int = [][]int{
	{0, 1}, 
	{0, -1}, 
	{1, 0}, 
	{-1, 0},
}

func dfs(graph [][]int, x int, y int, visited [][]int) {
	if visited[x][y] == 1 || graph[x][y] == 2 {
		return
	}
	visited[x][y] = 1
	for i,n := 0, len(dir); i < n; i++ {
		var next_x int = x + dir[i][0];
		var next_y int = y + dir[i][1];
		if next_x >=0 && next_x <len(graph) && next_y >=0 && next_y < len(graph[0]) && visited[next_x][next_y] == 0 && graph[next_x][next_y] == 1  {
			dfs(graph, next_x, next_y, visited)
		}
	}
}

func main() {
	var graph [][]int = [][]int {
	{1,1,1,1,0},
	{1,1,0,1,0},
	{1,1,0,0,0},
	{0,0,0,0,0},
	}
	var visited [][]int = make([][]int, len(graph))
	var result int = 0;
	for i,n := 0, len(visited); i < n; i++ {
		visited[i] = make([]int, len(graph[0])) //默认不赋值就是0
	}
	for i,n := 0, len(graph); i < n; i++ {
		for j,m := 0, len(graph[0]); j < m; j++ {
			if visited[i][j] == 0 && graph[i][j] ==1 {
				dfs(graph,i,j,visited)
				result++;
			}
		}
	}
	fmt.Println("result is:",result);
	fmt.Println("graph is:",graph);
}