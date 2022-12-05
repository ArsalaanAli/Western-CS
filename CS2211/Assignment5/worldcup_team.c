#include "worldcup_team.h"
#include <stdio.h>

void inputTeam(int teamCode, struct Team *other) {
  other->code = -1;

  char name[25];
  printf("\tEnter team name: ");
  scanf("%25s", name);

  char seeding[2];
  printf("\tEnter group seeding: ");
  scanf("%s", seeding);
  if (seeding[0] < 65 || seeding[0] > 72 || seeding[1] < 49 ||
      seeding[1] > 52) {
    printf("Error: improper group seeding\n");
		return;
  }
  char colour;
  char availColours[7][10] = {"Red",  "Orange", "Yellow", "Green",
                              "Blue", "Indigo", "Violet"};
  int chosenColour = -1;
  printf("\tEnter the kit colour: ");
  scanf(" %c", &colour);

  for (int i = 0; i < 7; i++) {
    if (availColours[i][0] == colour) {
      chosenColour = i;
      break;
    }
  }
  if (chosenColour == -1) {
    printf("Error: improper kit colour\n");
		return;
  }

  other->code = teamCode;
  other->next = NULL;
  strncpy(other->name, name, 25);

  strncpy(other->seeding, seeding, 2);

  strncpy(other->colour, availColours[chosenColour], 10);
}

void printTeam(struct Team *team) {
  printf("%-12d%-16s%-16s%s\n", team->code, team->name, team->seeding,
         team->colour);
}