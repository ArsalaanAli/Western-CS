#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int summation(int start, int end)
{
	int sum = 0;
	if (start < end)
	{
		sum = ((end * (end + 1)) - (start * (start - 1))) / 2;
	}
	return sum;
}

int ith_part_start(int i, int N, int M)
{
	int part_size = N / M;
	int start = i * part_size;
	return start;
}
int ith_part_end(int i, int N, int M)
{
	int part_size = N / M;
	int end = (i < M - 1) ? ((i + 1) * part_size - 1) : N;
	return end;
}
int main(int argc, char **argv)
{
	printf("parent(PID %d): process started\n\n", getpid());
	printf("parent(PID %d): forking child_1\n", getpid());
	int M = 5;
	int N = 12;
	int c1 = fork();
	if(c1 > 0){
		printf("parent(PID %d): fork successful for child_1(PID %d)\n", getpid(), c1);
		printf("parent(PID %d): waiting for child_1(PID %d) to complete\n\n", getpid(), c1);	
	}
	if (c1 == 0){
		printf("child_1(PID %d): process started from parent(PID %d)\n", getpid(), getppid());
		int port[2];
		if (pipe(port) < 0){
    	perror("pipe error");
    	exit(0);
  	} 
		printf("child_1(PID 7061): forking child_1.1....child_1.%d\n\n", M);
		for(int i = 0; i<M; i++){
			int c2 = fork();
			if (c2 == 0){
				printf("child_1.%d(PID %d): fork() successful\n", i+1, getpid());
				int start = ith_part_start(i, N, M);
				int end = ith_part_end(i, N, M);
				int sum = summation(start, end);
				write(port[1], &sum, sizeof(int));
				printf("child_1.%d(PID %d): partial sum: [%d - %d] = %d\n",i+1, getpid(), start, end, sum);
				return 0;
			}
			wait(NULL);
		}
		wait(NULL);
		int totalSum = 0;
		for(int i = 0; i<M; i++){
			int r;
			read(port[0], &r, sizeof(int));
			totalSum += r;
		}
		printf("\nchild_1(PID %d): total sum = %d\n", getpid(), totalSum);
		printf("child_1(PID %d): child_1 completed\n\n", getpid());
		return 0;
	}
	wait(NULL);
	printf("parent(PID %d): parent completed\n", getpid());
	return 0;
}