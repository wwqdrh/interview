package main

// 合并K个升序链表
func mergeKLists(lists []*ListNode) (res *ListNode) {
	for _, v := range lists {
		res = mergeTwoLists(res, v)
	}
	return res
}

// 合并两个升序链表
func mergeTwoLists(list1 *ListNode, list2 *ListNode) *ListNode {
	//初始化一个虚拟的头节点
	newList := &ListNode{}
	p := newList
	p1 := list1
	p2 := list2
	//遍历对比两个指针值的大小，有一个走完了就停止
	for p1 != nil && p2 != nil {
		//将值小的节点接到p指针后面
		if p1.Val > p2.Val {
			p.Next = p2
			p2 = p2.Next
		} else {
			p.Next = p1
			p1 = p1.Next
		}
		//p指针前进
		p = p.Next
	}
	//将未比较的剩余节点都放到p指针后面
	if p1 != nil {
		p.Next = p1
	}
	if p2 != nil {
		p.Next = p2
	}
	//返回虚拟头节点的下一个节点就是真正的头节点
	return newList.Next
}
