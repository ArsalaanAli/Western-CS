#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int input_array[4];

void *sum(void *thread_id) {
  int x = input_array[0];
  int y = input_array[1];
	printf("3. thread_1 (TID %lu) reads X = %d and Y = %d from input_array[]\n", pthread_self(), x, y);
  input_array[2] = x + y;
	printf("4. thread_1 (TID %lu) writes X + Y = %d to the input_array[2]\n", pthread_self(), input_array[2]);
  return 0;
}

void *multiplication(void *thread_id) {
	int x = input_array[0] ;
	int y = input_array[1];
  input_array[3] = x*y;
	printf("7. thread_2 (TID %lu) reads X and Y from input_array[], writes X * Y = %d to input_array[3]\n", pthread_self(), input_array[3]);
  return 0;
}

void *even_odd(void *thread_id) {
  pthread_t *first_thread = (pthread_t *)thread_id;
  pthread_join(*first_thread, NULL);
  int s = input_array[2];
	printf("5. thread_2 (TID %lu) reads %d from the input_array[2]\n", pthread_self(), s);
	if(s%2==0){
		printf("6. thread_2 (TID %lu) identifies that %d is an even number\n", pthread_self(), s);
	}
	else{
		printf("6. thread_2 (TID %lu) identifies that %d is an odd number\n", pthread_self(), s);
	}
	multiplication(NULL);
  return 0;
}

void *reverse_num(void *thread_id){
	pthread_t *second_thread = (pthread_t *)thread_id;
	pthread_join(*second_thread, NULL);
	int M = input_array[3];
	printf("8. thread_3 (TID %lu) reads %d from input_array[3]\n", pthread_self(), M);
	int reverse = 0, remainder;
	while (M != 0) {
		remainder = M % 10;
		reverse = reverse * 10 + remainder;
		M /= 10;
	}
	printf("9. thread_3 (TID %lu) reverses the number %d -> %d\n", pthread_self(), input_array[3], reverse);
	return 0;
}

int main(int argc, char **argv) {
  int x = atoi(argv[1]);
  int y = atoi(argv[2]);
  printf("1. parent (PID %d) receives X = %d and Y = %d from the user\n", getpid(), x, y);
  input_array[0] = x;
  input_array[1] = y;
	printf("2. parent (PID %d) writes X = %d and Y = %d to input_array[]\n", getpid(), x, y);
  pthread_t thread_1, thread_2, thread_3;
  pthread_create(&thread_1, NULL, sum, NULL);
  pthread_create(&thread_2, NULL, even_odd, &thread_1);
	pthread_create(&thread_3, NULL, reverse_num, &thread_2);
  pthread_join(thread_3, NULL);
}