struct Team {
  int code;
  char name[25];
  char seeding[3];
  char colour[10];
  struct Team *next;
};

void inputTeam(int teamCode, struct Team *other);

void printTeam(struct Team *team);

void updateTeam(struct Team *team);