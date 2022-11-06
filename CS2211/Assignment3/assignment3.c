 
#include <stdio.h>
 
int main(void)
{
    //input
    int input;
    printf("Please enter the number of integers to process: ");
    int array[input];
    scanf("%d", &input);
    if(input > 12){
        printf("There is not enough room in your array for %d integers (%d bytes)", input, sizeof(input));
        return 0;
    }
    if(input < 5){
        printf("Your array size %d is too small", input);
        return 0;
    }
    printf("There is enough room in your array for %d integers (%d bytes)", input, sizeof(input));
    printf("Please enter your integers separated by spaces: ");
    for (int i = 0; i < input; i++){
        scanf("%d", &array[i]);
    }

    //Part 1:
    printf("Your array is: ");
    for (int i = 0; i < input; i++){
        printf("[%d] = %d, ", i, array[i]);
    }

    //Part 2:
    
}