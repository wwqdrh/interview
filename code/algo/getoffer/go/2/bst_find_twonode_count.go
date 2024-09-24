package main

func findTarget(root *TreeNode, k int) bool {
	visit := map[int]struct{}{}
	flag := false
	var inorder func(*TreeNode)
	inorder = func(node *TreeNode) {
		if node == nil || flag {
			return
		}
		inorder(node.Left)
		if _, ok := visit[k-node.Val]; ok {
			flag = true
			return
		}
		visit[node.Val] = struct{}{}
		inorder(node.Right)
	}
	inorder(root)
	return flag
}
