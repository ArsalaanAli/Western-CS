#include "worldcup_player.h"
#include "worldcup_team.h"
#include <stdio.h>
#include <stdlib.h>

struct Team *lastNode(struct Team *head) {
  while (head->next) {
    head = head->next;
  }
  return head;
}

struct Player *lastpNode(struct Player *head) {
  while (head->next) {
    head = head->next;
  }
  return head;
}

int main(void) {

  // inputTeam(5);

  struct Team *head;
  head = malloc(sizeof(struct Team));
  head->code = -1;
  head->next = NULL;

  struct Player *pHead;
  pHead = malloc(sizeof(struct Player));
  pHead->code = -1;
  pHead->next = NULL;

  while (1) {
    char menuOp;
    printf("Enter menu option: ");
    scanf(" %c", &menuOp);

    if (menuOp == 'q') {
      return 0;
    }

    if (menuOp == 'h') {
      printf("Commands:\nq: quit\np: control players (i: input, s: search, u: "
             "update player, p: print all, d: delete)\nt: control teams (i: "
             "input, s: search, u: update team, p: print all, d: delete, r: "
             "print players for team)\n");
    }

    if (menuOp == 'p') {
      char command;
      printf("\tEnter a command: ");
      scanf(" %c", &command);

      if (command == 'i') {
        int playerCode;
        int flag = 0;
        printf("\tEnter player code: ");
        scanf("%d", &playerCode);
        if (playerCode < 0) {
          printf("Invalid player code\n");
        }

        struct Player *temp = pHead;
        while (temp) {
          if (temp->code == playerCode) {
            printf("Player already exists\n");
            flag = 1;
            break;
          }
          temp = temp->next;
        }
        if (flag) {
          continue;
        }
        struct Player *other = malloc(sizeof(struct Player));
        inputPlayer(playerCode, other, head);
        struct Player *current = lastpNode(pHead);
        if (other->code > 0) {
          current->next = other;
        }
      }

      if (command == 's') {
        int playerCode;
        int flag = 0;
        printf("\tEnter player code: ");
        scanf("%d", &playerCode);
        struct Player *temp = pHead;
        while (temp) {
          if (temp->code == playerCode) {
            flag = 1;
            printf("Player Code\tPlayer Name\t\tGroup Seeding\tTeam Code\n");
            printPlayer(temp);
            break;
          }
          temp = temp->next;
        }
        if (!flag) {
          printf("Player does not exist");
        }
      }

      if (command == 'u') {
        int playerCode;
        int flag = 0;
        printf("\tEnter player code: ");
        scanf("%d", &playerCode);
        struct Player *temp = head;
        while (temp) {
          if (temp->code == playerCode) {
            struct Player *holdNext = temp->next;
            flag = 1;
            inputPlayer(playerCode, temp, head);
            temp->next = holdNext;
            break;
          }
          temp = temp->next;
        }
        if (!flag) {
          printf("Player does not exist");
        }
      }

      if (command == 'p') {
        struct Player *temp = pHead;
        printf("Player Code\tPlayer Name\t\tGroup Seeding\tTeam Code\n");
        while (temp) {
          if (temp->code >= 0) {
            printPlayer(temp);
          }
          temp = temp->next;
        }
      }

      if (command == 'd') {
        int playerCode;
        int flag = 0;
        printf("\tEnter player code: ");
        scanf("%d", &playerCode);
        struct Player *temp = pHead;
        while (temp) {
          if (temp->next->code == playerCode) {
            struct Player *remove = temp->next;
            temp->next = remove->next;
            free(remove);
            flag = 1;
            break;
          }
          temp = temp->next;
        }
        if (!flag) {
          printf("Player does not exist\n");
        }
      }
    }

    if (menuOp == 't') {
      char command;
      printf("\tEnter a command: ");
      scanf(" %c", &command);

      if (command == 'i') {
        int teamCode;
        int flag = 0;
        printf("\tEnter team code: ");
        scanf("%d", &teamCode);
        if (teamCode < 0) {
          printf("Invalid teamcode\n");
        }

        struct Team *temp = head;
        while (temp) {
          if (temp->code == teamCode) {
            printf("Team already exists\n");
            flag = 1;
            break;
          }
          temp = temp->next;
        }
        if (flag) {
          continue;
        }
        struct Team *other = malloc(sizeof(struct Team));
        inputTeam(teamCode, other);
        struct Team *current = lastNode(head);
        if (other->code > 0) {
          current->next = other;
        }
      }

      if (command == 's') {
        int teamCode;
        int flag = 0;
        printf("\tEnter team code: ");
        scanf("%d", &teamCode);
        struct Team *temp = head;
        while (temp) {
          if (temp->code == teamCode) {
            flag = 1;
            printf(
                "Team Code\tTeam Name\t\tGroup Seeding\tPrimary Kit Colour\n");
            printTeam(temp);
            break;
          }
          temp = temp->next;
        }
        if (!flag) {
          printf("Team does not exist");
        }
      }
      if (command == 'u') {
        int teamCode;
        int flag = 0;
        printf("\tEnter team code: ");
        scanf("%d", &teamCode);
        struct Team *temp = head;
        while (temp) {
          if (temp->code == teamCode) {
            struct Team *holdNext = temp->next;
            flag = 1;
            inputTeam(teamCode, temp);
            temp->next = holdNext;
            break;
          }
          temp = temp->next;
        }
        if (!flag) {
          printf("Team does not exist");
        }
      }
      if (command == 'p') {
        struct Team *temp = head;
        printf("Team Code\tTeam Name\t\tGroup Seeding\tPrimary Kit Colour\n");
        while (temp) {
          if (temp->code >= 0) {
            printTeam(temp);
          }
          temp = temp->next;
        }
      }
      if (command == 'd') {
        int teamCode;
        int flag = 0;
        printf("\tEnter team code: ");
        scanf("%d", &teamCode);
        struct Team *temp = head;
        while (temp) {
          if (temp->next->code == teamCode) {
            struct Team *remove = temp->next;
            temp->next = remove->next;
            free(remove);
            flag = 1;
            break;
          }
          temp = temp->next;
        }
        if (!flag) {
          printf("Team does not exist\n");
        }
      }
      if (command == 'r') {
        int teamCode;
        int flag = 0;
        printf("\tEnter team code: ");
        scanf("%d", &teamCode);
        struct Team *temp = head;
        while (temp) {
          if (temp->code == teamCode) {
            flag = 1;
            break;
          }
          temp = temp->next;
        }
        if (!flag) {
          printf("Team does not exist");
        }

        struct Player *ptemp = pHead;
        printf("\tPlayers in this team:\n");
        printf("Player Code\tPlayer Name\t\tGroup Seeding\tTeam Code\n");
        while (ptemp) {
          if (ptemp->teamCode == teamCode) {
            printPlayer(ptemp);
          }
          ptemp = ptemp->next;
        }
      }
    }
  }
}