#include <stdio.h>
#include <math.h>

int main(void)
{
  int a, b, area, round, row, col;
  a = 9;
  b = 11;
  area = a * b;
  row = a, col = b;
  int landNum = 0;
  if (a % 2 != 0)
  {
    area -= b;
    a--;
    landNum += b;
  }
  if (b % 2 != 0)
  {
    area -= a;
    b--;
    landNum += a;
  }
  if (a % 2 != 0 && b % 2 != 0)
  {
    area++;
    landNum--;
  }

  int n;
  while (area > 0)
  {
    int n = (int)log2(a < b ? a : b);
    a -= pow(2, n);
    b -= pow(2, n);
    if (a == 0 && b != 0)
      a += row;
    if (b == 0 && a != 0)
      b += col;
    landNum++;
    area -= pow((pow(2, n)), 2);
  }
  printf("%d", landNum);

  return 0;
}
