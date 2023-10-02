#include <stdio.h>
#include <stdlib.h>
#include <week8.h>
#ifndef __bin_tree__
typedef struct node
{
  int data;
  struct node *left;
  struct node *right;
} node_t;
typedef node_t tree_t;
#endif

int is_full(tree_t *t)
{
  // leaf node
  if (t->left == NULL && t->right == NULL)
  {
    return 1;
  }
  // there's only one child node
  if (t->left == NULL || t->right == NULL)
  {
    return 0;
  }
  return is_full(t->left) && is_full(t->right);
}

int max(int a, int b)
{
  if (a >= b)
  {
    return a;
  }
  return b;
}

int treeHeight(tree_t *t)
{
  if (t == NULL)
  {
    return 0;
  }
  return max(treeHeight(t->left), treeHeight(t->right)) + 1;
}

int is_perfect(tree_t *t)
{
  if (t == NULL)
  {
    return 1;
  }
  return (treeHeight(t->left) == treeHeight(t->right)) && is_perfect(t->left) && is_perfect(t->right);
}

int countNode(tree_t *t)
{
  if (t == NULL)
  {
    return 0;
  }
  return 1 + countNode(t->left) + countNode(t->right);
}

int complete(tree_t *t, int i, int node)
{
  if (t == NULL)
    return 1;
  if (i >= node)
    return 0;
  return complete(t->left, 2 * i + 1, node) && complete(t->right, 2 * i + 2, node);
}
int is_complete(tree_t *t)
{
  int nodeNum = countNode(t);
  return complete(t, 0, nodeNum);
}

int is_degenerate(tree_t *t)
{
  if (t == NULL)
  {
    return 1;
  }
  // have two child
  if (t->left != NULL && t->right != NULL)
  {
    return 0;
  }
  return is_degenerate(t->left) && is_degenerate(t->right);
}

int is_onlyleft(tree_t *t)
{
  if (t == NULL)
  {
    return 1;
  }
  if (t->right != NULL)
  {
    return 0;
  }
  return is_onlyleft(t->left);
}
int is_onlyright(tree_t *t)
{
  if (t == NULL)
  {
    return 1;
  }
  if (t->left != NULL)
  {
    return 0;
  }
  return is_onlyright(t->right);
}

int is_skewed(tree_t *t)
{
  return is_onlyleft(t) ^ is_onlyright(t);
}

int main(void)
{
  tree_t *t = NULL;
  int n, i;
  int parent, child;
  int branch; // 0 root, 1 left, 2 right
  scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    scanf("%d %d %d", &parent, &child,
          &branch);
    t = attach(t, parent, child, branch);
  }
  printf("%d %d %d %d %d\n", is_full(t),
         is_perfect(t), is_complete(t), is_degenerate(t), is_skewed(t));
  return 0;
}