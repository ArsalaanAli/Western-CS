worldCupDB: worldCupDB.o worldcup_player.o worldcup_team.o
gcc -o worldCupDB worldCupDB.o worldcup_player.o worldcup_team.o

worldCupDB.o: worldCupDB.c worldcup_player.h worldcup_team.h
gcc -c worldCupDB.c

worldcup_player.o: worldcup_player.c worldcup_player.h worldcup_team.h
gcc -c worldcup_player.c

worldcup_team.o: worldcup_team.c worldcup_team.h
gcc -c worldcup_team.c