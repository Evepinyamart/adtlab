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
  for (int i = 2; i < ((int)sqrt(num)) + 1; i++)
  {
    if (num % i == 0)
    {
      return 0;
    }
  }
  return 1;
}

int main(int argc, char const *argv[])
{
  int num;
  scanf(" %d", &num);
  printf("%d\n", isPrime(num));
  // O(n**1/2)
  return 0;
}
