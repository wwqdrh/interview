package main

func addTwoNumbers(l1 *ListNode, l2 *ListNode) (head *ListNode) {
	var s1, s2 []int
	for l1 != nil {
		s1 = append(s1, l1.Val)
		l1 = l1.Next
	}
	for l2 != nil {
		s2 = append(s2, l2.Val)
		l2 = l2.Next
	}
	carry := 0
	for len(s1) > 0 || len(s2) > 0 || carry > 0 {
		sum := 0
		if len(s1) > 0 {
			sum += s1[len(s1)-1]
			s1 = s1[:len(s1)-1]
		}
		if len(s2) > 0 {
			sum += s2[len(s2)-1]
			s2 = s2[:len(s2)-1]
		}
		sum += carry
		node := &ListNode{Val: sum % 10}
		node.Next = head
		head = node
		carry = sum / 10
	}
	return
}
