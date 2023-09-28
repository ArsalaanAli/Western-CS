#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	printf("parent (PID %d): process started\n", getpid());
	char* N = argv[1];
	char* M = argv[2];
	char* S = argv[3];
	printf("parent (PID %d): forking child_1\n", getpid());
	int c1 = fork();
	if(c1 == 0){	
		//child 1
		printf("child_1 (PID %d): process started from parent (PID %d)\n", getpid(), getppid());
		printf("child_1 (PID %d): forking child_1.1\n", getpid());
		int c11 = fork();
		if(c11 == 0){
			//child 1.1
			printf("child_1.1 (PID %d): process started from child_1 (PID %d)\n", getpid(), getppid());
			printf("child_1.1 (PID %d): calling an external program [./external_program1.out]\n", getpid());
			execl("external_program1.out", N, NULL);
			return 0;
		}
		wait(NULL);
		printf("child_1 (PID %d): completed child_1.1\n", getpid());
		int c12 = fork();
		printf("child_1 (PID %d): forking child_1.2\n", getpid());
		if(c12 == 0){
			//child 1.2
			printf("child_1.2 (PID %d): process started from child_1 (PID %d)\n", getpid(), getppid());
			printf("child_1.2 (PID %d): calling an external program [./external_program1.out]\n", getpid());
			execl("external_program1.out", M, NULL);
			return 0;
		}
		wait(NULL);
		printf("child_1 (PID %d): completed child_1.2\n", getpid());
		return 0;
		
	}
	printf("parent (PID %d): fork successful for child_1 (PID %d)\n", getpid(), c1);
	printf("parent (PID %d): waiting for child_1 (PID %d) to complete\n", getpid(), c1);
	wait(NULL);
	printf("parent (PID %d): forking child_2\n", getpid());
	int c2 = fork();
	if(c2 == 0){
		printf("child_2 (PID %d): process started from parent (PID %d)\n", getpid(), getppid());
		printf("child_2 (PID %d): calling an external program [./external_program2.out]\n", getpid());
		execl("external_program2.out", S, NULL);
		return 0;
	}
	printf("parent (PID %d): fork successful for child_2 (PID %d)\n", getpid(), c2);
	wait(NULL);
	printf("completed parent\n");
	return 0;
}
