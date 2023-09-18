tree_t *createNode(int value)
{
  tree_t *node = (tree_t *)malloc(sizeof(node_t));
  node->data = value;
  node->left = node->right = NULL;
  return node;
}

tree_t *searchNode(tree_t *t, int val)
{
  if (t == NULL || t->data == val)
  {
    return t;
  }
  tree_t *pos = searchNode(t->left, val);
  if (pos != NULL)
  {
    return pos;
  }
  else
  {
    return searchNode(t->right, val);
  }
}

tree_t *attach(tree_t *t, int parent, int child, int branch)
{
  node_t *newNode = createNode(child);
  // this is a value for root node
  if (parent == -1)
  {
    return newNode;
  }
  node_t *parentNode = searchNode(t, parent) if (branch == 1)
  {
    parentNode->left = newNode;
  }
  else
  {
    parentNode->right = newNode;
  }
  return t;
}
