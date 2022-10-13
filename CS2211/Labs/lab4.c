#include <stdio.h>

int closestDeparture(int time){
	int dep[8] = {480, 583, 679, 767, 840, 945, 1140, 1305};
	int small = 10000000;
	int ind = 0;
	for(int i = 0; i<8; i++){
		if(abs(dep[i]-time) < small){
			small = abs(dep[i]-time);
			ind = i;
		}
	}
	return ind;
}
void printTime(int hour, int min){
	int pm = 0;
	if(hour>12){
		hour%=12;
		pm = 1;
	}
	if(hour==0){
		hour=12;
	}
  printf("%d:%02d", hour, min);
	if(pm){
		printf(" pm");
	}
	else{
		printf(" am");
	}
}



int main(void) {
	
  int hour, min;
	while(1){
		printf("Enter a 24-hour time: ");
	  scanf("%d%*c%d", &hour, &min);
		int minFromMid = hour*60 + min;
		int bestTime = closestDeparture(minFromMid);
		int arivH[8] = {10, 11, 13, 15, 16, 17, 21, 23};
		int arivM[8] = {16, 52, 31, 0, 8, 55, 20, 58};
		int depH[8] = {8, 9, 11, 12, 14, 15, 19, 21};
		int depM[8] = {0, 43, 19, 47, 0 ,45, 0, 45};
		printf("Closest departure time is ");
		printTime(depH[bestTime], depM[bestTime]);
		printf(", arriving at ");
		printTime(arivH[bestTime], arivM[bestTime]);
		int x;
	  printf("\nEnter 1 to continue or 0 to quit: ");
		scanf("%d", &x);
		if(!x){
			break;
		}
	}
  
}