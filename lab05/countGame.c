#include <stdio.h>
#include <stdlib.h>

typedef struct player
{
  int playerNum;
  int shotsTaken;
  int shotsDuration;
  struct player *next;
} player_t;

player_t *createCircle(int n)
{
  player_t *firstPlayer = NULL;
  player_t *lastPlayer = NULL;

  for (int i = 0; i < n; i++)
  {
    player_t *newPlayer = (player_t *)malloc(sizeof(player_t));
    newPlayer->playerNum = i + 1;

    // Read shotsDuration value from a single line input
    scanf("%d", &newPlayer->shotsDuration);

    newPlayer->shotsTaken = 0;
    newPlayer->next = NULL;

    if (firstPlayer == NULL)
    {
      firstPlayer = newPlayer;
      lastPlayer = newPlayer;
    }
    else
    {
      lastPlayer->next = newPlayer;
      lastPlayer = newPlayer;
    }
  }

  if (lastPlayer != NULL)
  {
    lastPlayer->next = firstPlayer; // Connect the last player to the first
  }

  return firstPlayer;
}

int inAnyDigit(int k, int num)
{
  while (num != 0)
  {
    if (k == num % 10)
    {
      return 1;
    }
    num /= 10;
  }
  return 0;
}

player_t *playGame(int n, int k, player_t *firstPlayer)
{
  player_t *p = firstPlayer;
  player_t *lastPerson = NULL;
  int countNum = 1;

  while (p->next != p)
  {
    if (countNum % k == 0 || inAnyDigit(k, countNum))
    {
      p->shotsTaken += 1;
    }

    if (p->shotsTaken > p->shotsDuration)
    {
      player_t *tmp = p;
      p = p->next;

      if (tmp == firstPlayer)
      {
        firstPlayer = p;
      }

      if (lastPerson != NULL)
      {
        lastPerson->next = p;
      }

      free(tmp);
    }
    else
    {
      lastPerson = p;
      p = p->next;
    }

    countNum++;
  }

  return p;
}

int main(void)
{
  player_t *firstPlayer = NULL;
  int n, k;
  scanf("%d %d", &n, &k);
  firstPlayer = createCircle(n);
  firstPlayer = playGame(n, k, firstPlayer);
  printf("%d\n", firstPlayer->playerNum);
  return 0;
}
