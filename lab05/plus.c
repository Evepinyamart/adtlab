#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct list
{
  char *arr;
  int count;
} list_t;

list_t create()
{
  list_t nl;
  nl.arr = (char *)malloc(sizeof(char) * 1000);
  scanf(" %s", nl.arr);
  nl.count = strlen(nl.arr);
  return nl;
}

list_t add(list_t a, list_t b)
{
  short carry = 0;
  int i;
  int maxDigit = a.count >= b.count ? a.count : b.count;
  list_t res;
  res.arr = (char *)calloc(maxDigit, sizeof(char));

  for (i = 0; i < maxDigit; i++)
  {
    int r = 0;
    if (i < a.count)
    {
      r += a.arr[a.count - i - 1] - 48;
    }
    if (i < b.count)
    {
      r += b.arr[b.count - i - 1] - 48;
    }
    r += carry;
    res.arr[maxDigit - i - 1] = r >= 10 ? r - 10 + '0' : r + '0';
    carry = r / 10;
  }
  if (carry > 0)
  {
    res.arr = (char *)realloc(res.arr, (maxDigit + 1) * sizeof(char));
    for (int j = maxDigit; j > 0; j--)
    {
      res.arr[j] = res.arr[j - 1];
    }
    res.arr[0] = '1';
  }
  return res;
}

int main(int argc, char const *argv[])
{
  list_t l1 = create();
  list_t l2 = create();
  list_t res = add(l1, l2);
  printf("%s\n", res.arr);
  free(l1.arr);
  free(l2.arr);
  free(res.arr);
  return 0;
}