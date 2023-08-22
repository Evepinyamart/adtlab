#include <stdio.h>
#include <stdlib.h>

struct node
{
  char data;
  struct node *next;
};

typedef struct node stack_t;

int isEmpty(stack_t *s)
{
  return s == NULL;
}

int isMatch(int p1, int p2)
{
  return (p1 == '{' && p2 == '}') || (p1 == '(' && p2 == ')') || (p1 == '[' && p2 == ']');
}

stack_t *pop(stack_t *s)
{
  stack_t *tmp = NULL;
  if (s != NULL)
  {
    tmp = s;
    s = s->next;
    free(tmp);
  }
  return s;
}

stack_t *push(stack_t *s, int value)
{
  stack_t *newData = (stack_t *)malloc(sizeof(stack_t));
  newData->data = value;
  newData->next = NULL;
  if (s == NULL)
  {
    s = newData;
    return s;
  }
  newData->next = s;
  s = newData;
  return s;
}

int main(void)
{
  stack_t *pStack = NULL;
  int n;
  char d;
  scanf(" %d", &n);
  for (int i = 0; i < n; i++)
  {
    scanf(" %c", &d);
    if (d == '(' || d == '[' || d == '{')
    {
      pStack = push(pStack, d);
    }
    else
    {
      if (isEmpty(pStack) || !isMatch(pStack->data, d))
      {
        printf("0");
        return 0;
      }
      else
      {
        pStack = pop(pStack);
      }
    }
  }
  printf("1\n");
  return 0;
}
