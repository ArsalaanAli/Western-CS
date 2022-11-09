#include <stdio.h>

int max(int array[], int arraySize) {//function to find the largest value in an array, takes in an array and its length
  int large = array[0];//variable to hold largest value
  for (int i = 0; i < arraySize; i++) {
    if (array[i] > large) {
      large = array[i];//loop through list, if larger value is found, set it to the variable
    }
  }
  return large;//return the variable for the largest value
}

void sortArray(int array[], int arraySize) {//function to sort an array
	int done = 0;//boolean variable to check if done sorting
	while(!done){
		for(int i = 0; i< arraySize; i++){//loop through array
			if(i == arraySize-1){//if at the end of the array, sorting is finished
				done = 1;
				break;
			}
			if(array[i] < array[i+1]){//if the current value is less than the next value, the current value is moved over one index
				int temp = array[i];
				array[i] = array[i+1];
				array[i+1] = temp;
				break;//break to rerun loop from the start of the array
			}
		}
	}
}


int main(void) {
  // input
  int input;
  printf("Please enter the number of integers to process: ");
  scanf("%d", &input);//getting input
  int array[input];
  if (input > 12) {//checking if it is a valid input
    printf("There is not enough room in your array for %d integers (%d bytes)",
           input, sizeof(array));
    return 0;
  }
  if (input < 5) {
    printf("Your array size %d is too small", input);//if not a valid input, the user is notified
    return 0;
  }
  printf("\tThere is enough room in your array for %d integers (%d bytes)", input,
         sizeof(array));//telling the user how much room their array takes up
  printf("\n\nPlease enter your integers separated by spaces: ");
  for (int i = 0; i < input; i++) {
    scanf("%d", &array[i]);//getting input for integers in array
  }

  // Part 1:
	printf("\nPart1:");
  printf("\n\tYour array is: ");
  for (int i = 0; i < input; i++) {
    printf("[%d] = %d, ", i, array[i]);//printing out values in array
  }

  // Part 2:
	printf("\n\nPart2:");
  int large = max(array, input);//using custom max function to find largest value in array

  printf("\n\tThe largest value in your array is: %d", large);//printing largest value

  // Part 3:
	printf("\n\nPart3:");
  printf("\n\tYour array in reverse is: ");
  for (int i = input - 1; i >= 0; i--) {
    printf("%d ", array[i]);//printing array backwards, using descendind loop
  }

  // Part 4:
	printf("\n\nPart4:");
  int sum = 0;//vairable to hold sum
  for (int i = 0; i < input; i++) {
    sum += array[i];//getting sum of array values
  }
  printf("\n\tThe sum of all the values in your array is: %d", sum);//pritning out sum	
	
	//Part 5:
	int sortedArray[input];//array that holds the sorted integers
	for (int i = 0; i < input; i++) {
		sortedArray[i] = array[i];//creating copy of array so that original array is not changed
	}
	printf("\n\n Part5:");
	sortArray(sortedArray, input);//sorting the copied array using custom sort function
	printf("\n\tYour array in sorted order is: ");
	for (int i = 0; i < input; i++) {
    printf("%d ", sortedArray[i]);//printing out sorted array
  }

	//Part 6:
  int switched[input];//array that holds the integers with first and last int switched
	for (int i = 0; i < input; i++) {
		switched[i] = array[i];//creating copy of array so that original array is not changed
	}
	int temp = switched[0];
	switched[0] = switched[input-1];
	switched[input-1] = temp;//swithcing the first and last int
    
	printf("\n\nPart6:");
	printf("\n\tYour array with first and last element switched is: ");
	for (int i = 0; i < input; i++) {
    printf("%d ", switched[i]);//printing out switched array
  }
}