#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
  char data;
  struct node *next;
  struct node *prev;
} node_t;
typedef node_t queue_t;

queue_t *rear;

queue_t *enqueue(queue_t *q, char value)
{
  queue_t *nextNode = (queue_t *)malloc(sizeof(queue_t));
  nextNode->data = value;
  nextNode->next = NULL;
  nextNode->prev = NULL;

  if (q == NULL)
  {
    q = nextNode;
    rear = q;
  }
  else
  {
    nextNode->prev = rear;
    rear->next = nextNode;
    rear = rear->next;
  }
  return q;
}

int checkPassword(queue_t *front, queue_t *last)
{
  // last is the character before y
  while (front->data != 'x' && last->data != 'x')
  {
    if (front->data != last->data)
    {
      return 0;
    }
    front = front->next;
    last = last->prev;
  }
  if (front->data != 'x' || last->data != 'x')
  {
    // for the case that the length of the right side and the left side of x are not equal
    return 0;
  }
  else
  {
    return 1;
  }
}

int main(void)
{
  queue_t *password = NULL;
  char ch;
  do
  {
    scanf("%c", &ch);
    password = enqueue(password, ch);
  } while (ch != 'y');
  printf("%d\n", checkPassword(password, rear->prev));

  // clear the allocated memory
  while (password != NULL)
  {
    queue_t *tmp = password;
    password = password->next;
    free(tmp);
  }
  return 0;
}
