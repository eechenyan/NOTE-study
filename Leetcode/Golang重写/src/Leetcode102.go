// 层序遍历二叉树

// 头节点压入队列 之后开始循环 对于当前队列里面的出队然后获得数值 
// 然后对当前节点的左右子树进入队列 进行循环

package main
import "fmt"

type TreeNode struct {
	val int;
	left *TreeNode;
	right *TreeNode;
}

func traversal(root *TreeNode) []int {
	var result []int = make([]int, 0);
	var queue []*TreeNode = make([]*TreeNode, 0);
	// 1.头节点入队
	queue = append(queue, root);
	for len(queue) > 0 {
		var size int = len(queue);
		for i,n := 0, size; i < n; i++ {
			var node *TreeNode = queue[0];
			queue = queue[1:]; //出队
			result = append(result, node.val);
			// 入队
			if node.left != nil {
				queue = append(queue, node.left);
			}
			if node.right != nil {
				queue = append(queue, node.right);
			}
		}
	}
	return result;
}

func main() {
	// 手动拼接一棵树
	//      1
	//   2     3
	// 4   5 6   7
	var root TreeNode = TreeNode{val:1, left:nil, right:nil};
	var node1 TreeNode = TreeNode{val:2, left:nil, right:nil};
	var node2 TreeNode = TreeNode{val:3, left:nil, right:nil};
	root.left = &node1;
	root.right = &node2;
	var node3 TreeNode = TreeNode{val:4, left:nil, right:nil};
	var node4 TreeNode = TreeNode{val:5, left:nil, right:nil};
	var node5 TreeNode = TreeNode{val:6, left:nil, right:nil};
	var node6 TreeNode = TreeNode{val:7, left:nil, right:nil};
	node1.left = &node3;
	node1.right = &node4;
	node2.left = &node5;
	node2.right = &node6;
	fmt.Println(traversal(&root));
}