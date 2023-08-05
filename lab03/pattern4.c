#include <stdio.h>
#include <stdlib.h>
void printArray(int **arr, int x, int y)
{
  int i, j;
  for (j = 0; j < y; j++)
  {
    for (i = 0; i < x; i++)
    {
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
}

void pattern4(int n)
{
  int **arr = (int **)malloc(sizeof(int *) * n);
  int i = 0, j = 0, k;
  int num = 1;
  for (i = 0; i < n; i++)
  {
    arr[i] = (int *)calloc(n, sizeof(int));
  }

  // start
  for (k = 0; k < 2 * n - 1; k++)
  {
    for (j = k; j < n - k; j++)
    {
      arr[k][j] = num++;
    }
    j--;
    for (i = k + 1; i < n - k; i++)
    {
      arr[i][j] = num++;
    }
    i--;
    for (j = n - k - 2; j >= k; j--)
    {
      arr[i][j] = num++;
    }
    j++;
    for (i = n - k - 2; i > k; i--)
    {
      arr[i][j] = num++;
    }
  }

  printArray(arr, n, n);
  for (i = 0; i < n; i++)
  {
    free(arr[i]);
  }
  free(arr);
}

int main(void)
{
  pattern4(5);
  return 0;
}