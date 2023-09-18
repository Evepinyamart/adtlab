#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
  float data;
  struct node *next;
} node_t;
typedef node_t stack_t;

stack_t *push(stack_t *s, float value)
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
  int n;
  stack_t *s = NULL;
  scanf(" %d", &n);
  for (int i = 0; i < n; i++)
  {
    char ch;
    scanf(" %c", &ch);
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
    {
      stack_t *tmp = s;
      s = s->next->next;
      float a = (float)tmp->data;
      float b = (float)tmp->next->data;
      if (ch == '+')
      {
        s = push(s, b + a);
      }
      else if (ch == '-')
      {
        s = push(s, b - a);
      }
      else if (ch == '*')
      {
        s = push(s, b * a);
      }
      else
      {
        s = push(s, b / a);
      }
      free(tmp->next);
      free(tmp);
    }
    else
    {
      s = push(s, (float)ch - '0');
    }
  }
  printf("%.2f\n", s->data);
  return 0;
}
