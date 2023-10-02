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

typedef struct stack
{
  int value, height;
  struct stack *next, *prev;
} stack_t;

stack_t *stackPush(stack_t *s, int val)
{
  stack_t *newNode = (stack_t *)malloc(sizeof(stack_t));
  newNode->value = val;
  newNode->next = newNode->prev = NULL;
  if (s == NULL)
  {
    newNode->height = 1;
    return newNode;
  }
  s->prev = newNode;
  newNode->next = s;
  newNode->height = s->height + 1;
  return newNode;
}

void print_preorder(tree_t *t)
{
  // print out dfs in sequence
  // base case
  if (t == NULL)
  {
    return;
  }
  printf("%d ", t->data);
  print_preorder(t->left);
  print_preorder(t->right);
}

stack_t *stackPostOrder(tree_t *t, stack_t *s)
{ // create a stack and storage all the values
  if (t == NULL)
  {
    return s;
  }
  s = stackPush(s, t->data);
  s = stackPostOrder(t->right, s);
  s = stackPostOrder(t->left, s);
  return s;
}
void print_postorder(tree_t *t)
{
  stack_t *s = NULL;
  printf("\n");
  s = stackPostOrder(t, s);
  while (s != NULL)
  {
    printf("%d ", s->value);
    stack_t *tmp = s;
    s = s->next;
    free(tmp);
  }
}

stack_t *stackInOrder(tree_t *t, stack_t *s)
{ // create a stack and storage all the values
  if (t == NULL)
  {
    return s;
  }
  s = stackInOrder(t->right, s);
  s = stackPush(s, t->data);
  s = stackInOrder(t->left, s);
  return s;
}
void print_inorder(tree_t *t)
{
  // create a stack and storage all the values
  stack_t *s = NULL;
  printf("\n");
  s = stackInOrder(t, s);
  while (s != NULL)
  {
    printf("%d ", s->value);
    stack_t *tmp = s;
    s = s->next;
    free(tmp);
  }
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
  print_preorder(t);
  print_postorder(t);
  print_inorder(t);
  return 0;
}