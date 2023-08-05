#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

void printMaze(int n, char **maze)
{
  int i, j;
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      printf("%c", maze[i][j]);
    }
    printf("\n");
  }
}

bool traverseMaze(int n, char **maze, int current[2])
{
  int x = current[0];
  int y = current[1];
  // still in matrix n*n
  if ((0 <= x && x < n) && (0 <= y && y < n))
  {
    if (maze[x][y] == 'G')
    {
      printMaze(n, maze);
      return true;
    }
    if (maze[x][y] == ' ' || maze[x][y] == 'S')
    {
      if (maze[x][y] == ' ')
        maze[x][y] = '.';

      // visited
      // search up
      int up[2] = {x - 1, y};
      if (traverseMaze(n, maze, up))
      {
        return true;
      }
      // right
      int right[2] = {x, y + 1};
      if (traverseMaze(n, maze, right))
      {
        return true;
      }
      // down
      int down[2] = {x + 1, y};
      if (traverseMaze(n, maze, down))
      {
        return true;
      }
      // left
      int left[2] = {x, y - 1};
      if (traverseMaze(n, maze, left))
      {
        return true;
      }
      if (maze[x][y] == '.')
        maze[x][y] = ' ';
    }
  }
  return false;
}

int main(void)
{
  int n, i, j;
  char **arr;
  int current[2];

  scanf("%d ", &n);
  arr = (char **)malloc(sizeof(char *) * n);
  for (i = 0; i < n; i++)
  {
    j = 0;
    arr[i] = (char *)malloc(sizeof(char) * n);
    fgets(arr[i], n + 2, stdin);
    arr[i][n] = '\0';
    for (j = 0; j < n; j++)
    {
      if (arr[i][j] == 'S')
      {
        current[0] = i;
        current[1] = j;
        break;
      }
    }
  }
  printMaze(n, arr);
  traverseMaze(n, arr, current);

  for (i = 0; i < n; i++)
  {
    free(arr[i]);
  }
  free(arr);

  return 0;
}