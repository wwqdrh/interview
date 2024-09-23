struct Node {
  int Val;
  Node *Prev;
  Node *Next;
  Node *Child;
  Node(int x) : Val(x), Prev(nullptr), Next(nullptr), Child(nullptr) {}
};

Node *dfs(Node *node) {
  Node *cur = node;
  Node *last = nullptr;

  while (cur != nullptr) {
    Node *next = cur->Next;
    if (cur->Child != nullptr) {
      Node *childLast = dfs(cur->Child);

      cur->Next = cur->Child;
      cur->Child->Prev = cur;

      if (next != nullptr) {
        childLast->Next = next;
        next->Prev = childLast;
      }

      cur->Child = nullptr;
      last = childLast;
    } else {
      last = cur;
    }
    cur = next;
  }
  return last;
}

Node *flatten(Node *root) {
  dfs(root);
  return root;
}
