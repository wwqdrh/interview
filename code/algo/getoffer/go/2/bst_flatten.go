package main

func increasingBST(root *TreeNode) *TreeNode {
	dummyNode := &TreeNode{}
	resNode := dummyNode

	var inorder func(*TreeNode)
	inorder = func(node *TreeNode) {
		if node == nil {
			return
		}
		inorder(node.Left)

		// 在中序遍历的过程中修改节点指向
		resNode.Right = node
		node.Left = nil
		resNode = node

		inorder(node.Right)
	}
	inorder(root)

	return dummyNode.Right
}
