#include <stdio.h>
// Number to words program
// converts numbers to words
// Arsalaan Ali 251241809
int main(void) {
  while (1) { // loop that runs until user quits
    printf("Please enter a value (1-999, 0 to quit): ");
    int input; // user is asked to input a number
    scanf("%d", &input);
    if (input == 0) {
      break;
    }
    int digits[] = {0, 0, 0}; // array to hold all the digits
    for (int i = 2; i >= 0; i--) {
      digits[i] = input % 10; // the last digit is added to array
      input /= 10;            // the last digit is removed from the number
      if (input == 0) {
        break; // if input is 0 then program ends
      }
    }
    for (int i = 0; i < 3; i++) { // loop that goes through the 3 numbers
      if (i == 0 && digits[i] == 0) {
        continue; // if hundreds place is 0 then we move on
      }
      if (i == 1) { // if tens place is 1 then there are special cases
        if (digits[i] == 1) {
          if (digits[2] == 0) { // special cases depend on the next digit
            printf("ten");
          }
          if (digits[2] == 1) {
            printf("eleven");
          }
          if (digits[2] == 2) {
            printf("twelve");
          }
          if (digits[2] == 3) {
            printf("thirteen");
          }
          if (digits[2] == 4) {
            printf("fourteen");
          }
          if (digits[2] == 5) {
            printf("fifteen");
          }
          if (digits[2] == 6) {
            printf("sixteen");
          }
          if (digits[2] == 7) {
            printf("seventeen");
          }
          if (digits[2] == 8) {
            printf("eighteen");
          }
          if (digits[2] == 9) {
            printf("nineteen");
          }
          break;
        } else { // special cases for tens place if the digit isnt 1
          if (digits[i] == 2) {
            printf("twenty");
          }
          if (digits[i] == 3) {
            printf("thirty");
          }
          if (digits[i] == 4) {
            printf("fourty");
          }
          if (digits[i] == 5) {
            printf("fifty");
          }
          if (digits[i] == 6) {
            printf("sixty");
          }
          if (digits[i] == 7) {
            printf("seventy");
          }
          if (digits[i] == 8) {
            printf("eighty");
          }
          if (digits[i] == 9) {
            printf("ninety");
          }
          if (digits[2] != 0) {
            printf("-"); // if the next digit isnt 0 then there is a dash
                         // between the numbers
          }
        }
      } else {                // for hundreds and ones place
        if (digits[i] == 1) { // print out the digit as a word
          printf("one");
        }
        if (digits[i] == 2) {
          printf("two");
        }
        if (digits[i] == 3) {
          printf("three");
        }
        if (digits[i] == 4) {
          printf("four");
        }
        if (digits[i] == 5) {
          printf("five");
        }
        if (digits[i] == 6) {
          printf("six");
        }
        if (digits[i] == 7) {
          printf("seven");
        }
        if (digits[i] == 8) {
          printf("eight");
        }
        if (digits[i] == 9) {
          printf("nine");
        }
        if (i == 0) { // if its in the hundreds place print 'hundred'
          printf(" hundred ");
          if (digits[1] != 0 || digits[2] != 0) {
            printf("and "); // if there are numbers after the hundred place that
                            // arent zero, then print 'and'
          }
        }
      }
    }
    printf("\n"); // newline after each character
  }
}