#include <stdio.h>
#include <stdlib.h>
#include "week9.h"
#ifndef __avl_tree__
typedef struct node
{
  int data;
  int height;
  struct node *left;
  struct node *right;
} node_t;
typedef node_t avl_t;
#endif

int height(node_t *node)
{
  if (node == NULL)
  {
    return -1;
  }
  return node->height;
}

node_t *createNode(int val)
{
  node_t *node = (node_t *)malloc(sizeof(node_t));
  node->left = node->right = NULL;
  node->height = 0;
  node->data = val;
  return node;
}

int find_min(avl_t *t)
{
  if (t == NULL)
  {
    return 0;
  }
  if (t->left == NULL)
  {
    return t->data;
  }
  find_min(t->left);
}

int max(int a, int b)
{
  return (a > b) ? a : b;
}

int checkBalance(node_t *node)
{
  if (node == NULL)
  {
    return 0;
  }
  return height(node->left) - height(node->right);
}

node_t *rightRotation(node_t *a)
{
  node_t *b = a->left;
  node_t *c = b->right;

  // perform right rotatation
  b->right = a;
  a->left = c;
  // update height
  a->height = max(height(a->left), height(a->right)) + 1;
  b->height = max(height(b->left), height(b->right)) + 1;
  return b;
}

node_t *leftRotation(node_t *a)
{
  node_t *b = a->right;
  node_t *c = b->left;

  // perform left rotatation
  b->left = a;
  a->right = c;
  // update height
  a->height = max(height(a->left), height(a->right)) + 1;
  b->height = max(height(b->left), height(b->right)) + 1;
  return b;
}

node_t *treeBalance(avl_t *t, int data)
{
  int balance = checkBalance(t);
  // Right rotation
  if (balance > 1 && checkBalance(t->left) >= 0)
  {
    return rightRotation(t);
  }
  // Left rotation
  if (balance < -1 && (checkBalance(t->right) <= 0))
  {
    return leftRotation(t);
  }
  // Left-Right rotation
  if (balance > 1 && (checkBalance(t->left) < 0))
  {
    t->left = leftRotation(t->left);
    return rightRotation(t);
  }
  // Right-Left rotation
  if (balance < -1 && (checkBalance(t->right) > 0))
  {
    t->right = rightRotation(t->right);
    return leftRotation(t);
  }
  // No rotation needed, return the original node
  return t;
}

avl_t *insert(avl_t *t, int data)
{
  if (t == NULL)
  {
    return createNode(data);
  }
  if (t->data > data)
  {
    t->left = insert(t->left, data);
  }
  else
  {
    t->right = insert(t->right, data);
  }
  // Update height of the current node
  t->height = 1 + max(height(t->left), height(t->right));
  // check if the current node is balance if not then balance()

  return treeBalance(t, data);
}

node_t *findMin(node_t *root)
{
  if (root == NULL)
  {
    return NULL;
  }
  while (root->left != NULL)
  {
    root = root->left;
  }
  return root;
}

avl_t *delete(avl_t *t, int val)
{
  if (t == NULL)
  {
    return t; // Node not found
  }

  if (val < t->data)
  {
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
      avl_t *temp = t->right;
      free(t);
      return temp;
    }
    else if (t->right == NULL)
    {
      avl_t *temp = t->left;
      free(t);
      return temp;
    }
    else
    {
      // Node that we want to delete has two children
      node_t *minNode = findMin(t->right);
      t->data = minNode->data;
      t->right = delete (t->right, minNode->data);
    }
  }
  // Update height of the current node
  t->height = 1 + max(height(t->left), height(t->right));
  // check if the current node is balance if not then balance()
  return treeBalance(t, val);
}

int main(void)
{
  avl_t *t = NULL;
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
      print_tree(t);
      break;
    }
  }
  return 0;
}