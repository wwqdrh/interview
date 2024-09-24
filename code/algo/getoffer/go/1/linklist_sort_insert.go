package main

func insert(head *ListNode, insertVal int) *ListNode {
	node := &ListNode{Val: insertVal}
	if head == nil {
		node.Next = node
		return node
	}
	if head.Next == head {
		head.Next = node
		node.Next = head
		return head
	}
	curr, next := head, head.Next
	for next != head {
		if insertVal >= curr.Val && insertVal <= next.Val {
			break
		}
		if curr.Val > next.Val {
			if insertVal > curr.Val || insertVal < next.Val {
				break
			}
		}
		curr = curr.Next
		next = next.Next
	}
	curr.Next = node
	node.Next = next
	return head
}
