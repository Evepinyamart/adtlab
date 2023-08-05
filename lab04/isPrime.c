#include <stdio.h>
#include <math.h>
int isPrime(int num)
{
  if (num < 2)
  {
    return 0;
  }
  if (num <= 3)
  {
    return 1;
  }
  if (num == 5 || num == 7)
  {
    return 1;
  }
  if (sqrt((double)num) == (int)sqrt((double)num))
  {
    return 0;
  }

  if (num % 2 == 0 || num % 3 == 0 || num % 5 == 0 || num % 7 == 0)
  {
    return 0;
  }
  return 1;
}

int main(void)
{
  int num;
  scanf(" %d", &num);
  printf("%d\n", isPrime(num));
  // O(1)
  return 0;
}
