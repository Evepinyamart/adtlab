#include <stdio.h>
#include <stdlib.h>
void findStats(int *maxi, int *mini, double *avg, int n, int *nums)
{
  *maxi = 0;
  *mini = 999;
  float sum = 0;
  int i;
  for (i = 0; i < n; i++)
  {
    if (*(nums + i) > *maxi)
    {
      *maxi = *(nums + i);
    }
    if (*(nums + i) < *mini)
    {
      *mini = *(nums + i);
    }
    sum += *(nums + i);
  }
  *avg = sum / n;
}
int main()
{
  int n, i, maxi, mini;
  double avg;
  int *nums;
  scanf("%d", &n);
  nums = (int *)malloc(sizeof(int) * n);
  for (i = 0; i < n; i++)
    scanf("%d", nums + i);
  findStats(&maxi, &mini, &avg, n, nums);
  printf("%.2f %d %d", avg, maxi, mini);
  return 0;
}