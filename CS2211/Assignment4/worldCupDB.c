#include <stdio.h>
#include <string.h>

struct Team {//a struct to hold the team information
  int code;
  char name[25];
  char seeding[3];
  char colour[10];
};

struct Team inputTeam(int teamCode) {//a function to get the team information and return it in a team struct
  struct Team tempTeam;//temporary team struct to hold all inputted information
  tempTeam.code = -1;//if teamcode is -1 when the struct is returned, then there was an invalid input

  char name[25];
  printf("\tEnter team name: ");//gets team name
  scanf("%25s", name);

  char seeding[2];
  printf("\tEnter group seeding: ");//gets team seeding
  scanf("%s", seeding);
  if (seeding[0] < 65 || seeding[0] > 72 || seeding[1] < 49 ||
      seeding[1] > 52) {
    printf("Error: improper group seeding\n");
    return tempTeam;//if the group seeding is invalid, then returns to main menu with empty struct
  }
  char colour;
  char availColours[7][10] = {"Red",  "Orange", "Yellow", "Green",
                              "Blue", "Indigo", "Violet"};
  int chosenColour = -1;
  printf("\tEnter the kit colour: ");
  scanf(" %c", &colour);//gets team colours by checking if the char inputted is equal to the first letter of any available colour
  for (int i = 0; i < 7; i++) {
    if (availColours[i][0] == colour) {
      chosenColour = i;
      break;
    }
  }
  if (chosenColour == -1) {
    printf("Error: improper kit colour\n");//if the colour wasn't valid, then returns to main menu with empty struct
    return tempTeam;
  }

  tempTeam.code = teamCode;
  strncpy(tempTeam.name, name, 25);
  strncpy(tempTeam.seeding, seeding, 2);
  strncpy(tempTeam.colour, availColours[chosenColour], 10);//copies the information of the team to the struct, and returns it
  return tempTeam;
}

void printTeam(struct Team team) {//a function to print the team information
  printf("%-12d%-16s%-16s%s\n", team.code, team.name, team.seeding,
         team.colour);
}

int main(void) {
  struct Team teams[32];//database to hold all the teams
  for (int i = 0; i < 32; i++) {
    teams[i].code = -1;//initializing the team codes to -1, this way we know whether a team has been initialized
  }
  while (1) {//loop so the program run until quitted
    char operationCode;
    printf("Enter operation code: ");//getting optation code
    scanf(" %c", &operationCode);

    if (operationCode == 'i') {//input operation code

      int teamCode;
      printf("\tEnter team Code: ");
      scanf("%d", &teamCode);
      if (teamCode < 0 || teamCode >= 32) {
        printf("Error: improper team code\n");//if the team code is invalid returns to main menu
        continue;
      }
      if (teams[teamCode].code != -1) {
        printf("Error: team code already exists in database\n"); //if the team already exists returns to main menu
        continue;
      }

      struct Team createdTeam = inputTeam(teamCode);//gets team input
      if (createdTeam.code == -1) {//if input was invalid returns to main menu
        continue;
      } else {
        teams[teamCode] = createdTeam;//otherwise adds team to database
      }
    }

    if (operationCode == 's') {//searches for a team
      int teamCode;
      printf("\tEnter team code: ");
      scanf("%d", &teamCode);
      if (teams[teamCode].code == -1) {// if the team doesnt exist returns to main menu
        printf("Team not found\n");
        continue;
      } else {
        printf("Team Code\tTeam Name\t\tGroup Seeding\tPrimary Kit Colour\n");//otherwise prints team information
        printTeam(teams[teamCode]);
      }
    }

    if (operationCode == 'u') {//update a team

      int teamCode;
      printf("\tEnter Team Code: ");
      scanf("%d", &teamCode);
      if (teamCode < 0 || teamCode >= 32) {
        printf("Error: improper team code\n");
        continue;
      }
      if (teams[teamCode].code == -1) {
        printf("Error: team code does not exist in database\n");//if the team code doesnt exist returns to main menu
        continue;
      }

      struct Team createdTeam = inputTeam(teamCode);//otherwise gets input for the team
      if (createdTeam.code == -1) {
        continue;//if invalid input returns to main menu
      } else {
        teams[teamCode] = createdTeam;//otherwise adds the team to the database
      }
    }

    if (operationCode == 'p') {//prints out all teams in database
      printf("Team Code\tTeam Name\t\tGroup Seeding\tPrimary Kit Colour\n");//print header
      for (int i = 0; i < 32; i++) {
        if (teams[i].code != -1) {
          printTeam(teams[i]);//print each team that is initialized in database
        }
      }
      printf("\n");
    }
    if (operationCode == 'q') {//ends the program by returning
      printf("Ending Program.");
      return 0;
    }
  }
}