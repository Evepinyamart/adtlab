#include <stdio.h>
#include <math.h>

int separatedArea(int col, int row)
{
  if (col == 0 || row == 0)
  {
    return 0;
  }
  if (col == 1 || row == 1)
  {
    return col * row;
  }

  int exp = (int)log2(col > row ? row : col);
  int n = pow(2, exp);

  return 1 + separatedArea(col - n, n) + separatedArea(col, row - n);
}

int main(void)
{
  int col, row;
  scanf(" %d %d", &col, &row);
  printf("%d", separatedArea(col, row));
  // O(n**2)
  return 0;
}
