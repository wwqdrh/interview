struct Node {
  int Val;
  Node *Next;
  Node(int x) : Val(x), Next(nullptr) {}
};

Node *insert(Node *head, int insertVal) {
  Node *node = new Node(insertVal);
  if (head == nullptr) {
    node->Next = node;
    return node;
  }
  if (head->Next == head) {
    head->Next = node;
    node->Next = head;
    return head;
  }
  Node *curr = head;
  Node *next = head->Next;
  while (next != head) {
    if (insertVal >= curr->Val && insertVal <= next->Val) {
      break;
    }
    if (curr->Val > next->Val) {
      if (insertVal > curr->Val || insertVal < next->Val) {
        break;
      }
    }
    curr = curr->Next;
    next = next->Next;
  }
  curr->Next = node;
  node->Next = next;
  return head;
}
