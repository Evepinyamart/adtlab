#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
  int data;
  struct node *left;
  struct node *right;
} node_t;
typedef node_t bst_t;

node_t *createNode(int val)
{
  node_t *node = (node_t *)malloc(sizeof(node_t));
  node->left = node->right = NULL;
  node->data = val;
  return node;
}

node_t *findNode(bst_t *t, int val)
{
  if (t == NULL)
  {
    return NULL;
  }
  if (t->data == val)
  {
    return t;
  }
  if (val < t->data)
  {
    return findNode(t->left, val);
  }
  return findNode(t->right, val);
}

int find(bst_t *t, int val) { return (findNode(t, val) == NULL) ? 0 : 1; }

bst_t *insert(bst_t *t, int val)
{
  if (t == NULL)
  {
    bst_t *newNode = createNode(val);
    return newNode;
  }
  if (t->data > val)
  {
    bst_t *newNode = insert(t->left, val);
    t->left = newNode;
  }
  else
  {
    bst_t *newNode = insert(t->right, val);
    t->right = newNode;
  }
  return t;
}

int find_min(bst_t *t)
{
  if (t == NULL)
  {
    return -1;
  }
  if (t->left == NULL)
  {
    return t->data;
  }
  find_min(t->left);
}

int find_max(bst_t *t)
{
  if (t == NULL)
  {
    return -1;
  }
  if (t->right == NULL)
  {
    return t->data;
  }
  find_max(t->right);
}

void freeBST(bst_t *t)
{
  if (t == NULL)
    return;

  freeBST(t->left);
  freeBST(t->right);
  free(t);
}

bst_t *delete(bst_t *t, int val)
{
  if (t == NULL)
  {
    return t; // Node not found
  }

  if (val < t->data)
  {
    // วิ่งไปก็ assign ใหม่ไปด้วย พอเจอตัวที่ต้องการก็ไม่ต้องหา parent
    t->left = delete (t->left, val);
  }
  else if (val > t->data)
  {
    t->right = delete (t->right, val);
  }
  else
  { // Node with val found
    if (t->left == NULL)
    {
      bst_t *temp = t->right;
      free(t);
      return temp;
    }
    else if (t->right == NULL)
    {
      bst_t *temp = t->left;
      free(t);
      return temp;
    }

    // Node that we want to delete has two children
    node_t *minNode = t->right;
    while (minNode->left != NULL)
    {
      minNode = minNode->left;
    }

    // use minNode to replace the node that we want to delete
    t->data = minNode->data;
    t->right = delete (t->right, minNode->data);
  }
  return t;
}

int main(void)
{
  bst_t *t = NULL;
  int n, i;
  int command, data;
  scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    scanf("%d", &command);
    switch (command)
    {
    case 1:
      scanf("%d", &data);
      t = insert(t, data);
      break;
    case 2:
      scanf("%d", &data);
      t = delete (t, data);
      break;
    case 3:
      scanf("%d", &data);
      printf("%d\n", find(t, data));
      break;
    case 4:
      printf("%d\n", find_min(t));
      break;
    case 5:
      printf("%d\n", find_max(t));
      break;
    }
  }
  freeBST(t);
  return 0;
}