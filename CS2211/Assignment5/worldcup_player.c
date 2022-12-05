#include "worldcup_player.h"
#include "worldcup_team.h"
#include <stdio.h>

void inputPlayer(int playerCode, struct Player *other, struct Team *head) {
  other->code = -1;

  char name[50];
  printf("\tEnter player name: ");
  scanf("%50s", name);

  int age;
  printf("\t Enter player age: ");
  scanf("%d", &age);
  if (age < 17 || age > 99) {
    return;
  }

  char club[50];
  printf("\tEnter club name: ");
  scanf("%50s", club);

  int teamCode;
  int flag = 0;
  printf("\tEnter team code: ");
  scanf("%d", &teamCode);
  while (head) {
    if (head->code == teamCode) {
      flag = 1;
    }
    head = head->next;
  }
  if (!flag) {
    printf("invalid team code");
  }

  other->code = playerCode;
  other->teamCode = teamCode;
  other->next = NULL;
  strncpy(other->name, name, 50);
  strncpy(other->club, club, 50);
}

void printPlayer(struct Player *player) {
  printf("%-12d%-16s%-16s%d\n", player->code, player->name, player->club,
         player->teamCode);
}