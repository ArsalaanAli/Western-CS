#include <stdio.h>
int main()
{
    int int1, int2, int3, int4;
    int maxInt;
    int minInt;
    printf("Enter 4 integers: ");
    scanf("%d %d %d %d", &int1, &int2, &int3, &int4);
    maxInt = int1 > int2 ? int1 : int2;
    maxInt = maxInt > int3 ? maxInt : int3;
    maxInt = maxInt > int4 ? maxInt : int4;
    minInt = int1 < int2 ? int1 : int2;
    minInt = minInt < int3 ? minInt : int3;
    minInt = minInt < int4 ? minInt : int4;
    printf("Number = %d %d\n", maxInt, minInt);

    int daysInMonth, startingDay;
    printf("Enter length of month and starting day: ");
    scanf("%d %d", &daysInMonth, &startingDay);
    for (int i = 0; i<startingDay-1; i++){
        printf("   ");
    }

    int currentDay = 1;
    for (int i = 0; i<7-(startingDay-1); i++){
        printf("%3d", currentDay);
        currentDay++;
    }
    printf("\n");
    while(currentDay < daysInMonth){
        for (int i = 0; i<7; i++){
        printf("%3d", currentDay);
        currentDay++;
        if(currentDay>daysInMonth){
            break;
            }
        }
        printf("\n");
    }
    return 0;
}