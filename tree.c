#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int value, depth;
  struct node *firstChild, *lastChild, *nextSibling, *parent, *prevSibling;
} node_t;
typedef node_t tree_t;

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

typedef struct queue
{
  int value;
  struct queue *next;
} queue_t;

queue_t *enqueue(queue_t *q, int val)
{
  queue_t *newNode = (queue_t *)malloc(sizeof(queue_t));
  newNode->value = val;
  newNode->next = NULL;

  if (q == NULL)
  {
    return newNode;
  }

  queue_t *temp = q;
  while (temp->next != NULL)
  {
    temp = temp->next;
  }
  temp->next = newNode;

  return q;
}

int dequeue(queue_t **q)
{
  if (*q == NULL)
  {
    return -1; // Queue is empty
  }

  int val = (*q)->value;
  queue_t *temp = *q;
  *q = (*q)->next;
  free(temp);

  return val;
}

tree_t *createNode(int value)
{
  tree_t *node = (tree_t *)malloc(sizeof(node_t));
  node->value = value;
  node->firstChild = node->lastChild = node->nextSibling = node->prevSibling = node->parent = NULL;
  return node;
}

tree_t *searchNode(tree_t *t, int val)
{
  if (t == NULL || t->value == val)
  {
    return t;
  }
  tree_t *pos = searchNode(t->firstChild, val);
  if (pos != NULL)
  {
    return pos;
  }
  else
  {
    return searchNode(t->nextSibling, val);
  }
}

tree_t *attach(tree_t *t, int parentVal, int childVal)
{
  tree_t *newNode = createNode(childVal);
  // base case
  if (t == NULL)
  {
    newNode->depth = 0;
    return newNode;
  }

  tree_t *parentPos = searchNode(t, parentVal);
  newNode->depth = parentPos->depth + 1;
  newNode->parent = parentPos;
  if (parentPos->firstChild == NULL)
  {
    parentPos->firstChild = newNode;
    parentPos->lastChild = newNode;
  }
  else
  {
    parentPos->lastChild->nextSibling = newNode;
    newNode->prevSibling = parentPos->lastChild;
    parentPos->lastChild = newNode;
  }
  return t;
}

tree_t *detach(tree_t *t, int val)
{
  // base
  if (t->value == val)
  {
    if (t->prevSibling != NULL)
    {
      t->prevSibling->nextSibling = t->nextSibling;
    }
    else
    {
      t->parent->firstChild = t->nextSibling;
    }

    if (t->nextSibling != NULL)
    {
      t->nextSibling->prevSibling = t->prevSibling;
    }
    else
    {
      t->parent->lastChild = t->prevSibling;
    }
    return t;
  }
  // recursive
  if (t->nextSibling != NULL)
  {
    detach(t->nextSibling, val);
  }
  if (t->firstChild != NULL)
  {
    detach(t->firstChild, val);
  }
  return t;
}

int search(tree_t *t, int val)
{
  return searchNode(t, val) == NULL ? 0 : 1;
}
int degree(tree_t *t, int val)
{
  tree_t *node = searchNode(t, val);
  if (node == NULL)
  {
    return -1;
  }

  int childNum = 0;
  tree_t *child = node->firstChild;
  while (child != NULL)
  {
    child = child->nextSibling;
    childNum++;
  }
  return childNum;
}

int is_root(tree_t *t, int n)
{
  return t->value == n;
}

int is_leaf(tree_t *t, int val)
{
  tree_t *pos = searchNode(t, val);
  return pos->firstChild == NULL ? 1 : 0;
}

void siblings(tree_t *t, int val)
{
  tree_t *pos = searchNode(t, val);
  if (pos == NULL || pos->parent == NULL)
  {
    printf("\n");
  }
  else
  {
    tree_t *sibling = pos->parent->firstChild;
    while (sibling != NULL)
    {
      if (sibling->value != val)
      {
        printf("%d ", sibling->value);
      }
      sibling = sibling->nextSibling;
    }
    printf("\n");
  }
}

