struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *merge(ListNode *head1, ListNode *head2) {
  ListNode dummyHead(0);
  ListNode *temp = &dummyHead;
  ListNode *temp1 = head1;
  ListNode *temp2 = head2;

  while (temp1 != nullptr && temp2 != nullptr) {
    if (temp1->val <= temp2->val) {
      temp->next = temp1;
      temp1 = temp1->next;
    } else {
      temp->next = temp2;
      temp2 = temp2->next;
    }
    temp = temp->next;
  }

  if (temp1 != nullptr) {
    temp->next = temp1;
  } else if (temp2 != nullptr) {
    temp->next = temp2;
  }

  return dummyHead.next;
}

ListNode *sort(ListNode *head, ListNode *tail) {
  if (head == nullptr) {
    return head;
  }

  if (head->next == tail) {
    head->next = nullptr;
    return head;
  }

  ListNode *slow = head;
  ListNode *fast = head;
  while (fast != tail) {
    slow = slow->next;
    fast = fast->next;
    if (fast != tail) {
      fast = fast->next;
    }
  }

  ListNode *mid = slow;
  return merge(sort(head, mid), sort(mid, tail));
}

ListNode *sortList(ListNode *head) { return sort(head, nullptr); }
