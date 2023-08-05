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

void pattern1(int n)
{
  int i, j;
  for (i = 1; i < n + 1; i++)
  {
    for (j = 0; j < n; j++)
    {
      printf("%d ", i + (j * n));
    }
    printf("\n");
  }
}

void pattern2(int n)
{
  int i, j;
  for (i = 0; i < n; i++)
  {
    printf("%d ", i + 1);
    for (j = 1; j < n; j++)
    {
      if (j % 2 != 0)
      {
        printf("%d ", i + 1 + ((j + 1) / 2) * (2 * (n - i) - 1) + ((j - 1) / 2) * (2 * i + 1));
      }
      else
      {
        printf("%d ", i + 1 + (j / 2) * (2 * (n - i) - 1) + (j / 2) * (2 * i + 1));
      }
    }
    printf("\n");
  }
}

void pattern3(int n)
{
  int **arr = (int **)malloc(sizeof(int *) * n);
  int i, j, k;
  int num = 1;
  for (i = 0; i < n; i++)
  {
    arr[i] = (int *)calloc(n, sizeof(int));
  }

  for (i = 0; i < 2 * n - 1; i++)
  {
    if (i >= n)
    {
      k = 2 * n - i - 2;
    }
    else
    {
      k = i;
    }

    if (i % 2 == 0)
    {
      for (j = 0; j < k + 1; j++)
      {
        if (i >= n)
        {
          arr[n - j - 1][k - j] = num++;
        }
        else
        {
          arr[k - j][n - j - 1] = num++;
        }
      }
    }
    else
    {
      for (j = k; j >= 0; j--)
      {
        if (i >= n)
        {
          arr[n - j - 1][k - j] = num++;
        }
        else
        {
          arr[k - j][n - j - 1] = num++;
        }
      }
    }
  }
  printArray(arr, n, n);
  for (i = 0; i < n; i++)
  {
    free(arr[i]);
  }
  free(arr);
}

void pattern4(int n)
{
  int **arr = (int **)malloc(sizeof(int *) * n);
  int i, j;
  int num = 1;
  for (i = 0; i < n; i++)
  {
    arr[i] = (int *)calloc(n, sizeof(int));
  }

  int startRow = 0, endRow = n - 1;
  int startCol = 0, endCol = n - 1;

  while (startRow <= endRow && startCol <= endCol)
  {
    for (j = startCol; j <= endCol; j++)
    {
      arr[startRow][j] = num++;
    }
    startRow++;

    for (i = startRow; i <= endRow; i++)
    {
      arr[i][endCol] = num++;
    }
    endCol--;

    if (startRow <= endRow)
    {
      for (j = endCol; j >= startCol; j--)
      {
        arr[endRow][j] = num++;
      }
      endRow--;
    }

    if (startCol <= endCol)
    {
      for (i = endRow; i >= startRow; i--)
      {
        arr[i][startCol] = num++;
      }
      startCol++;
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
  /*int n, pick;
  scanf("%d %d", &n, &pick);
  switch (pick)
  {
  case 1:
    pattern1(n);
    break;
  case 2:
    pattern2(n);
    break;
  case 3:
    pattern3(n);
    break;
  case 4:
    pattern4(n);
    break;
  default:
    break;
  } */
  pattern4(4);
  return 0;
}