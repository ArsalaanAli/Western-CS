#include <stdio.h>
#include <string.h>

struct Team {
  int code;
  char name[25];
  char seeding[3];
  char colour[10];
};

struct Team inputTeam(int teamCode) {
  struct Team tempTeam;
  tempTeam.code = -1;

  char name[25];
  printf("\tEnter team name: ");
  scanf("%25s", name);

  char seeding[2];
  printf("\tEnter group seeding: ");
  scanf("%s", seeding);
  if (seeding[0] < 65 || seeding[0] > 72 || seeding[1] < 49 ||
      seeding[1] > 52) {
    printf("Error: improper group seeding\n");
    return tempTeam;
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
    return tempTeam;
  }

  tempTeam.code = teamCode;
  strncpy(tempTeam.name, name, 25);
  strncpy(tempTeam.seeding, seeding, 2);
  strncpy(tempTeam.colour, availColours[chosenColour], 10);
  return tempTeam;
}

void printTeam(struct Team team) {
  printf("%-12d%-16s%-16s%s\n", team.code, team.name, team.seeding,
         team.colour);
}

int main(void) {
  struct Team teams[32];
  for (int i = 0; i < 32; i++) {
    teams[i].code = -1;
  }
  while (1) {
    char operationCode;
    printf("Enter operation code: ");
    scanf(" %c", &operationCode);

    if (operationCode == 'i') {

      int teamCode;
      printf("\tEnter team Code: ");
      scanf("%d", &teamCode);
      if (teamCode < 0 || teamCode >= 32) {
        printf("Error: improper team code\n");
        continue;
      }
      if (teams[teamCode].code != -1) {
        printf("Error: team code already exists in database\n");
        continue;
      }

      struct Team createdTeam = inputTeam(teamCode);
      if (createdTeam.code == -1) {
        continue;
      } else {
        teams[teamCode] = createdTeam;
      }
    }

    if (operationCode == 's') {
      int teamCode;
      printf("\tEnter team code: ");
      scanf("%d", &teamCode);
      if (teams[teamCode].code == -1) {
        printf("Team not found\n");
        continue;
      } else {
        printf("Team Code\tTeam Name\t\tGroup Seeding\tPrimary Kit Colour\n");
        printTeam(teams[teamCode]);
      }
    }

    if (operationCode == 'u') {

      int teamCode;
      printf("\tEnter Team Code: ");
      scanf("%d", &teamCode);
      if (teamCode < 0 || teamCode >= 32) {
        printf("Error: improper team code\n");
        continue;
      }
      if (teams[teamCode].code == -1) {
        printf("Error: team code does not exist in database\n");
        continue;
      }

      struct Team createdTeam = inputTeam(teamCode);
      if (createdTeam.code == -1) {
        continue;
      } else {
        teams[teamCode] = createdTeam;
      }
    }

    if (operationCode == 'p') {
      printf("Team Code\tTeam Name\t\tGroup Seeding\tPrimary Kit Colour\n");
      for (int i = 0; i < 32; i++) {
        if (teams[i].code != -1) {
          printTeam(teams[i]);
        }
      }
      printf("\n");
    }
    if (operationCode == 'q') {
      printf("Ending Program.");
      return 0;
    }
  }
}