int depth(tree_t *t, int val)
{
  tree_t *pos = searchNode(t, val);
  if (pos == NULL)
  {
    return -1;
  }
  return pos->depth;
}

stack_t *explore(tree_t *t, int startVal, int stopVal)
{
  node_t *startNode = searchNode(t, startVal);
  node_t *stopNode = searchNode(t, stopVal);
  stack_t *res = (stack_t *)malloc(sizeof(stack_t));
  while (stopNode->value != startNode->value)
  {
    res = stackPush(res, stopNode->value);
    stopNode = searchNode(startNode, stopNode->parent->value);
  }
  res = stackPush(res, stopNode->value);
  return res;
}

void print_path(tree_t *t, int startVal, int stopVal)
{
  stack_t *topStack = explore(t, startVal, stopVal);
  while (topStack->next != NULL)
  {
    printf("%d ", topStack->value);
    topStack = topStack->next;
  }
  printf("\n");
}

int path_length(tree_t *t, int startVal, int stopVal)
{
  stack_t *topStack = explore(t, startVal, stopVal);
  return topStack->height;
}

void ancestor(tree_t *t, int stopVal)
{
  print_path(t, t->value, stopVal);
}

void dfs(tree_t *t)
{
  // print out dfs in sequence
  // base case
  if (t == NULL)
  {
    return;
  }
  printf("%d ", t->value);
  dfs(t->firstChild);
  dfs(t->nextSibling);
}

void bfs(tree_t *t)
{
  if (t == NULL)
  {
    return;
  }

  queue_t *queue = NULL;
  queue = enqueue(queue, t->value);

  while (queue != NULL)
  {
    int val = dequeue(&queue);
    printf("%d ", val);

    tree_t *node = searchNode(t, val);
    tree_t *child = node->firstChild;
    while (child != NULL)
    {
      queue = enqueue(queue, child->value);
      child = child->nextSibling;
    }
  }
}

void descendant(tree_t *t, int val)
{
  tree_t *node = searchNode(t, val);
  bfs(node);
}

void print_tree(tree_t *t)
{
  if (t == NULL)
  {
    return;
  }
  for (int i = 0; i < t->depth; i++)
  {
    printf("    ");
  }
  printf("%d\n", t->value);
  print_tree(t->firstChild);
  print_tree(t->nextSibling);
}



int main(void)
{
  tree_t *t = NULL;
  int n, i, command;
  int parent, child, node, start, end;
  scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    scanf("%d", &command);
    switch (command)
    {
    case 1:
      scanf("%d %d", &parent, &child);
      t = attach(t, parent, child);
      break;
    case 2:
      scanf("%d", &node);
      t = detach(t, node);
      break;
    case 3:
      scanf("%d", &node);
      printf("%d\n", search(t, node));
      break;
    case 4:
      scanf("%d", &node);
      printf("%d\n", degree(t, node));
      break;
    case 5:
      scanf("%d", &node);
      printf("%d\n", is_root(t, node));
      break;
    case 6:
      scanf("%d", &node);
      printf("%d\n", is_leaf(t, node));
      break;
    case 7:
      scanf("%d", &node);
      siblings(t, node);
      break;
    case 8:
      scanf("%d", &node);
      printf("%d\n", depth(t, node));
      break;
    case 9:
      scanf("%d %d", &start, &end);
      print_path(t, start, end);
      break;
    case 10:
      scanf("%d %d", &start, &end);
      printf("%d\n",
             path_length(t, start, end));
      break;
    case 11:
      scanf("%d", &node);
      ancestor(t, node);
      break;
    case 12:
      scanf("%d", &node);
      descendant(t, node);
      break;
    case 13:
      bfs(t);
      break;
    case 14:
      dfs(t);
      break;
    case 15:
      print_tree(t);
      break;
    }
  }
  return 0;
}