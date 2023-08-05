#include <stdio.h>
#include <stdlib.h>

int sortArray(int *arr, int size)
{
  int i, j;
  for (i = 0; i < size - 1; i++)
  {
    for (j = 0; j < size - i - 1; j++)
    {
      if (*(arr + j) > *(arr + j + 1))
      {
        // Swap the elements
        int temp = *(arr + j);
        *(arr + j) = *(arr + j + 1);
        *(arr + j + 1) = temp;
      }
    }
  }
  return 0;
}

int main(void)
{
  int round, i, j;
  int **countNum = NULL;
  countNum = (int **)malloc(sizeof(int *));
  int *maxptr = NULL;

  scanf("%d", &round);
  int size = 0, max = 1, sizep = 0;

  for (i = 0; i < round; i++)
  {
    int num;
    scanf("%d", &num);
    int k;
    int isin = 0;
    for (k = 0; k < size; k++)
    {
      if (countNum[k][0] == num)
      {
        countNum[k][1] += 1;
        isin = 1;
        if (max < countNum[k][1])
        {
          max = countNum[k][1];
        }
        break;
      }
    }
    if (isin == 0)
    {
      countNum = realloc(countNum, (size + 1) * sizeof(int *));
      countNum[size] = (int *)malloc(sizeof(int) * 2);
      countNum[size][0] = num;
      countNum[size][1] = 1;
      size += 1;
    }
  }

  maxptr = (int *)malloc(sizeof(int) * size);

  for (i = 0; i < size; i++)
  {
    if (countNum[i][1] == max)
    {
      maxptr[sizep] = countNum[i][0];
      sizep += 1;
    }
  }

  sortArray(maxptr, sizep);

  for (i = 0; i < sizep; i++)
  {
    printf("%d ", maxptr[i]);
  }

  // Free allocated memory
  for (i = 0; i < size; i++)
  {
    free(countNum[i]);
  }
  free(countNum);
  free(maxptr);

  return 0;
}
