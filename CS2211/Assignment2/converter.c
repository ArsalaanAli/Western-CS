#include <stdio.h>
//Converter program
//converts between different units
//Arsalaan Ali 251241809
int main(void) {
	while(1){//loop that runs until user quits
	  int conversionType = 0;
		//printing different options
	  printf("1 for conversion between Kilograms and Pounds\n");
	  printf("2 for conversion between Hectares and Acres\n");
	  printf("3 for conversion between Litres and Gallons\n");
	  printf("4 for conversion between Kilometre and Mile\n");
	  printf("5 for quit\n");
		printf("Choose an option: ");
	  scanf("%d", &conversionType); //getting input from user
	  if (conversionType < 1 || conversionType > 5) {
	    printf("Improper input please try again.");
	    continue;
	  }
		//printing different options
	  if (conversionType == 1) {
	    printf("K for conversion from Kilograms to Pounds\n");
	    printf("P for conversion from Pounds to Kilograms\n");
	  }
	  if (conversionType == 2) {
	    printf("H for conversion from Hectares to Acres\n");
	    printf("A for conversion from Acres to Hectares\n");
	  }
	  if (conversionType == 3) {
	    printf("L for conversion from Litres to Gallons\n");
	    printf("G for conversion from Gallons to Litres\n");
	  }
	  if (conversionType == 4) {
	    printf("K for conversion from Kilometre to Mile\n");
	    printf("M for conversion from Mile to Kilometre\n");
	  }
	  char conversionMode;
	  printf("Enter a character to choose which conversion you want: ");
	  scanf(" %c", &conversionMode);//getting input for which conversion mode the user wants
	  double convertNum;
	  if (conversionType == 1) {//checking if the user entered the right character value for their converstion, and printing out the converted value
	    if (conversionMode == 'K') {
	      printf("Enter a value: ");
	      scanf("%lf", &convertNum);
	      convertNum *= 2.20462;//converting value
	      printf("Your conversion is: %f pounds", convertNum);//printing out converted value
	    } else if (conversionMode == 'P') {
	      printf("Enter a value: ");
	      scanf("%lf", &convertNum);
	      convertNum /= 2.20462;
	      printf("Your conversion is: %f kilograms", convertNum);
	    } else {
	      printf("Improper input please try again.");//if input is improper then user is asked to try again.
	    }
	  }
		//same thing is done for all other conversion types
	  if (conversionType == 2) {
	    if (conversionMode == 'H') {
	      printf("Enter a value: ");
	      scanf("%lf", &convertNum);
	      convertNum *= 2.47105;
	      printf("Your conversion is: %f acres", convertNum);
	    } else if (conversionMode == 'A') {
	      printf("Enter a value: ");
	      scanf("%lf", &convertNum);
	      convertNum /= 2.47105;
	      printf("Your conversion is: %f hectares", convertNum);
	    } else {
	      printf("Improper input please try again.");
	    }
	  }
	  if (conversionType == 3) {
	    if (conversionMode == 'L') {
	      printf("Enter a value: ");
	      scanf("%lf", &convertNum);
	      convertNum *= 0.264172;
	      printf("Your conversion is: %f gallons", convertNum);
	    } else if (conversionMode == 'G') {
	      printf("Enter a value: ");
	      scanf("%lf", &convertNum);
	      convertNum /= 0.264172;
	      printf("Your conversion is: %f litres", convertNum);
	    } else {
	      printf("Improper input please try again.");
	    }
	  }
	  if (conversionType == 4) {
	    if (conversionMode == 'K') {
	      printf("Enter a value: ");
	      scanf("%lf", &convertNum);
	      convertNum *= 0.621371;
	      printf("Your conversion is: %f miles", convertNum);
	    } else if (conversionMode == 'M') {
	      printf("Enter a value: ");
	      scanf("%lf", &convertNum);
	      convertNum /= 0.621371;
	      printf("Your conversion is: %f kilometres", convertNum);
	    } else {
	      printf("Improper input please try again.");
	    }
	  }
		printf("\n");
	}
}